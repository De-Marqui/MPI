#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(void)
{
  
  // initialise the MPI 
  int ierr = MPI_Init(&argc, &argv);
  int procid, numprocs;
  
  ierr = MPI_Comm_rank(MPI_COMM_WORLD, &procid);
  ierr = MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

  // partition = (job size) over (processors). 
  unsigned int partition = N / numprocs;
  
   double serie = 0, S = 0;
   long long int T = 2222222222;

  
  for (long long int i = 1; i<=T; i++)
  {
     S += (1.0/i);
  }
   
   ierr = MPI_Finalize();
  
   printf("Serie de Taylor(%lld): %f\n", T, S);
}
