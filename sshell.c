// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <stdbool.h>
// #include <fcntl.h>

// #define CMDLINE_MAX 512
// #define ARGS_LIMIT 16

// struct myparse{
//     char **arg;
//     char com[CMDLINE_MAX]; 
//     char dir[CMDLINE_MAX];
//     char firstcmd[CMDLINE_MAX];
//     char file[CMDLINE_MAX];
//     int do_caret;
//     int count_pipes;
// };

// void secondtokenparser(struct myparse * par, char secondtoken[CMDLINE_MAX]){
//         char *strtoken = strtok(secondtoken, " ");
//         while(strtoken != NULL){
//                 printf("Strtoken: %s\n",strtoken);
//                 strcpy(par->file, strtoken);
//                 strtoken = strtok(NULL, " ");
//         }
// }

// void parser(struct myparse *par, char command[CMDLINE_MAX]){
//         char *token = strtok(command, " ");
//         int cnt = 0;
//         while (token != NULL)
//         {
//             cnt++;
//             if (cnt == 1)
//             {   
//                 strcpy(par->com, token);
//                 strcpy(par->arg[cnt - 1], token);
//             } 
//             if (cnt >= 2)
//             {
//                 strcpy(par->arg[cnt- 1], token);
//                 strcpy(par->dir, token);
//             }

//             token = strtok(NULL, " ");
//         }
//         par->arg[cnt] = NULL;  
// }

// void caret_parser(struct myparse * par, char command[CMDLINE_MAX]){
//         par->do_caret = 0;
//         par->count_pipes = 0;

//         if(strchr(command,'>') != NULL){
//                 par->do_caret = 1;
//         }

//         char *strtoken = strtok(command, ">");         
//         char first_token[CMDLINE_MAX];
//         int count = 0;

//         while(strtoken != NULL){
//                 if(count == 0){
//                         strcpy(first_token,strtoken); 
//                 }
//                 else{
//                         secondtokenparser(par, strtoken);
//                 }
//                 strtoken = strtok(NULL, ">");
//                 ++count;
//         }
//         parser(par, first_token);
// }

// void pipeparser(struct myparse *par, struct myparse *par2, char command[CMDLINE_MAX]){
//         char *token = strtok(command, "|");
//         int count = 0;
//         while (token != NULL){

//             if( count == 0){
//                 printf("Token: %s\n", token);
//                 caret_parser(par, token);
//             } else{
//                 caret_parser(par2,token);
//             }
//                 token = strtok(NULL, "|");
//             count++;
            
//         } 
// }

// void mycd(char argument[CMDLINE_MAX], char comline[CMDLINE_MAX])
// {
    
//     if (chdir(argument) != 0)
//     {
//         printf("Error: cannot cd into directory\n");
//         printf("+ completed '%s' [1]\n", comline);
//     }
//     else
//     {
//         printf("+ completed '%s' [0]\n", comline);
//     }
// }

// int main(void){

//         struct myparse *p1 = (struct myparse *) malloc(sizeof(struct myparse));
//         char cmd[CMDLINE_MAX];
//         p[q].arg = (char**) malloc(sizeof(char*) * (ARGS_LIMIT));
//         while (1) { 
//                 char *nl;
//                 int retval;
//                 int fd;
//                 for(unsigned i = 0; i < ARGS_LIMIT; i++)
//                     p[q].arg[i] = (char*) malloc(sizeof(char) * (CMDLINE_MAX));
//                 /* Print prompt */
//                 printf("sshell@ucd$ ");
//                 fflush(stdout);

//                 /* Get command line */
//                 fgets(cmd, CMDLINE_MAX, stdin);

//                 /* Print command line if stdin is not provided by terminal */
//                 if (!isatty(STDIN_FILENO)) {
//                         printf("%s", cmd);
//                         fflush(stdout);
//                 }

//                 /* Remove trailing newline from command line */
//                 nl = strchr(cmd, '\n');
//                 if (nl)
//                         *nl = '\0';

//                 /* Builtin command */
//                 if (!strcmp(cmd, "exit")) {
//                         for(unsigned i = 0; i < ARGS_LIMIT ; i++)
//                             free(p[q].arg[i]);
//                         free(p[q].arg);
//                         fprintf(stderr, "Bye...\n");
//                         break;
//                 }
//                 strcpy(p[q].firstcmd, cmd);

//                 //Count the # of pipes
//                 if(strchr(cmd, '|') != NULL){
//                         struct myparse *p2 = (struct myparse *) malloc(sizeof(struct myparse));
//                         p2->arg = (char**) malloc(sizeof(char*) * (ARGS_LIMIT));
//                         for(unsigned i = 0; i < ARGS_LIMIT; i++)
//                                 p2->arg[i] = (char*) malloc(sizeof(char) * (CMDLINE_MAX));
//                         pipeparser
//                         p[q].count_pipes++;
//                 }
                
//                 //Checks for either using pipe parser or caret_parser
//                 // if(p[q].count_pipes){
//                 //         pipeparser(p1, cmd);
//                 // }
//                 // else{
//                 //         caret_parser(p1,cmd);
//                 // }
                        
//                 if (!strcmp(p[q].com, "cd")){
//                         for(unsigned i = 0; i < ARGS_LIMIT ; i++)
//                             free(p[q].arg[i]);
//                         mycd(p[q].dir, p[q].com);
//                         continue;
//                 }
//                 /* Regular command */
//                 // for(int = 0; i < p[q].count_pipes + 1; i++){
//                         pid_t pid = fork();

//                         
                
//                         if (pid == 0) {
//                         /* Child */
//                         if(p[q].do_caret){
//                                 //printf("%s\n", p[q].file);
//                                 fd = open(p[q].file, O_WRONLY | O_CREAT, 0644);
//                                 dup2(fd, STDOUT_FILENO);
//                                 close(fd);
//                         }
//                         // if(p[q].count_pipes){
//                         //         close(n_pipes[1]);
//                         //         dup2(n_pipes[0], STDIN_FILENO);
//                         //         close(n_pipes[0]);
//                         //         //need to work the execvp
//                         // }        
//                                 execvp(p[q].com,p[q].arg);
//                                 perror("execv");
//                                 exit(1);
//                         } else if (pid > 0) {
//                         /* Parent */
//                         // if(p[q].count_pipes){
//                         //         close(n_pipes[0]);
//                         //         dup2(n_pipes[1], STDOUT_FILENO);
//                         //         close(n_pipes[1]);
//                         //         //need to work on execvp
//                         //         //execvp();
//                         // }
//                         waitpid(pid, &retval, 0);
                        
//                         // printf("Child returned %d\n",
//                         // WEXITSTATUS(status));
//                         } else {
//                                 perror("fork");
//                                 exit(1);
//                         }
//                 // }
//                 // retval = system(cmd);
//                 fprintf(stderr, "+ completed '%s' [%d]\n",
//                         p[q].firstcmd, retval);
//                 // free(p1);

//                 for(unsigned i = 0; i < ARGS_LIMIT ; i++)
//                     free(p[q].arg[i]);
//             }
//             free(p[q].arg);
//             // free(p[q].com);
//             // free(p[q].dir);
//             free(p1);        
                
//         return EXIT_SUCCESS;
// }

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
                //printf("Strtoken: %s\n",strtoken);
                strcpy(par->file, strtoken);
                strtoken = strtok(NULL, " ");
        }
}

void parser(struct myparse * par, char command[CMDLINE_MAX]){
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
        char store_args[ARGS_LIMIT][CMDLINE_MAX];
        char *strtoken = strtok(command, ">");
        //char * first_token = malloc(sizeof(char) * CMDLINE_MAX);         
        //char first_token[CMDLINE_MAX];
        // char* first_token;
        int count = 0;
        
        while(strtoken != NULL){
            strcpy(store_args[count],strtoken); 
            strtoken = strtok(NULL, ">");
            ++count;
        }

        for(int i = 0; i < count; i++){
            if(i == 0){
                parser(par, store_args[i]);
            }
            else{
                secondtokenparser(par,store_args[i]);
            }
        }
}

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
        
        struct myparse p[4];
        char cmd[CMDLINE_MAX];
        char copy_cmd[CMDLINE_MAX];
        int st_pid[4];
        int status;
        // int st_status[4]; 

        
        while (1) { 
                char *nl;
                //int retval = 0;
                int fd;
                int n_pipes[2];         
                int count_pipes = 0;
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
                    
                    // for(int i = 0; i <= count_pipes ; i++){
                    //     for(int j = 0; j < ARGS_LIMIT; j++)
                    //         free(p[i].arg[j]);
                    //     free(p[i].arg);
                    // }
                    
                    fprintf(stderr, "Bye...\n");
                    break;
                }
                strcpy(copy_cmd, cmd);

                for(unsigned i = 0; cmd[i] != '\0'; i++){
                    if(cmd[i] == '|')
                        count_pipes++;
                    //printf("Pipes: %d\n", count_pipes);
                }

                for(int i = 0; i <= count_pipes; i++){
                    
                    // struct myparse * s;
                    // s = &p[i];
                    // s = malloc(sizeof(struct myparse));
                    p[i].arg = (char**) malloc(sizeof(char*) * (ARGS_LIMIT));
                    for(unsigned j = 0; j < ARGS_LIMIT; j++)
                        p[i].arg[j] = (char*) malloc(sizeof(char) * (CMDLINE_MAX));
                
                }

                pipeparser(p, cmd, count_pipes);

                if(count_pipes){
                        pipe(n_pipes);
                    }

                for(int q = 0; q <= count_pipes; q++){  

                    if (!strcmp(p[q].com, "cd")){
                        mycd(p[q].dir, p[q].com);
                        // for(int i = 0; i <= count_pipes ; i++){
                        //     for(int j = 0; j < ARGS_LIMIT; j++)
                        //         free(p[i].arg[j]);
                        //     free(p[i].arg);
                        // }
                        continue;
                    }

                    pid_t pid = fork();
                    
                    if (pid == 0) {
                    /* Child */
                    
                        if(p[q].do_caret){
                            //printf("%s\n", p[q].file);
                            fd = open(p[q].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
                            else if (q == count_pipes){
                                close(n_pipes[1]);
                                dup2(n_pipes[0], STDIN_FILENO);
                                close(n_pipes[0]);  
                            }
                            else{
                                close(n_pipes[1]);
                                dup2(n_pipes[0], STDIN_FILENO);
                                close(n_pipes[0]);
                                dup2(n_pipes[1], STDOUT_FILENO);
                                // close(n_pipes[0]);
                                close(n_pipes[1]);
                                
                            }
                        }
                        
                        execvp(p[q].com,p[q].arg);
                        // execvp(p[q].com,p[q].arg);
                        perror("Error");
                        exit(1);
                        
                    
                    } 
                    else if (pid > 0) {
                    /* Parent */
                        
                        // if(count_pipes){
                        //     if(q == 0){
                        //         close(n_pipes[1]);
                        //         dup2(n_pipes[0], STDIN_FILENO);
                        //         close(n_pipes[0]);
                                
                        //     }
                        //     else if (q == count_pipes){
                        //         close(n_pipes[0]);
                        //         dup2(n_pipes[1], STDOUT_FILENO);
                        //         close(n_pipes[1]);  
                                

                        //     }
                        //     else{
                        //         close(n_pipes[0]);
                        //         dup2(n_pipes[1], STDIN_FILENO);
                        //         close(n_pipes[1]);
                        //         dup2(n_pipes[0], STDOUT_FILENO);
                        //         // close(n_pipes[0]);
                        //         close(n_pipes[0]);
                                
                        //     }
                        // }

                    } 
                    else {
                        perror("fork");
                        exit(1);
                    }
                    st_pid[q] = pid;
                    
                    
                    //     st_status[q] = wait(&status);
                    // waitpid(pid, &retval, 0)
                   //execvp(p[q + 1].com,p[q + 1].arg);
                }
                if(count_pipes){
                        close(n_pipes[0]);
                        close(n_pipes[1]);
                }
                // close(n_pipes[1]);
                // close(n_pipes[0]);
                
                for(int i = 0; i <= count_pipes; i++){
                        waitpid(st_pid[i], &status, 0);

                }
                

                fprintf(stderr, "+ completed '%s' [%d]\n",
                        copy_cmd, 0);
                
                

                for(int i = 0; i <= count_pipes ; i++){
                    for(int j = 0; j < ARGS_LIMIT; j++)
                        free(p[i].arg[j]);
                    free(p[i].arg);
                }


            }
                   
                
        return EXIT_SUCCESS;
}