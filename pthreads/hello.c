#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void * PrintHello(void * data)
{
    int my_data = (int)data;
	/*sleep(1);/*added*/
    printf("\n Hello from new thread - got (%u) !\n", my_data);
    /*pthread_exit(NULL);*/
}

int main()
{
    int rc;
    pthread_t thread_id;
/*print out self id*/
      pthread_t tid;
      tid = pthread_self();
	printf("\n I'm thread (%u).\n",tid);

    int t = 11;

    rc = pthread_create(&thread_id, NULL, PrintHello, (void*)tid);
    if(rc)
    {
      printf("\n ERROR: return code from pthread_create is %d \n", rc);
      exit(1);
    }
	sleep(1); /*added*/
    printf("\n Created new thread (%u)... \n", thread_id);

    pthread_exit(NULL);
}


