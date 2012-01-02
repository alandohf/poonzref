#include <stdio.h>

void clean_stdin(void);
int my_guessed(void);

int
main()
{
  const int MAGIC_NUMBER = 6;
  int guessed_number;

  printf("Try to guess what number I'm thinking of\n");
  printf("HINT: It's a number between 1 and 10\n");

  printf("enter your guess: ");

  guessed_number = my_guessed();

  printf("you guess %d \n",guessed_number);

  while (guessed_number != MAGIC_NUMBER)
    {
      printf("enter your guess: ");
     // scanf(" %d", &guessed_number);
      guessed_number = my_guessed();
    }

  printf("you win.\n");
    system("PAUSE");
  return 0;
}
    
void 
clean_stdin(void)
{
    int c;  

    do
    {
        c = fgetc(stdin);
    }
    while (c != '\n' && c != EOF);
}

int 
my_guessed()
{
    int n;
    int rv;
    do
    {
        rv = scanf("%d", &n);
        clean_stdin();
    }
    while (rv != 1);
 //   　如果只有a被成功读入，返回值为1
//　　如果a和b都未被成功读入，返回值为0
    return n;
}
