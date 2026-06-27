import fs from 'node:fs';

const tokens = {
    kwEncoding: /^encoding/,
    kwDynamic: /^dynamic/,
    kwFixed: /^fixed/,

    kwInstruction: /^instruction/,

    kwRegister: /^register/,
    kwBank: /^bank/,

    cppOpen: /^%{{/,
    cppClose: /^}}/,

    left: /^\(/,
    right: /^\)/,
    open: /^{/,
    close: /^}/,

    colon: /^:/,
    semi: /^;/,
    comma: /^,/,
    star: /^\*/,
    bang: /^#/,
    percent: /^%/,

    number: /^\d+/,
    identifier: /^[a-zA-Z]([a-zA-Z\d:_]+)?/,
};

export class ArchitectureFileParser {
    input;
    cursor = 0;

    architecture = {
        name: '',
        version: 0,
        preprocessorDirective: [],
        encodingSize: 0,
        encoding: {},
        instruction: {},
        register: {},
    };

    lookahead() {
        const whitespace = this.input.slice(this.cursor).match(/^\s*/);
        this.cursor += whitespace[0].length;

        if (this.cursor === this.input.length) {
            return {
                type: 'eof',
                value: null,
                position: this.cursor,
            };
        }

        for (const [token, regex] of Object.entries(tokens)) {
            const match = this.input.slice(this.cursor).match(regex);

            if (match) {
                return {
                    type: token,
                    value: match[0],
                    position: this.cursor,
                };
            }
        }

        return {
            type: 'none',
            value: null,
            position: this.cursor,
        };
    }

    consume(type) {
        const token = this.lookahead();
        this.cursor += token.value.length;

        if (type && token.type !== type) {
            this.fail(`Unexpected token '${token.type}' (expected '${type}')!`);
        }

        return token;
    }

    consumeUntil(pattern, include = false) {
        const begin = this.cursor;

        while (this.cursor < this.input.length) {
            if (this.input.slice(this.cursor).startsWith(pattern)) {
                if (include) {
                    this.cursor += pattern.length;
                }

                return this.input.slice(begin, this.cursor).trim();
            }

            this.cursor++;
        }

        this.fail(`Failed to find pattern "${pattern}" before reaching EOF!`);
    }

    fail(message) {
        console.error(`[ERROR] ${message}`);
        console.error(
            `[ERROR] At "${this.input.slice(Math.max(this.cursor - 20, 0), Math.min(this.cursor + 20, this.input.length)).trim()}"`,
        );

        process.exit(1);
    }

    ParseEncodingBlock() {
        this.consume('kwEncoding');

        let lh = this.lookahead();
        switch (lh.type) {
            case 'kwDynamic': {
                this.consume();

                this.architecture.encodingSize = 'dynamic';

                break;
            }

            case 'kwFixed': {
                this.consume();

                const size = this.consume('number');
                this.architecture.encodingSize = Number(size.value);

                break;
            }
        }

        this.consume('open');

        while (this.lookahead().type === 'identifier') {
            const encodingName = this.consume('identifier').value;

            this.architecture.encoding[encodingName] = {};

            if (this.lookahead().type === 'left') {
                this.architecture.encoding[encodingName].constructorArgs = this.consumeUntil(')', true);
            } else {
                this.architecture.encoding[encodingName].constructorArgs = '()';
            }

            if (this.lookahead().type === 'colon') {
                this.architecture.encoding[encodingName].initializer = this.consumeUntil('{');
            }

            this.consume('open');

            this.architecture.encoding[encodingName].properties = [];
            while (this.lookahead().type !== 'close') {
                switch (this.lookahead().type) {
                    case 'identifier': {
                        this.architecture.encoding[encodingName].properties.push(this.consumeUntil(';', true));
                        break;
                    }

                    case 'cppOpen': {
                        this.consume('cppOpen');

                        this.architecture.encoding[encodingName].constructorBody = this.consumeUntil('}}');

                        this.consume('cppClose');
                    }
                }
            }

            this.consume('close');
        }

        this.consume('close');
    }

    ParseInstructionBlock() {
        this.consume('kwInstruction');

        this.consume('open');

        while (this.lookahead().type === 'identifier') {
            const encodingType = this.consume('identifier');
            const instructionName = this.consume('identifier');

            const properties = [];
            if (this.lookahead().type === 'open') {
                this.consume();

                while (this.lookahead().type === 'identifier') {
                    const property = this.consume('identifier');
                    properties.push(property.value);

                    if (this.lookahead().type === 'comma') {
                        this.consume();
                    } else {
                        break;
                    }
                }

                this.consume('close');
            }

            this.architecture.instruction[instructionName.value] = {
                encoding: this.architecture.encoding[encodingType.value],
                properties,
            };
        }

        this.consume('close');
    }

    ParseRegisterBlock() {
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

    ParseStatement() {
        const lh = this.lookahead();
        switch (lh.type) {
            case 'percent': {
                this.consume();

                const property = this.consume('identifier');
                this.architecture[property.value] = this.consumeUntil('\n');

                return;
            }

            case 'bang': {
                const directive = this.consumeUntil('\n');
                this.architecture.preprocessorDirective.push(directive.value);

                return;
            }

            case 'kwEncoding': {
                this.ParseEncodingBlock();

                return;
            }

            case 'kwInstruction': {
                this.ParseInstructionBlock();

                return;
            }

            case 'kwRegister': {
                this.ParseRegisterBlock();

                return;
            }

            default: {
                this.fail(`Unexpected token. Statement cannot begin with "${lh.type}"!`);
            }
        }
    }

    ParseBody() {
        while (this.lookahead().type !== 'eof') {
            this.ParseStatement();
        }
    }

    parse() {
        this.ParseBody();

        return this.architecture;
    }

    constructor(architecturePath) {
        this.input = fs.readFileSync(architecturePath, 'utf-8');
    }
}
