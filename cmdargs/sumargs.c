#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
	if(argc > 3)
    	{
        	printf("Invalid command line: supply two integers \n");
        	exit(1);
    	}
	
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);

	printf("%d\n", a + b);
	return 0;
}
