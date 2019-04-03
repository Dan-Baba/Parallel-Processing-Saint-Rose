#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define NUM_THREADS 50
#define CONTROL_TIMES 100
#define CONTROL_SLEEP_TIME 10

int clearances_remaining = 5;
int num_planes = NUM_THREADS - 1;

pthread_mutex_t clearance_mutex;
pthread_mutex_t num_planes_mutex;
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
                break;
            } else {
                printf("Thread #%ld waiting for control to broadcast.\n", tid);
                pthread_cond_wait(&clearance_cv, &clearance_mutex);
            }
        }
        pthread_mutex_unlock(&clearance_mutex);

        // Generate random number between 2 - 5, this is the flight-time.
        int flight_time = (rand_r(&seed) % 4) + 2;
        printf("Thread #%ld, leg #%d, flight-time %d\n", tid, (i + 1), flight_time);
        sleep(flight_time);
        pthread_mutex_lock(&clearance_mutex);
        clearances_remaining++;
        pthread_mutex_unlock(&clearance_mutex);
    }

    pthread_mutex_lock(&num_planes_mutex);
    num_planes--;
    pthread_mutex_unlock(&num_planes_mutex);
    printf("Thread #%ld finished!\n", tid);
    pthread_exit(NULL);
}

// Control actually keeps looping until all airplanes are done.
void *Control(void *threadid) {
    pthread_mutex_lock(&num_planes_mutex);
    while (num_planes > 0) {
        pthread_mutex_unlock(&num_planes_mutex);
        pthread_mutex_lock(&clearance_mutex);
        if (clearances_remaining > 0) {
            pthread_cond_broadcast(&clearance_cv);
            printf("Control announcing %d clearances\n", clearances_remaining);
        }
        pthread_mutex_unlock(&clearance_mutex);
        sleep(CONTROL_SLEEP_TIME);
        pthread_mutex_lock(&num_planes_mutex);
    }
    pthread_mutex_unlock(&num_planes_mutex);
    printf("Control exiting...\n");
    pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    pthread_mutex_init(&clearance_mutex, NULL);
    pthread_mutex_init(&num_planes_mutex, NULL);
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