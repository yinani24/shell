#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define CMDLINE_MAX 512
#define ARGS_LIMIT 16

/*structure where all the command arguments will be stored*/
struct myparse{
    
    char **arg;
    char com[CMDLINE_MAX]; 
    char dir[CMDLINE_MAX];
    char firstcmd[CMDLINE_MAX];
    char file[CMDLINE_MAX];
    char amper[CMDLINE_MAX];
    int do_caret;
    int do_append;

};

/*parser for the file during output redirection*/
void secondtokenparser(struct myparse * par, char secondtoken[CMDLINE_MAX]){
    
    char *strtoken = strtok(secondtoken, " >");
    
    while(strtoken != NULL){
        strcpy(par->file, strtoken);
        strtoken = strtok(NULL, " ");
    }

}

/*parser to separate each command line into arguments, command line and direcotry names in
the instance of the strcture*/
void parser(struct myparse * par, char command[CMDLINE_MAX]){
    
    char *token = strtok(command, " ");
    int cnt = 0;
    while (token != NULL)
    {    
        cnt++;
        if (cnt == 1){   
            strcpy(par->com, token);
            strcpy(par->arg[cnt - 1], token);
        } 
        if (cnt >= 2){
            strcpy(par->arg[cnt- 1], token);
            strcpy(par->dir, token);
        }
        token = strtok(NULL, " ");
    }
    
    par->arg[cnt] = NULL;  

}

/*parser for the checking if the command contains a output redirection symbol and 
pass it to parser function and secondtokenparser*/
void caret_parser(struct myparse * par, char command[CMDLINE_MAX]){
    
    par->do_caret = 0;
    par->do_append = 0;

    if(strstr(command,">>") != NULL){
        par->do_append = 1;
    }
    else if(strchr(command,'>') != NULL){
        par->do_caret = 1;
    }

    char store_args[ARGS_LIMIT][CMDLINE_MAX];
    char *strtoken = strtok(command, ">");
    int count = 0;
    
    while(strtoken != NULL){
        strcpy(store_args[count],strtoken); 
        strtoken = strtok(NULL, ">");
        ++count;
    }

    for(int i = 0; i < count; i++){
        if(i == 0){
            parser(par, store_args[i]);
        }else{
            secondtokenparser(par,store_args[i]);
        }
    }

}

/*parser for separating each command from the pipe and send it to caret_parser*/
void pipeparser(struct myparse par [], char command[CMDLINE_MAX], int count_pipes){
        
    char store_pipe[ARGS_LIMIT][CMDLINE_MAX];
    char *strtoken = strtok(command, "|");
    int count = 0;
    while(strtoken != NULL){
        strcpy(store_pipe[count],strtoken); 
        strtoken = strtok(NULL, "|");
        ++count;
    }

    for(int i = 0; i <= count_pipes; i++){
        caret_parser(&par[i], store_pipe[i]);
    }

}

/*parser for ampersand token and pass it to pipeparser function*/
void ampertokenparser(struct myparse par[], char secondtoken[CMDLINE_MAX], int count_pipes, int * sleep){
        
    if(strchr(secondtoken,'&') != NULL){
        *sleep = 1;
    }

    char store_cmd[CMDLINE_MAX];
    char *strtoken = strtok(secondtoken, "&");

    while(strtoken != NULL){
        strcpy(store_cmd,strtoken); 
        strtoken = strtok(NULL, "&");
    }  

    pipeparser(par, store_cmd, count_pipes);

}

/*to check for cd and then move into directory*/
void mycd(char argument[CMDLINE_MAX])
{
    
    if (chdir(argument) != 0){   
        printf("Error: cannot cd into directory\n");
    }

}

int checker(char argument[CMDLINE_MAX]){

    char *strtoken = strtok(argument, " ");
    int count = 0;
    while(strtoken != NULL){
        count++; 
        strtoken = strtok(NULL, " ");
    }

    return count;

}

int main(void){
        
    struct myparse p[4];
    char cmd[CMDLINE_MAX];
    char copy_cmd[CMDLINE_MAX];
    char sleep_cmd[CMDLINE_MAX];
    int st_pid[4];
    int status;
    int or_status[4];
    int slc = 0;
    int h = 0;
    char error[CMDLINE_MAX];
    // int st_status[4]; 

    while (1) { 
        char *nl;
        int fd;
        int n_pipes[2];         
        int count_pipes = 0;
        int sleep = 0;
        
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
        
        if(nl)
            *nl = '\0';
        
        strcpy(error,cmd);

        if(checker(error) > 16){
            fprintf(stderr, "Error: too many process arguments\n");
            continue;
        }

        /*creates an extra copy of the command*/
        strcpy(copy_cmd, cmd);

        /* Builtin command */
        if (!strcmp(cmd, "exit")) {
            fprintf(stderr, "Bye...\n");
            fprintf(stderr, "+ completed '%s' [%d]\n",
                cmd, 0);
            break;
        }

        /*counts the number of pipes*/
        for(unsigned i = 0; cmd[i] != '\0'; i++){
            if(cmd[i] == '|')
                count_pipes++;
        }

        /*allocates memory for each instance of the struct*/
        for(int i = 0; i <= count_pipes; i++){
            p[i].arg = (char**) malloc(sizeof(char*) * (ARGS_LIMIT));
            for(unsigned j = 0; j < ARGS_LIMIT; j++)
                p[i].arg[j] = (char*) malloc(sizeof(char) * (CMDLINE_MAX));
        }

        ampertokenparser(p, cmd, count_pipes,&sleep);

        /*creates pipes*/
        if(count_pipes){
            pipe(n_pipes);
        }

        /*runs for number of commands present which is equal to count_pipes + 1 or loop from 0 to 
        count_pipes including*/
        for(int q = 0; q <= count_pipes; q++){  

            if (!strcmp(p[q].com, "cd")){
                mycd(p[q].dir);
                continue;
            }

            pid_t pid = fork();
            
            if (pid == 0) {
            /* Child */
            
                if(p[q].do_caret){
                    fd = open(p[q].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                }
                if(p[q].do_append){
                    fd = open(p[q].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                }
                    

                if(count_pipes){
                    close(fd);
                    if(q == 0){
                        close(n_pipes[0]);
                        dup2(n_pipes[1], STDOUT_FILENO);
                        close(n_pipes[1]);
                    }
                    else if(q == count_pipes){
                        close(n_pipes[1]);
                        dup2(n_pipes[0], STDIN_FILENO);
                        close(n_pipes[0]);  
                    }
                    else{
                        close(n_pipes[1]);
                        dup2(n_pipes[0], STDIN_FILENO);
                        close(n_pipes[0]);
                        pipe(n_pipes);
                        close(n_pipes[0]);
                        dup2(n_pipes[1], STDOUT_FILENO);
                        close(n_pipes[1]);
                    }
                }
                
                
                execvp(p[q].com,p[q].arg);
                perror("Error");
                exit(1);

            } 
            else if (pid > 0) {
            /* Parent */

            } 
            else {
                perror("fork");
                exit(1);
            }
            st_pid[q] = pid; 
        }

        /*closing pipes*/
        if(count_pipes){
            close(n_pipes[0]);
            close(n_pipes[1]);
        }

        int j = 0;
        
        /*run for each child and wait for it to get over*/
        for(int i = 0; i <= count_pipes; i++){
            if(sleep == 1){
                slc = 1;
                waitpid(-1, &status, WNOHANG);
                strcpy(sleep_cmd,copy_cmd);
                h = status;
                j++;
            }
            else{
                waitpid(st_pid[i], &or_status[i], 0);
            }   
        }
        
        /*for sleeping*/
        if(j == 1){
            continue;
        }
        if(slc==1){
            fprintf(stderr, "+ completed '%s' [%d]\n",sleep_cmd, h);
            slc = 0;
        }
        
        fprintf(stderr, "+ completed '%s' ", copy_cmd);    
        for(int e = 0; e <= count_pipes ; e++){
            fprintf(stderr, "[%d]", or_status[e]);
        }
        fprintf(stderr, "\n");
        

        for(int i = 0; i <= count_pipes ; i++){
            for(int j = 0; j < ARGS_LIMIT; j++)
                free(p[i].arg[j]);
            free(p[i].arg);
        }

    }
      
    return EXIT_SUCCESS;

}
