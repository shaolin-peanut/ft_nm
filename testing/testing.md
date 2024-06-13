# Guide to testing
## Things that should work
- no argument, looks for a.out
    - print out the symbols in a.out if there is one in the current directory
- 1 argument
    - prints out the symbols
- multiple arguments
    - prints a newline, the name of the file and then the symbols of the file, for each file
- object files
    - 64 and 32 bit
- shared object library. dynamic shared library
## Errors that should be properly handled
- 