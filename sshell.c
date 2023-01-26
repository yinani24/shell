#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <fcntl.h>

#define CMDLINE_MAX 512
#define ARGS_LIMIT 16

struct myparse{
    char **arg;
    char com[CMDLINE_MAX]; 
    char dir[CMDLINE_MAX];
    char firstcmd[CMDLINE_MAX];
    char file[CMDLINE_MAX];
    int do_caret;
};

void secondtokenparser(struct myparse * par, char secondtoken[CMDLINE_MAX]){
        char *strtoken = strtok(secondtoken, " ");
        while(strtoken != NULL){
                printf("Strtoken: %s\n",strtoken);
                strcpy(par->file, strtoken);
                strtoken = strtok(NULL, " ");
        }
}

void parser(struct myparse *par, char command[CMDLINE_MAX]){
        char *token = strtok(command, " ");
        int cnt = 0;
        while (token != NULL)
        {
            cnt++;
            // printf("%s\n", token);

            if (cnt == 1)
            {   
                strcpy(par->com, token);
                // par->arg[cnt-1] = malloc(CMDLINE_MAX * sizeof(char*));
                strcpy(par->arg[cnt - 1], token);
                // printf("this is parcom%s\n", par->com);
                // printf("this is pararg%s\n", par->arg[cnt - 1]);
            } 
            // if (cnt == 2)
            // {
            //     strcat(par->arg, token);
            // }
            if (cnt >= 2)
            {
                //strcat(par->arg, " ");
                // par->arg[cnt-1] = malloc(CMDLINE_MAX * sizeof(char*));
                strcpy(par->arg[cnt- 1], token);
                strcpy(par->dir, token);
                // printf("this is parcom%s\n", par->com);
                // printf("this is pararg%s\n", par->arg[cnt - 1]);
            }

            token = strtok(NULL, " ");
        }
        par->arg[cnt] = NULL;  
}

void caret_parser(struct myparse * par, char command[CMDLINE_MAX]){
        // printf("Aaad");
        par->do_caret = 0;
        if(strchr(command,'>') != NULL){
                // printf("ADA\n");
                par->do_caret = 1;
        }
        //printf("Cmd: %s\n", command);
        char *strtoken = strtok(command, ">");         
        char first_token[CMDLINE_MAX];
        int count = 0;

        while(strtoken != NULL){
                if(count == 0){
                        strcpy(first_token,strtoken);
                        
                }
                else{
                        secondtokenparser(par, strtoken);
                }
                strtoken = strtok(NULL, ">");
                ++count;
        }
        parser(par, first_token);
        // return first_token;
}




void mycd(char argument[CMDLINE_MAX], char comline[CMDLINE_MAX])
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
        p1->arg = (char**) malloc(sizeof(char*) * (ARGS_LIMIT));
        while (1) { 
                char *nl;
                int retval;
                int fd;
                // char firtok[CMDLINE_MAX];
                for(unsigned i = 0; i < ARGS_LIMIT; i++)
                    p1->arg[i] = (char*) malloc(sizeof(char) * (CMDLINE_MAX));
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
                        for(unsigned i = 0; i < ARGS_LIMIT ; i++)
                            free(p1->arg[i]);
                        fprintf(stderr, "Bye...\n");
                        break;
                }
                strcpy(p1->firstcmd, cmd);
                // strcpy(firtok,caret_parser(p1, cmd));
                caret_parser(p1, cmd);
                if (!strcmp(p1->com, "cd")){
                        for(unsigned i = 0; i < ARGS_LIMIT ; i++)
                            free(p1->arg[i]);
                        mycd(p1->dir, p1->com);
                        continue;
                }
                /* Regular command */
                pid_t pid = fork();
                /*char *args[] = {cmd, NULL};*/
                
                        
                
                if (pid == 0) {
                /* Child */
                    if(p1->do_caret){
                        //printf("%s\n", p1->file);
                        fd = open(p1->file, O_WRONLY | O_CREAT, 0644);
                        dup2(fd, STDOUT_FILENO);
                        close(fd);
                    }
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
                        p1->firstcmd, retval);
                // free(p1);

                for(unsigned i = 0; i < ARGS_LIMIT ; i++)
                    free(p1->arg[i]);
            }
            free(p1->arg);
            // free(p1->com);
            // free(p1->dir);
            free(p1);        
                
        return EXIT_SUCCESS;
}
