#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


int lock = 0;
int mails = 0;
//p_thread_mutex_t mutex;

void *routine()
{
    printf("Test from threads\n");

}

int main (int argc, char **argv)
{
    pthread_t t1;
    pthread_create(&t1, NULL, &routine, NULL);
    pthread_join(t1, NULL);


    return (0);
}

/* #include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock;
int counter = 0;

void *incrementCounter(void *arg) {
    pthread_mutex_lock(&lock);
    counter++;
    printf("Counter value: %d\n", counter);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&thread1, NULL, incrementCounter, NULL);
    pthread_create(&thread2, NULL, incrementCounter, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock);
    return 0;
} */
