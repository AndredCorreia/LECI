#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

int main() {
    // Create shared memory for an integer counter using anonymous mmap (shared between processes)
    int *counter = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (counter == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }

    // Initialize shared variable to 1
    *counter = 1;

    // Launch child process
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // ==================== CHILD PROCESS ====================
        int target = 0;

        // Ask user for a value between 10 and 20 with validation
        while (true) {
            printf("Child process: Enter a value between 10 and 20: ");
            if (scanf("%d", &target) != 1) {
                while (getchar() != '\n'); // clear input buffer on invalid input
                printf("Invalid input. Please enter an integer.\n");
                continue;
            }
            if (target >= 10 && target <= 20) {
                break;
            }
            printf("Error: Value must be between 10 and 20. Try again.\n");
        }

        // Increment the shared variable until it reaches the target value
        while (*counter < target) {
            (*counter)++;
            printf("Child incremented counter: %d\n", *counter);
        }

        exit(EXIT_SUCCESS);
    } else {
        // ==================== PARENT PROCESS ====================
        
        // Wait until the child process terminates
        wait(NULL);

        printf("\n--- Child process finished. Parent starting decrement phase ---\n");

        // Decrement the shared variable until it reaches 1, printing at every iteration
        while (*counter > 1) {
            printf("Parent decremented counter: %d\n", *counter);
            (*counter)--;
        }

        printf("Final counter value: %d\n", *counter);

        // Release shared memory
        munmap(counter, sizeof(int));
    }

    return 0;
}