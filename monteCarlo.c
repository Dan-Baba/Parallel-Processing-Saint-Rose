#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

#define NUM_POINTS 1500000000
#define NUM_THREADS 12

long numHits[NUM_THREADS];

void *throwDarts(void *id);
double mytime();
int main() {
  // unsigned int seed = time(NULL);
  // double randomNum = (double)rand_r(&seed) / RAND_MAX;
  // printf("%f\n", randomNum);
  double start = mytime();
  pthread_t threads[NUM_THREADS];

  // Throw all of our darts.
  for (long i = 0; i < NUM_THREADS; i++) {
    pthread_create(&threads[i], NULL, throwDarts, (void *)i);
  }

  // Collect results
  long totalHits = 0;
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
    totalHits += numHits[i];
  }

  double piEstimation = ((double)totalHits / (double)NUM_POINTS) * 4.0;
  printf("After throwing %d darts, we have %ld hits.\n", NUM_POINTS, totalHits);
  printf("Estimation of PI: %f\n", piEstimation);
  double end = mytime();
  double timeTaken = end - start;
  printf("Total time taken: %f\n", timeTaken);
  return 0;
}

void *throwDarts(void *id) {
  int tid = (unsigned int)id;
  int throws = NUM_POINTS / NUM_THREADS;
  if (NUM_POINTS % NUM_THREADS > tid)
    throws++;
  printf("Thread #%d: %d throws.\n", tid, throws);

  long hits = 0;
  // Generating a seed that's unique this this thread.
  unsigned int seed = time(NULL) * tid;
  for (int i = 0; i < throws; i++) {
    double x = (double)rand_r(&seed) / RAND_MAX;
    double y = (double)rand_r(&seed) / RAND_MAX;
    if (((x * x) + (y * y)) <= 1.0) {
      hits++;
    }
  }

  numHits[tid] = hits;
  pthread_exit(NULL);
}

double mytime() {
  struct timeval t1;

  gettimeofday(&t1,NULL);

  return t1.tv_sec + t1.tv_usec/1000000.0;
}