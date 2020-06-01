#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char* argv[])
{
	if (argc > 2)
	{
		printf("Invalid command line: supply a integer \n");
		exit(1);
	}

	int a = atoi(argv[1]);

	if (fork()!=0)
	{
		if(fork()==0)
		{
			int fac = 1;
			for (int i =1; i<=a; i++)
			{
				fac*=i;
			}
			printf ("\n ID = [%d] Factorial of %d is %d \n", getpid(), a, fac);

		}
		else
		{
			wait(NULL);
			wait(NULL);
			printf ("\n ID = [%d] Done \n", getpid());
		}
	}
	else
	{
		int sum = a*(a+1)/2;
		printf ("\n ID = [%d] Sum of positive integers up to %d is %d \n", getpid(),a,sum);
	}

	return 0;
}


