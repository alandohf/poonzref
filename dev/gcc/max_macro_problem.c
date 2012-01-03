/**
When the text substitution occurs there will be two instances of ++sheep. Another more sinister way for this bug may manifest itself is when you pass use a function as an argument to a macro. If the function modifies a global or static variable then this modification may occur multiple times. These bugs can be very hard to find, the code is perfectly valid so the compiler has nothing to complain about, the bug will only be noticed at run time and wont occur every time the macro is called, only when it is called with an argument that has a side effect.
**/

#include <stdio.h>
#define MAX(a, b) (a > b ? a : b)

int
main()
{
  int cows = 10, sheep = 12;

  printf("We have %d of our most common animal\n", MAX(cows, sheep));

  printf("Hang on, we just bought another one.\n");
  printf("Now we have %d.\n", MAX(cows, ++sheep));

  return 0;
}
