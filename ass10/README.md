# Questions -

Write a program to add two arrays. The addition should be
performed by calling a function from a dyanmic linked library.

[ Use dlopen(), dlsym() and dlclose() ]

## Note

Make the .so file from Addlib.c DLL by using : ___gcc -shared -o Addlib.so -fPIC Addlib.c___

Compile ass10_1.c by : ___gcc ass10_1.c -ldl___

