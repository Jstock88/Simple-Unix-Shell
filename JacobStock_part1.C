//Name: Jacob Stock   CWID: 12249936

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#define MAX_LINE 80 /* The maximum length command */

int main(void)
{
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    int should_run = 1;  /* flag to determine when to exit program */
    char userIn[MAX_LINE];
    

    while (should_run) {
        printf("Stock_%d>", getpid());
        fflush(stdout);
        
        /**
        * After reading user input, the steps are:
        * (1) fork a child process using fork()
        * (2) the child process will invoke execvp()
        * (3) if command included &, parent will NOT invoke wait()
        */
        
        //Recive input
        fgets(userIn, MAX_LINE, stdin);

        userIn[strcspn(userIn, "\n")] = 0;
        
        char *token = strtok(userIn, " ");
        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        

        bool hasAmp = false;

        if (strcmp(args[i - 1], "&") == 0) {
            hasAmp = true;
            args[i - 1] = NULL;
        }


        pid_t pid;
        pid = fork();
        if (pid == 0) {  //The child
            printf("I am in the child");
            execvp(args[0], args);

        } else {  //The parent
            if(!hasAmp){
                wait(NULL);
            }
        }
    }
    return 0;
}