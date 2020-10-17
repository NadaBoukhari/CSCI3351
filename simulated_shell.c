#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
    char num[100];
    char tokens[20][100];
    char cwd[PATH_MAX];
    int status;
    char *pointer = num;
    int i = 0;
    pid_t pid;

    while (1)
    {
        pid = fork();

        if (pid != 0)
        {
            waitpid(pid, &status, 0);
        }
        else
        {

            getcwd(cwd, sizeof(cwd));
            printf("%s$ ", cwd);
            fgets(num, 100, stdin);

            for (pointer = strtok(num, " "); pointer; pointer = strtok(NULL, " \n"))
            {
                strcpy(tokens[i], pointer);
                i++;
            }

            if (strncmp(tokens[0], "ls", 2) == 0)
            {
                execl("/bin/ls", "ls", NULL);
            }
            else if (strncmp(tokens[0], "ps", 2) == 0)
            {
                execl("/bin/ps", "ps", NULL);
            }
            else if (strncmp(tokens[0], "pwd", 3) == 0)
            {
                execl("/bin/pwd", "pwd", NULL);
            }
            else if (strncmp(tokens[0], "q", 1) == 0)
            {
                exit(0);
            }
        }
        i = 0;
    }

    return 0;
}