//Phuong Thao Phan
//300319057
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Global variables
int a, b, turn;
pthread_mutex_t lock; // Mutex for mutual exclusion

// Thread functions with busy waiting
void *th0(void *arg) {
    for (int i = 0; i < a; i++) {
        while (turn != 0); // Busy wait until it's thread 0's turn

        pthread_mutex_lock(&lock);
        b += 1;
        printf("Thr0, (b+1=%d)\n", b);
        turn = 1; // Set the next thread to execute
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

void *th1(void *arg) {
    for (int i = 0; i < a; i++) {
        while (turn != 1); // Busy wait

        pthread_mutex_lock(&lock);
        b += 2;
        printf("Thr1, (b+2=%d)\n", b);
        turn = 2;
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

void *th2(void *arg) {
    for (int i = 0; i < a; i++) {
        while (turn != 2); // Busy wait

        pthread_mutex_lock(&lock);
        b += 3;
        printf("Thr2, (b+3=%d)\n", b);
        turn = 3;
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

void *th3(void *arg) {
    for (int i = 0; i < a; i++) {
        while (turn != 3); // Busy wait

        pthread_mutex_lock(&lock);
        b += 4;
        printf("Thr3, (b+4=%d)\n", b);
        turn = 0; // Loop back to the first thread
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

// Fibonacci function
void fibonacci(int n) {
    int v1 = 1, v2 = 1, v3;
    printf("\nThe Fibonacci sequence for %d is:\n", n);
    printf("1 ");
    if (n == 1) {
        printf("\n");
        return;
    }
    printf("1 ");

    for (int i = 2; i < n; i++) {
        v3 = v1 + v2;
        v1 = v2;
        v2 = v3;
        printf("%d ", v3);
    }
    printf("\n");
}

int main() {
    // Validate input
    do {
        printf("Enter integer a value: ");
        scanf("%d", &a);
    } while (a < 0);

    do {
        printf("Enter integer b value: ");
        scanf("%d", &b);
    } while (b < 0);

    do {
        printf("Enter the Thread # to start first (0 to 3): ");
        scanf("%d", &turn);
    } while (turn < 0 || turn > 3);

    printf("\n");


    // Initialize mutex
    pthread_mutex_init(&lock, NULL);

    // Create threads
    pthread_t t0, t1, t2, t3;
    pthread_create(&t0, NULL, th0, NULL);
    pthread_create(&t1, NULL, th1, NULL);
    pthread_create(&t2, NULL, th2, NULL);
    pthread_create(&t3, NULL, th3, NULL);

    // Wait for all threads to finish (join)
    pthread_join(t0, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    // Main thread prints final b and computes Fibonacci
    printf("Parent, (b=%d)\n", b);
    fibonacci(b);

    // Destroy mutex
    pthread_mutex_destroy(&lock);

    return 0;
}

