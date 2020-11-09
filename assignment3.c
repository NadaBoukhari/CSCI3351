
//******************* to run type 'gcc assignment3.c -o m -pthread' then run using ./m 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

struct args
{
    int parentNumber;
    int threadNumber;
    int PID;
};

void *printThreadID(void *input)
{
    int k;
    //for (k = 0; k < 1000; k++)
    //{
        printf("\tI am a thread [%d] %d.%d\n", ((struct args *)input)->PID, ((struct args *)input)->parentNumber, ((struct args *)input)->threadNumber);
        // pthread_exit(NULL);
    //}
}

void callNonSynchronizedThreads()
{
    int i, pid, parentID;
    struct args *Info = (struct args *)malloc(sizeof(struct args));
    for (i = 0; i < 3; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            parentID = getpid();
            printf("I am process %d\n", parentID);
        }
        else if (pid == -1)
        {
            printf("Error while forking child.");
            return;
        }
        else
        {
            pthread_t tids[3];
            int vals[3];
            int j, l;
            Info->PID = getpid();
            Info->parentNumber = i + 1;

            for (j = 0; j < 3; j++)
            {
                vals[j] = j;

                Info->threadNumber = j + 1;
                pthread_create(tids + j, NULL, printThreadID, (void *)Info);
                pthread_join(tids[j], NULL);
            }

            wait(NULL);
            exit(0);

            return;
        }
    }
    return;
}

void callSynchronizedThreads()
{
    printf("void");
}

void menu()
{
    char menuChoice;
    do
    {
        printf("\n1. Without synchronization\n");
        printf("2. With synchronization\n");
        printf("3. Exit\n");
        scanf("%s", &menuChoice);

        switch (menuChoice)
        {
        case '1':
            callNonSynchronizedThreads();
            break;
        case '2':
            callSynchronizedThreads();
            break;
        case '3':
            printf("\nProgram terminated \n");
            break;
        default:
            printf("Wrong choice. Please choose a number from the menu: ");
            break;
        }

    } while (menuChoice != '3');
    return;
}

int main(void)
{
    menu();
    return (0);
}
