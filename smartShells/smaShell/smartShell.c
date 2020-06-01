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
 
int main()
{
    /* Step 1:
     *   Add calls to execute_cmd here to test it out. 
     *   Example: execute_cmd("ps -f");
     *   ... other commands you wish to try here ...
	
     */
	execute_cmd("ps -f");
	execute_cmd("ls -l");
	execute_cmd("mkdir a");
	execute_cmd("ls -l");
	execute_cmd("rmdir a");
	execute_cmd("ls -l");
 
    /*
     * Step 2: 
     *   Read and process commands in an infinite loop
     *   Exit when the user types "quit" 
     */
     
	for( ; ; )
	{
		printf("enter a command \n");
		int size =50;
		char buf[size];
		
		fgets(buf, size, stdin);

		/*if input "quit", exit the program*/
		if(strncmp(buf,"quit",4)==0)
		{
			exit(0);
		}
		/*if input "mem", display the amount of total memory available in kibibytes*/
		else if(strncmp (buf,"mem",3)==0)
		{
			execute_cmd ("free -k");
		}
		/*if input "disk", display the amount of disk space available*/
		else if(strncmp (buf,"disk",4)==0)
		{
			execute_cmd ("df -H /dev/sda1");
		}
		/*if input "list", display the files in current directory*/
		else if (strncmp (buf, "list",4)==0)
		{
			execute_cmd ("ls -l");
		}
		/*if input "time", display the sentence "never too early"*/
		else if (strncmp (buf, "time",4)==0)
		{
			printf("never too early \n");
		}
		/*for every other command, try to execute as it as*/
		else
		{
			execute_cmd(buf);
		}

		
	}
     return 0;
}
