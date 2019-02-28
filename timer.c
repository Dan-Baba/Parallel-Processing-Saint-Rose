#include <stdio.h>
#include <sys/time.h>

double mytime();

int main() {
  struct timeval t1, t2;
  double elapsedTime;
  double t2secs;
  double t1secs;

  //gettimeofday(&t1, NULL);
  t1secs = mytime();

  sleep(1);

  //gettimeofday(&t2, NULL);
  t2secs = mytime();
  
  //t2secs = t2.tv_sec + (t2.tv_usec / 1000000.0);
  //t1secs = t1.tv_sec + (t1.tv_usec / 1000000.0);

  elapsedTime = t2secs - t1secs;
  //elapsedTime = (t2.tv_sec + (t2.tv_usec / 1000000.0)) -
  //  (t1.tv_sec + (t1.tv_usec / 1000000.0));

  printf("Elapsed Time: %f\n", elapsedTime);
  return 0;
}


double mytime() {
  struct timeval t1;

  gettimeofday(&t1,NULL);

  return t1.tv_sec + t1.tv_usec/1000000.0;
}
