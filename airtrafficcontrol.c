#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define NUM_THREADS 20
#define CONTROL_TIMES 100
#define CONTROL_SLEEP_TIME 10

int clearances_remaining = 5;
pthread_mutex_t clearance_mutex;
pthread_cond_t clearance_cv;

void *Plane(void *threadid) {
  long tid;
  tid= (long)threadid;
  // Generating a seed that's unique to this thread.
  unsigned int seed = time(NULL) * tid;

  // Generate random number between 1 - 10.
  int leg = (rand_r(&seed) % 10) + 1;
    


    for (int i = 0; i < leg; i++) {
        pthread_mutex_lock(&clearance_mutex);

        while (true) {
            if (clearances_remaining > 0) {
                clearances_remaining--;
                // TODO: figure out flight-time
                printf("Thread #%ld, leg #%d, flight-time\n", tid, (i + 1));
                break;
            } else {
                //printf("Thread #%ld waiting for broadcast\n", tid, (i + 1));
                pthread_cond_wait(&clearance_cv, &clearance_mutex);
                //printf("Thread #%ld waking up\n", tid, (i + 1));
            }
        }
        //printf("Thread #%ld releasing lock\n", tid, (i + 1));
        pthread_mutex_unlock(&clearance_mutex);
        // Generate random number between 1 - 3 and sleep.
        int sleep_time = (rand_r(&seed) % 3) + 1;
        sleep(sleep_time);
    }

    printf("Thread #%ld finished!\n", tid);
    pthread_exit(NULL);
}

void *Control(void *threadid) {
    for (int i = 0; i < CONTROL_TIMES; i++) {
        pthread_mutex_lock(&clearance_mutex);
        if (clearances_remaining <= 0) {
            clearances_remaining += 5;
            pthread_cond_broadcast(&clearance_cv);
            // TODO: Is this what's meant by print signaled condition variable?
            printf("Control making clearance\n");
        }
        pthread_mutex_unlock(&clearance_mutex);
        //printf("Control sleeping\n");
        sleep(CONTROL_SLEEP_TIME);
        //printf("Control waking up\n");
    }

    printf("Control exiting...\n");
    pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    pthread_mutex_init(&clearance_mutex, NULL);
    pthread_cond_init(&clearance_cv, NULL);

    pthread_t threads[NUM_THREADS];
    long t;
    for (t = 0; t < NUM_THREADS - 1; t++) {
        pthread_create(&threads[t], NULL, Plane, (void *)t);
    }

    pthread_create(&threads[t], NULL, Control, (void *)t);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&clearance_mutex);
    pthread_cond_destroy(&clearance_cv);
    pthread_exit(NULL);
}