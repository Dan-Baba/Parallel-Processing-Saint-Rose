#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int numtasks, rank, dest, source, rc, count, tag=1;
  int inmsg, outmsg;

  MPI_Status Stat;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    dest = 1; source = numtasks - 1;
    outmsg = 0;
    rc = MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
    rc = MPI_Recv(&inmsg, 1, MPI_INT, source, MPI_ANY_TAG, MPI_COMM_WORLD, &Stat);
    printf("Final Value Received: %d\n", inmsg);
  } else {
    dest = (rank + 1) % numtasks; source = rank -1 ;
    rc = MPI_Recv(&inmsg, rank, MPI_INT, source, MPI_ANY_TAG, MPI_COMM_WORLD, &Stat);
    outmsg = inmsg + (rank * 2);
    rc = MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
  }

  MPI_Finalize();
}