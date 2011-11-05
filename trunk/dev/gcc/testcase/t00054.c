/**
name: 
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
Examples of pointer constructs
Below are some example constructs which may aid in creating your pointer.
int i;         // integer variable 'i'
int *p;        // pointer 'p' to an integer
int a[];       // array 'a' of integers
int f();       // function 'f' with return value of type integer
int **pp;      // pointer 'pp' to a pointer to an integer
int (*pa)[];   // pointer 'pa' to an array of integer
int (*pf)();   // pointer 'pf' to a function with returnvalue integer
int *ap[];     // array 'ap' of pointers to an integer
int *fp();     // function 'fp' which returns a pointer to an integer
int ***ppp;    // pointer 'ppp' to a pointer to a pointer to an integer
int (**ppa)[]; // pointer 'ppa' to a pointer to an array of integers
int (**ppf)(); // pointer 'ppf' to a pointer to a function with return value of type integer
int *(*pap)[]; // pointer 'pap' to an array of pointers to an integer
int *(*pfp)(); // pointer 'pfp' to function with return value of type pointer to an integer
int **app[];   // array of pointers 'app' that point to pointers to integer values
int (*apa[])[];// array of pointers 'apa' to arrays of integers
int (*apf[])();// array of pointers 'apf' to functions with return values of type integer
int ***fpp();  // function 'fpp' which returns a pointer to a pointer to a pointer to an int
int (*fpa())[];// function 'fpa' with return value of a pointer to array of integers
int (*fpf())();// function 'fpf' with return value of a pointer to function which returns an integer
**/

#include <stdio.h> 
#include <stdlib.h> 

 