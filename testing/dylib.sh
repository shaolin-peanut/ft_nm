gcc -c mymod.c
gcc -dynamiclib -current_version 1.0  mymod.o  -o libmylib.dylib
