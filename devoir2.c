//Phuong Thao Phan
// 300319057

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
        printf("Thread 0: b = %d\n", b);
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
        printf("Thread 1: b = %d\n", b);
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
        printf("Thread 2: b = %d\n", b);
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
        printf("Thread 3: b = %d\n", b);
        turn = 0; // Loop back to the first thread
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

// Fibonacci function
void fibonacci(int n) {
    int v1 = 1, v2 = 1, v3;
    printf("Suite de Fibonacci pour %d: ", n);
    if (n <= 1) {
        printf("%d\n", v1);
        return;
    }

    printf("%d %d ", v1, v2);
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
        printf("Entrez une valeur nulle ou positive pour a: ");
        scanf("%d", &a);
    } while (a < 0);

    do {
        printf("Entrez une valeur nulle ou positive pour b: ");
        scanf("%d", &b);
    } while (b < 0);

    do {
        printf("Entrez une valeur pour turn (0 à 3): ");
        scanf("%d", &turn);
    } while (turn < 0 || turn > 3);

    printf("Valeurs valides saisies: a = %d, b = %d, turn = %d\n", a, b, turn);

    // Convert `a` to total iterations (a full RR cycle has 4 threads)
    a *= 4;

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

    // Main thread continues execution
    printf("Parent: b final = %d\n", b);
    fibonacci(b);

    // Destroy mutex
    pthread_mutex_destroy(&lock);

    return 0;
}

