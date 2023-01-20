#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CMDLINE_MAX 512

struct command
{
    char** val; 
};


int main(void)
{
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

                /* Regular command */
                pid_t pid = fork();
                char *args[] = {cmd, NULL};
                
                if (pid == 0) {
                /* Child */
                    execvp(cmd,args);
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