#include <stdio.h>
      
int
main()
{
/**
struct personal_data
{
  char name[100];
  char address[200];
  int year_of_birth;
  int month_of_birth;
  int day_of_birth;
};
**/
///**
struct Person
{
  char *name;
  int age;
  int height_in_cm;
};
//**/
  struct Person hero = {"Robin Hood",20, 191 };

  struct Person john;

  john.age = 31;
  john.name = "John Little";
  john.height_in_cm = 237;

  struct Person sidekick=john;

  printf("%s is %d years old and stands %dcm tall in his socks\n",
         sidekick.name, sidekick.age, sidekick.height_in_cm);

  printf( "He is often seen with %s.\n", hero.name );

  return 0;
}
      
