#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>


void tree ( )
{
	
	printf ("\n ID = [%d] I'm the root parent. \n", getpid());
	if (fork()!=0)
	{
		if (fork()==0)
		{
			printf ("\n ID = [%d] My parent is %d. \n", getpid(), getppid());
			if (fork ()==0)
			{
				printf ("\n ID = [%d] My parent is %d. \n", getpid(), getppid());

			}
			wait(NULL);
			
		}		
		
	}
	
	else
	{
		printf ("\n ID = [%d] My parent is %d. \n", getpid(), getppid());
		if (fork ()==0)
		{
				printf ("\n ID = [%d] My parent is %d. \n", getpid(), getppid());

		}		
			//printf ("\n ID = [%d] My parent is %d. \n", getpid(), getppid());
			wait(NULL);
	}	
	wait(NULL);
	wait(NULL);
}

int main ( )
{
	tree();
	return 0;
}
