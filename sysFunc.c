#include <stdlib.h>

int main()
{
   system("ps -f");
   system("mkdir aaa");
   system("ls -l");
   system("rm -r aaa");
   system("ls -l");

   return 0;
}

