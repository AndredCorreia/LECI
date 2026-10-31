#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <libgen.h>

#include "hdp.h"
#include "dbc.h"
#include "utils.h"

int main() 
{
    // (a) Ask the user for a value between 10 and 20, validating the value inserted
    int initial_val = 0;
    while (true) 
    {
        printf("Enter a starting value between 10 and 20: ");
        if (scanf("%d", &initial_val) != 1) 
        {
            while (getchar() != '\n');
            printf("Invalid input. Please enter an integer.\n");
            continue;
        }
        if (initial_val >= 10 && initial_val <= 20) 
        {
            break;
        }
        printf("Error: Value must be between 10 and 20. Try again.\n");
    }

    // Create an integer variable in shared memory and start it with the value read
    int shmid = MO(shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0600));
    int *counter = (int *)MOP(shmat(shmid, NULL, 0));
    *counter = initial_val;

    // Create the semaphores required to synchronize the activity of the two child processes (2 semaphores)
    int semid = MO(semget(IPC_PRIVATE, 2, IPC_CREAT | 0600));

    // Initialize the semaphores: Child 0 starts with turn = 1, Child 1 waits with turn = 0
    MO(semctl(semid, 0, SETVAL, 1));
    MO(semctl(semid, 1, SETVAL, 0));

    // Launch two child processes
    pid_t cpid[2];
    for (int i = 0; i < 2; i++) 
    {
        if ((cpid[i] = MO(fork())) == 0) 
        {
            // ==================== CHILD PROCESS ====================
            int id = i;
            int next_id = 1 - id;

            while (true) 
            {
                // Wait until it is its turn to decrement
                struct sembuf sop_wait = {(unsigned short)id, -1, 0};
                MO(semop(semid, &sop_wait, 1));

                // Terminate if the value in the shared variable is 1
                if (*counter == 1) 
                {
                    // Signal the other child before terminating so it can also exit if needed
                    struct sembuf sop_signal = {(unsigned short)next_id, 1, 0};
                    semop(semid, &sop_signal, 1);
                    break;
                }

                // Decrement the counter
                (*counter)--;

                // Print the value saying who made the decrement (PID)
                printf("Child PID %d (Index %d) decremented counter to %d\n", getpid(), id, *counter);

                // Terminate if value is 1
                if (*counter == 1) 
                {
                    // Signal the other child so it can wake up and terminate gracefully
                    struct sembuf sop_signal = {(unsigned short)next_id, 1, 0};
                    semop(semid, &sop_signal, 1);
                    break;
                }

                // Otherwise, signal the other child's turn and repeat
                struct sembuf sop_signal = {(unsigned short)next_id, 1, 0};
                MO(semop(semid, &sop_signal, 1));
            }

            // Detach shared memory and terminate child
            MO(shmdt(counter));
            exit(EXIT_SUCCESS);
        }
    }

    // Wait until both child processes terminate
    for (int i = 0; i < 2; i++) 
    {
        MO(waitpid(cpid[i], NULL, 0));
        printf("Child process %u finished\n", i+1);
    }

    // Release the shared memory and the semaphores and terminate
    MO(shmdt(counter));
    MO(shmctl(shmid, IPC_RMID, NULL));
    MO(semctl(semid, 0, IPC_RMID));

    printf("All resources released successfully. Program exiting.\n");
    return 0;
}