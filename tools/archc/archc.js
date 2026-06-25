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
        kwName: /^name/,
        kwVersion: /^version/,
        kwEncoding: /^encoding/,
        kwDynamic: /^dynamic/,

        open: /^{/,
        close: /^}/,

        number: /^\d+/,
        identifier: /^[a-zA-Z]([a-zA-Z\d:]+)?/,

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

const parseArchitectureFile = (path) => {
    const rawArchitectureDefinition = fs.readFileSync(path, 'utf-8');
    const tokens = tokenize(rawArchitectureDefinition);

    const architecture = {};

    return {};
};

const architectures = fs
    .readdirSync(options.input, { recursive: true })
    .filter((entry) => entry.endsWith('architecture.txt'))
    .map((architecturePath) => path.join(options.input, architecturePath))
    .map((architecturePath) => parseArchitectureFile(architecturePath));

console.log(architectures);
