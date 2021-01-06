

#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>

int main()
{
    int pid;
    int cpid;
    int status;
    int i=0;

    printf("Ready to fork...\n");
    pid = fork();	// create a clone
    printf("Fork returned %d\n",pid);
    cpid = wait(&status);
    if (pid == 0) {
// child process instructions
printf(“Child process pid=%d parent process id=%d \n”,getpid(), getppid());
return(55);
} else if (pid > 0) {
// parent process instructions
printf(“\t Parent process pid=%d child process id=%d \n”,getpid(), pid);
return(0);
} else {
// pid < 0 – an error occurred during the form operation
 printf(“\t ERROR - parent process pid=%d could not fork a child process \n”,getpid());
return(1);
}


}
