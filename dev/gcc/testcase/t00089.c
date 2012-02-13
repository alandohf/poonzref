//~ Z.1.3  EXTERNAL VARIABLE - extern
//~ All variables we have seen so far have had limited scope (the block in which they are declared) and limited lifetimes (as for automatic variables).
//~ However, in some applications it may be useful to have data which is accessible from within any block and/or which remains in existence for the entire execution of the program.  Such variables are called global variables, and the C language provides storage classes which can meet these requirements; namely, the external (extern) and static (static) classes.
//~ Declaration for external variable is as follows:
//~ extern int var;
//~ External variables may be declared outside any function block in a source code file the same way any other variable is declared; by specifying its type and name (extern keyword may be omitted).
//~ Typically if declared and defined at the beginning of a source file, the extern keyword can be omitted.  If the program is in several source files, and a variable is defined in let say file1.c and used in file2.c and file3.c then the extern keyword must be used in file2.c and file3.c.
//~ But, usual practice is to collect extern declarations of variables and functions in a separate header file (.h file) then included by using #include directive.
//~ Memory for such variables is allocated when the program begins execution, and remains allocated until the program terminates.  For most C implementations, every byte of memory allocated for an external variable is initialized to zero.
//~ The scope of external variables is global, i.e. the entire source code in the file following the declarations. All functions following the declaration may access the external variable by using its name.  However, if a local variable having the same name is declared within a function, references to the name will access the local variable cell.
//~ The following program example demonstrates storage classes and scope.
/* storage class and scope */
#include <stdio.h>
 
void funct1(void);
void funct2(void);
 
/* external variable, scope is global to main(), funct1() and funct2(), extern keyword is omitted here, coz just one file */
int globvar = 10;
 
int main()
{
    printf("\n****storage classes and scope****\n");
    /* external variable */
    globvar = 20;
    
    printf("\nVariable globvar, in main() = %d\n", globvar);
    funct1();
    printf("\nVariable globvar, in main() = %d\n", globvar);
    funct2();
    printf("\nVariable globvar, in main() = %d\n", globvar);
    return 0;
}
 
/* external variable, scope is global to funct1() and funct2() */
int globvar2 = 30;
 
void funct1(void)
{
    /* auto variable, scope local to funct1() and funct1() cannot access the external globvar */
    char globvar;
   
    /* local variable to funct1() */
    globvar = 'A';
    /* external variable */
    globvar2 = 40;
   
    printf("\nIn funct1(), globvar = %c and globvar2 = %d\n", globvar, globvar2);
}
 
void funct2(void)
{
    /* auto variable, scope local to funct2(), and funct2() cannot access the external globvar2 */
    double globvar2;
    /* external variable */
    globvar =  50;
    /* auto local variable to funct2() */
    globvar2 = 1.234;
    printf("\nIn funct2(), globvar = %d and globvar2 = %.4f\n", globvar, globvar2);
}
 
//~ Output:
 
 
//~ External variables may be initialized in declarations just as automatic variables; however, the initializers must be constant expressions. The initialization is done only once at compile time, i.e. when memory is allocated for the variables.
//~ In general, it is a good programming practice to avoid using external variables as they destroy the concept of a function as a 'black box' or independent module.
//~ The black box concept is essential to the development of a modular program with modules.  With an external variable, any function in the program can access and alter the variable, thus making debugging more difficult as well.  This is not to say that external variables should never be used.
//~ There may be occasions when the use of an external variable significantly simplifies the implementation of an algorithm.  Suffice it to say that external variables should be used rarely and with caution.

