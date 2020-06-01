
#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h>
int main ()
{  
	int ret = fork(); 

 	 if(ret == 0) {    
		printf("Child runs\n");    
		execl("./xrunmy", "xrunmy", "dog", NULL);   
		 printf("Child done\n");  
	}

  	else {   
		 wait(NULL);    
		printf("Parent done\n");  
	}
}
