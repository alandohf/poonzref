#include <stdio.h>



/**
Just like structures, the members of unions can be accessed with the . and -> operators. However, unlike structures, the variables my_union1 and my_union2 above can be treated as either integers or floating-point variables at different times during the program. For example, if you write my_union1.int_member = 5;, then the program sees my_union1 as being an integer. (This is only a manner of speaking. However, my_union1 by itself does not have a value; only its members have values.) On the other hand, if you then type my_union1.float_member = 7.7;, the my_union variable loses its integer value. It is crucial to remember that a union variable can only have one type at the same time.
**/

int 
main()
{

union int_or_float
{
  int int_member;
  float float_member;
};

union int_or_float my_union1, my_union2;

my_union1.int_member = 5;
my_union2.float_member = 5.6;
printf("int:%d\n",my_union1.int_member);
printf("float:%f\n",my_union2.float_member);
return 0;
}
