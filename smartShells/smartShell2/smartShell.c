//----------------------------
// Name: Shiyu (Jenny) Su
// Date: Spring 2020
// Class: Computer Systems II
// Assignment: Smart Shell
//----------------------------
 
#include <string.h>    /* for strcpy and strtok */
 
/* Include other header files that are needed */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

       #include <sys/stat.h>
       #include <fcntl.h>
 
#define MAX_ARGV  10 /* maximum number of command tokens */
#define MAX_CMD   80 /* maximum length of command */
 
void tokenize_cmd (char * cmd, int max, char * argv[])
/* Input:  cmd is the command to be tokenized
 *         max is the maximum number of tokens allowed  
 * Output: argv is the array of tokens (command arguments) 
 */
{
    int num_args = 0;           /* number of arguments (tokens) in cmd */
 
    if(cmd == NULL) return;     /* nothing to do */
 
    /* Tokenize the command */
    argv[0] = strtok(cmd, " \n");
    while((num_args < max) && (argv[num_args] != NULL))
    {
       num_args++;
       argv[num_args] = strtok(NULL, " \n");
    }
}
 
void execute_cmd(char * cmd)
{
    char * argv[MAX_ARGV];  /* array of command arguments*/
    char cmd_copy[MAX_CMD]; /* buffer to store local copy of cmd*/
 
    /* Make a local copy of the command */
    if(cmd == NULL) return; /* nothing to do */
    strcpy(cmd_copy, cmd);
 
    /* Tokenize the command */
    tokenize_cmd(cmd_copy, MAX_ARGV, argv);
 
    /* Fork a child to execute the command 
     *   - if execvp fails, print an error message and exit
     */
	int ret = fork();
	if (ret < 0)
	{
		printf("Fork error.\n");
		exit(1);
	}
	if (ret == 0)
	{
		execvp (argv[0], argv);
		printf("Exec error. Please enter another command. \n");
		exit(1);
	}
    /* Parent waits for child to finish execution */
	else
	{
		wait(NULL);
	}
	printf("All Finished! \n");
}
 
void execute_output_redirect_cmd(char * cmd, char * fname)
{
	char * argv[MAX_ARGV];  /* array of command arguments*/
    char cmd_copy[MAX_CMD]; /* buffer to store local copy of cmd*/
	int fd;
 
    if(cmd == NULL) return; /* nothing to do */
    strcpy(cmd_copy, cmd);
 
    tokenize_cmd(cmd_copy, MAX_ARGV, argv);
 
	int ret = fork();
	if (ret < 0)
	{
		printf("Fork error.\n");
		exit(1);
	}
	if (ret == 0)
	{
	 	
		fd = open("test3.txt", O_RDWR | O_CREAT);
		if(fd == -1)
		{
			printf("Error. File 1 already exist.\n");
			exit(1); //exit if file already exist
			
		}
		else
		{
			dup2(fd,1);
			close (fd);
			execvp (argv[0], argv);
			//close (1);
			printf("Exec error. Please enter another command. \n");
			exit(1);
		}
	}
    /* Parent waits for child to finish execution */
	else
	{
		wait(NULL);
	}
	printf("All Finished! \n");
	
}

void execute_input_redirect_cmd(char * cmd, char * fname)
{
	char * argv[MAX_ARGV];  
    char cmd_copy[MAX_CMD]; 
	int fd;
 
    if(cmd == NULL) return; /* nothing to do */
    strcpy(cmd_copy, cmd);
 
    tokenize_cmd(cmd_copy, MAX_ARGV, argv);
 
	int ret = fork();
	if (ret < 0)
	{
		printf("Fork error.\n");
		exit(1);
	}
	if (ret == 0)
	{
		fd = open("test2.txt", O_RDONLY);
		if(fd == -1)
		{
			printf("Error. File 2 doesn't exist.\n");
			
		}
		else
		{
			dup2(fd,0);
			close (fd);
			execvp (argv[0], argv);
			//close (0);
			printf("Exec error. Please enter another command. \n");
			exit(1);
		}
	}
    /* Parent waits for child to finish execution */
	else
	{
		wait(NULL);
	}
	printf("All Finished! \n");
	
}

void execute_piped_cmd (char * cmd1, char * cmd2)
{
	if(cmd1==NULL || cmd2==NULL)
	{
		return;
	}
	char * cmdargv1[MAX_ARGV]; 
    	char cmd_copy1[MAX_CMD]; 
	strcpy(cmd_copy1, cmd1);
    	tokenize_cmd(cmd_copy1, MAX_ARGV,cmdargv1);/* Tokenize cmd1*/

	char * cmdargv2[MAX_ARGV];  /* array of command arguments*/
    	char cmd_copy2[MAX_CMD]; /* buffer to store local copy of cmd*/
	strcpy(cmd_copy2, cmd2);
    	tokenize_cmd(cmd_copy2, MAX_ARGV,cmdargv2);/* Tokenize cmd2 */

	int fd[2];
	int ret;

	ret = pipe(fd);
	if (ret == -1)
	{
		printf("Pipe creation fails");
		exit(1);
	}

	ret = fork();
	if(ret == 0) //first child
	{
		close(fd[0]);
		dup2(fd[1],1);
		close(fd[1]);
		execvp (cmdargv1[0], cmdargv1);
		close (1);
		printf("Exec error. Please enter another command. \n");
		exit(1);
	}	
	else 
	{
		ret = fork();
		if (ret == 0) //second child
		{
			close(fd[1]);
			dup2(fd[0],0);
			close(fd[0]);
			execvp (cmdargv2[0], cmdargv2);
			close (0);
			printf("Exec error. Please enter another command. \n");
			exit(1);
		}
		else //parent
		{		
			close(fd[0]);
			close(fd[1]);
			wait(NULL);//make sure all past commands finish before going on to next one (might not be in this function)
			wait(NULL);
		}
	}

}


int main()
{
    
	execute_output_redirect_cmd("ps -f", "test1.txt");
        execute_input_redirect_cmd("sort","test2.txt");
	//execute_cmd("ps");

	execute_piped_cmd("ps","wc -l");
	

     return 0;
}
