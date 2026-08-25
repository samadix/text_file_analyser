## Compilation

Compile the project with:

gcc -O3 simple_filetxt_analyser.c -o analyse

Then run:

./analyse -opt pattern file 

## Usage

The program supports three main options:

./analyse -s <word> <file>

./analyse -o <word> <file>

./analyse -l <word> <file>

-s : Search for the word and display matching lines.
-o : Count the occurrences of the word.
-l : Count the lines containing the word.

Options can be combined:

./analyse -sol <word> <file>

For help:

./analyse -h

## Release

A precompiled version is available in the `release/` directory.
chmod +x analyse
./analyse -opt pattern file


## Performance

Tested on a 10 GB text file using the pattern "SXD".

The analyzer processes approximately 170 MB/s on average
and uses less than 1.5 MB of RAM.

10 GB benchmark:

-l : 39.30 s  | ~254 MB/s | ~1.5 MB RAM

-o : 67.80 s  | ~147 MB/s | ~1.5 MB RAM

-s : 91.37 s  | ~109 MB/s | ~1.4 MB RAM

## About

A lightweight text file analyzer written in C.

The program relies only on standard C libraries and uses a custom pattern
matching algorithm based on the **Bad Character rule**.

It is designed to analyze large text files with very low memory usage.
