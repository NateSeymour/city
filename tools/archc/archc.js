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

const parseArchitectureFile = (path) => {};

const architectures = fs
    .readdirSync(options.input, { recursive: true })
    .filter((entry) => entry.endsWith('architecture.txt'))
    .map((architecturePath) => path.join(options.input, architecturePath));

console.log(architectures);
