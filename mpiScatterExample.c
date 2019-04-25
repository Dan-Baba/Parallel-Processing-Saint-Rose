#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int numtasks, rank, dest, source, rc, count, tag=1;
  int sendBuf[4];
  int recvBuf = 0;
  for (int i = 0; i < 4; i++) {
    sendBuf[i] = i+1;
  }

  MPI_Status Stat;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Scatter(sendBuf, 1, MPI_INT, &recvBuf, 1, MPI_INT, 0, MPI_COMM_WORLD);

  printf("Rank %d received %d\n", rank, recvBuf);
  MPI_Finalize();
}