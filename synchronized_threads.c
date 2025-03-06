#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// Global shared variables
int a, b, turn;
pthread_mutex_t lock;

// Function to generate Fibonacci sequence
void print_fibonacci(int num) {
    int first = 1, second = 1, next;
    printf("Fibonacci sequence up to %d: ", num);
    if (num == 1) {
        printf("%d\n", first);
        return;
    }
    printf("%d %d", first, second);
    for (int i = 2; i < num; i++) {
        next = first + second;
        printf(" %d", next);
        first = second;
        second = next;
    }
    printf("\n");
}

// Thread function
void *thread_function(void *arg) {
    int thread_id = *(int *)arg;

    for (int i = 0; i < a; i++) {  // Loop a times in Round Robin order
        while (turn != thread_id); // Busy waiting

        pthread_mutex_lock(&lock); // Ensure only one thread enters CS
        switch (thread_id) {
            case 0: b += 1; break;
            case 1: b += 2; break;
            case 2: b += 3; break;
            case 3: b += 4; break;
        }
        printf("Thread %d updated b to %d\n", thread_id, b);
        turn = (turn + 1) % 4;  // Move turn to the next thread
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

int main() {
    // Get user input
    printf("Enter values for a, b, and turn (0-3): ");
    scanf("%d %d %d", &a, &b, &turn);

    if (turn < 0 || turn > 3) {
        printf("Invalid turn value! Must be between 0 and 3.\n");
        return 1;
    }

    pthread_t threads[4];
    int thread_ids[4] = {0, 1, 2, 3};
    pthread_mutex_init(&lock, NULL); // Initialize mutex

    // Create threads
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_function, (void *)&thread_ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print final value of b and its Fibonacci sequence
    printf("Parent: Final value of b is %d\n", b);
    print_fibonacci(b);

    pthread_mutex_destroy(&lock); // Clean up mutex
    return 0;
}
