import fs from 'node:fs';
import process from 'node:process';
import path from 'node:path';
import commandLineArgs from 'command-line-args';

const options = commandLineArgs([
    {
        name: 'input',
        type: String,
    },
    {
        name: 'output',
        type: String,
    },
]);

if (!options.input || !options.output) {
    console.error('[ERROR] Must provide input and output directories!');
    process.exit(1);
}

const tokenize = (input) => {
    const tokens = [];

    const tokenTypes = {
        kwName: /^%name/,
        kwVersion: /^%version/,

        kwEncoding: /^encoding/,
        kwDynamic: /^dynamic/,
        kwFixed: /^fixed/,

        kwInstruction: /^instruction/,

        kwRegister: /^register/,
        kwBank: /^bank/,
        kwVolatile: /^volatile/,

        star: /^\*/,

        open: /^{/,
        close: /^}/,

        number: /^\d+/,
        identifier: /^[a-zA-Z]([a-zA-Z\d:_]+)?/,

        preprocessorDirective: /^#.+$/m,
    };

    while (input.length > 0) {
        const tokenCount = tokens.length;
        input = input.trimStart();

        for (const [tokenType, regex] of Object.entries(tokenTypes)) {
            const match = input.match(regex);
            if (match) {
                tokens.push({
                    type: tokenType,
                    value: match[0],
                });

                break;
            }
        }

        if (tokens.length === tokenCount) {
            console.error('[ERROR] Unexpected token!');
            process.exit(1);
        }

        input = input.slice(tokens[tokens.length - 1].value.length);
    }

    return tokens;
};

class ArchitectureFileParser {
    tokens = [];

    architecture = {
        name: '',
        version: 0,
        preprocessorDirective: [],
        encoding: {
            size: 0,
            named: {},
        },
        instruction: {},
        register: {},
    };

    lookahead() {
        return this.tokens[0] || null;
    }

    consume(type) {
        const token = this.tokens.shift() || null;

        if (type && token.type !== type) {
            console.error(`[ERROR] Unexpected token ${token.type} (expected ${type})`);
            process.exit(1);
        }

        return token;
    }

    fail(message) {
        console.error(`[ERROR] ${message}`);
        console.error(`[ERRRO] Next token: ${JSON.stringify(this.lookahead())}`);

        process.exit(1);
    }

    AnonymousEncodingDefinitionBlock() {
        const properties = {};

        this.consume('open');

        while (this.lookahead().type !== 'close') {
            const type = this.consume('identifier');
            const name = this.consume('identifier');

            properties[name.value] = type.value;
        }

        this.consume('close');

        return properties;
    }

    EncodingBlock() {
        this.consume('kwEncoding');

        let lh = this.lookahead();
        switch (lh.type) {
            case 'kwDynamic': {
                this.consume();

                this.architecture.encoding.size = 'dynamic';

                break;
            }

            case 'kwFixed': {
                this.consume();

                const size = this.consume('number');
                this.architecture.encoding.size = Number(size.value);

                break;
            }
        }

        this.consume('open');

        while (this.lookahead().type === 'identifier') {
            const encodingName = this.consume('identifier');
            this.architecture.encoding.named[encodingName.value] = this.AnonymousEncodingDefinitionBlock();
        }

        this.consume('close');
    }

    InstructionBlock() {
        this.consume('kwInstruction');

        this.consume('open');

        while (this.lookahead().type === 'identifier') {
            const instructionName = this.consume('identifier');

            switch (this.lookahead().type) {
                case 'identifier': {
                    const encodingType = this.consume('identifier');

                    this.architecture.instruction[instructionName.value] = {
                        encoding: this.architecture.encoding.named[encodingType.value],
                    };

                    break;
                }

                case 'open': {
                    this.architecture.instruction[instructionName.value] = {
                        encoding: this.AnonymousEncodingDefinitionBlock(),
                    };

                    break;
                }
            }
        }

        this.consume('close');
    }

    RegisterBlock() {
        this.consume('kwRegister');

        this.consume('open');

        while (this.lookahead().type === 'identifier') {
            const registerNameOrPrefix = this.consume('identifier');
            this.consume('star');

            const type = this.consume('identifier');

            this.consume('open');

            while (this.lookahead().type === 'number') {
                const number = this.consume('number');

                const attributes = [];
                while (this.lookahead().type === 'identifier' || this.lookahead().type === 'kwVolatile') {
                    const attribute = this.consume();
                    attributes.push(attribute.value);
                }

                this.architecture.register[`${registerNameOrPrefix.value}${number.value}`] = {
                    type: type.value,
                    attributes,
                };
            }

            this.consume('close');
        }

        this.consume('close');
    }

    Statement() {
        const lh = this.lookahead();
        switch (lh.type) {
            case 'kwName': {
                this.consume();

                const name = this.consume('identifier');
                this.architecture.name = name.value;

                return;
            }

            case 'kwVersion': {
                this.consume();

                const version = this.consume('number');
                this.architecture.version = Number(version.value);

                return;
            }

            case 'preprocessorDirective': {
                const directive = this.consume();
                this.architecture.preprocessorDirective.push(directive.value);

                return;
            }

            case 'kwEncoding': {
                this.EncodingBlock();

                return;
            }

            case 'kwInstruction': {
                this.InstructionBlock();

                return;
            }

            case 'kwRegister': {
                this.RegisterBlock();

                return;
            }

            default: {
                this.fail('unexpected token!');
            }
        }
    }

    Body() {
        while (this.lookahead() != null) {
            this.Statement();
        }
    }

    parse() {
        this.Body();

        return this.architecture;
    }

    constructor(architecturePath) {
        const rawArchitectureDefinition = fs.readFileSync(architecturePath, 'utf-8');
        this.tokens = tokenize(rawArchitectureDefinition);
    }
}

const parseArchitectureFile = (path) => {
    const parser = new ArchitectureFileParser(path);

    return parser.parse();
};

const writeArchitectureFiles = (architecture) => {
    const outputDir = path.join(options.output, 'archc');
    if (!fs.existsSync(outputDir)) {
        fs.mkdirSync(outputDir);
    }

    const outputFile = path.join(outputDir, `${architecture.name}.h`);

    const output = `//
// Autogenerated by archc
//

#ifndef ARCHC_${architecture.name.toUpperCase()}_H
#define ARCHC_${architecture.name.toUpperCase()}_H

// Preprocessor Directives
${architecture.preprocessorDirective.join('\n')}

namespace city
{
    class ${architecture.name} {};
    
    template<>
    class Block<${architecture.name}> 
    {
    public:
        ${Object.entries(architecture.instruction)
            .map(([inst, def]) => `[[nodiscard]] city::Value &Insert${inst.toUpperCase()}() {}`)
            .join('\n\t\t')}
    };
} // namespace city

#endif // ARCHC_${architecture.name.toUpperCase()}_H
    `;

    fs.writeFileSync(outputFile, output, 'utf-8');
};

const architectures = fs
    .readdirSync(options.input, { recursive: true })
    .filter((entry) => entry.endsWith('.arch'))
    .map((architecturePath) => path.join(options.input, architecturePath))
    .map(parseArchitectureFile)
    .forEach(writeArchitectureFiles);
