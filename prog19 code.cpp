#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;

void* process(void* arg) {
    pthread_mutex_lock(&lock);
    printf("Process %d is in critical section.\n", *(int*)arg);
    sleep(1);
    printf("Process %d is leaving critical section.\n", *(int*)arg);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t threads[2];
    int id[2] = {1, 2};

    pthread_mutex_init(&lock, NULL);

    for(int i = 0; i < 2; i++)
        pthread_create(&threads[i], NULL, process, &id[i]);

    for(int i = 0; i < 2; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}

