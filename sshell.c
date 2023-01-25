#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CMDLINE_MAX 512

struct myparse{
    char arg[512];
    char com[512]; 
};

void myfunc(struct myparse *par, char command[512]){
        char *token = strtok(command, " ");
        int cnt = 0;
        while (token != NULL)
        {
            cnt++;
            printf("%s\n", token);
            if (cnt == 1)
            {
                strcpy(par->com, token);
                printf("this is parcom%s\n", par->com);
            } 
            if (cnt == 2)
            {
                strcpy(par->arg, token);
            }
            if (cnt > 2)
            {
                strcat(par->arg, " ");
                strcat(par->arg, token);
            }

            token = strtok(NULL, " ");
        }
        
}

void mycd(char argument[512], char comline[512])
{
    
    if (chdir(argument) != 0)
    {
        printf("Error: cannot cd into directory\n");
        printf("+ completed '%s' [1]\n", comline);
    }
    else
    {
        printf("+ completed '%s' [0]\n", comline);
    }
}

int main(void){
        struct myparse *p1 = (struct myparse *) malloc(sizeof(struct myparse));
        
        char cmd[CMDLINE_MAX];

        while (1) {
                char *nl;
                int retval;

                /* Print prompt */
                printf("sshell@ucd$ ");
                fflush(stdout);

                /* Get command line */
                fgets(cmd, CMDLINE_MAX, stdin);

                /* Print command line if stdin is not provided by terminal */
                if (!isatty(STDIN_FILENO)) {
                        printf("%s", cmd);
                        fflush(stdout);
                }

                /* Remove trailing newline from command line */
                nl = strchr(cmd, '\n');
                if (nl)
                        *nl = '\0';

                /* Builtin command */
                if (!strcmp(cmd, "exit")) {
                        fprintf(stderr, "Bye...\n");
                        break;
                }
                myfunc(p1, cmd);
                printf("p1com %s\n", p1->com);
                if (!strcmp(p1->com, "cd")){
                        mycd(p1->arg, p1->com);
                        continue;
                }
                /* Regular command */
                pid_t pid = fork();
                /*char *args[] = {cmd, NULL};*/
                
                if (pid == 0) {
                /* Child */
                    execvp(p1->com,p1->arg);
                    perror("execv");
                    exit(1);
                } else if (pid > 0) {
                /* Parent */
                    waitpid(pid, &retval, 0);
                    // printf("Child returned %d\n",
                    // WEXITSTATUS(status));
                } else {
                    perror("fork");
                    exit(1);
                }
                // retval = system(cmd);
                fprintf(stderr, "+ completed '%s' [%d]\n",
                        cmd, retval);
        }

        return EXIT_SUCCESS;
}