#include <pthread.h>
#include <stdio.h>

void *print_message(void *thread_id) {
    printf("Thread %d is running\n", *(int *)thread_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    int id = 1;
    pthread_create(&thread, NULL, print_message, (void *)&id);
    pthread_join(thread, NULL);
    return 0;
}
