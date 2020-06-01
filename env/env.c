#include <stdio.h>
#include <stdlib.h>  /* what header file is needed? */

int main(void)
{
  char *val;

  val = getenv("HOME");

  if (val == NULL)
      printf("variable not found\n");
  else
      printf("HOME = \"%s\"\n", val);

  return 0;
}

