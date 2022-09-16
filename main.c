#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(void)
{
  
  // initialise the MPI 
  int pe, numprocs, done = 0;
  
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &pe);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

  
  int intervals = 1000;
  double time1 = MPI_Wtime();
  MPI_Bcast(&intervals, 1, MPI_INT, 0, MPI_COMM_WORLD);
  
  int count = intervals / numprocs;
  int start = count * pe;
  int end = count * pe + count;

   long long int i;
   double serie = 0, S = 0;
   long long int T = 2222222222;

  
  for (i = start; i<=end; i++)
  {
     S += (1.0/i);
  }
  
   MPI_Reduce(&S, &serie, 1, MPI_DOUBLE, MPI_SUM,
        0, MPI_COMM_WORLD);

   double time2 = MPI_Wtime();
   
  
  if (pe == 0) {
        serie = serie * 4;
        printf("Result:   %.10lf\n", total);
        printf("Time:     %.10lf\n", time2 - time1);
    }

   MPI_Finalize();
   //ierr = MPI_Finalize();
  
   //printf("Serie de Taylor(%lld): %f\n", T, S);
}
