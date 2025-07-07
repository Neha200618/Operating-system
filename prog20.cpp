#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;
pthread_mutex_t mutex;
int readers = 0;

void* reader(void* arg) {
    pthread_mutex_lock(&mutex);
    readers++;
    if (readers == 1)
        sem_wait(&wrt);
    pthread_mutex_unlock(&mutex);

    printf("Reader %d is reading...\n", *(int*)arg);
    sleep(1);
    printf("Reader %d is done reading.\n", *(int*)arg);

    pthread_mutex_lock(&mutex);
    readers--;
    if (readers == 0)
        sem_post(&wrt);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* writer(void* arg) {
    sem_wait(&wrt);
    printf("Writer %d is writing...\n", *(int*)arg);
    sleep(2);
    printf("Writer %d is done writing.\n", *(int*)arg);
    sem_post(&wrt);
    return NULL;
}

int main() {
    pthread_t r[3], w[2];
    int r_id[3] = {1, 2, 3}, w_id[2] = {1, 2};

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 3; i++)
        pthread_create(&r[i], NULL, reader, &r_id[i]);
    for (int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &w_id[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);

    return 0;
}

