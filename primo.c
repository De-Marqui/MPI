#include <mpi.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdio.h>
int DEFAULT_RANGE = 10000000;  
int process_count;  
int my_rank; 

int get_range(int argc, char **argv) {
   if (argc < 2 || !argv[1])
      return DEFAULT_RANGE;
   int range = atoi(argv[1]);
   if (range < 2*process_count)
      return DEFAULT_RANGE;
   return range;
}

int is_prime(int n) {
   int top,d;
   top = (int)(sqrt((double)n)+0.0001);
   for (d = 2; d <= top; d++)
      if ( n % d == 0 )
         return 0;
   return 1;
}

void do_work(int argc, char **argv) {

   int range = get_range(argc,argv); 
   double delta = (double)range / process_count;
   int min;  
   int max; 
   min = (my_rank == 0)? 2 : (int)(my_rank*delta) + 1;
   max = (my_rank == process_count-1)? range : (int)((my_rank+1)*delta);

   int count = 0;  
   
   int i;

   if ( my_rank != 0) {
      for (i = min; i <= max; i++)    
         if (is_prime(i))
            count++;
      int data_to_send[3];
      data_to_send[0] = count;
      data_to_send[1] = min;
      data_to_send[2] = max;
      MPI_Send( data_to_send, 3, MPI_INT, 0, 0, MPI_COMM_WORLD);
   }
   else {
      double start = MPI_Wtime();
      for (i = min; i <= max; i++)    // Count the primes.
         if (is_prime(i))
            count++;
      printf("Process 0 reports %d primes between %d and %d.\n", count, min, max);
      int ct;
      for (ct = 1; ct < process_count; ct++) {
         int data_received[3];
         MPI_Status status;
         MPI_Recv( data_received, 3, MPI_INT, MPI_ANY_SOURCE,
                        MPI_ANY_TAG, MPI_COMM_WORLD, &status );
         count += data_received[0];
         printf("Process %d reports %d primes between %d and %d.\n", 
              status.MPI_SOURCE, data_received[0], data_received[1], data_received[2]);
      }
      printf("\nTotal number of primes between 2 and %d:  %d.\n", range, count);
      double elapsed = MPI_Wtime() - start;
      printf("\nElapsed time:  %1.3f seconds.\n", elapsed);
   }
}


int main(int argc, char **argv) {

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
   MPI_Comm_size(MPI_COMM_WORLD, &process_count);
   
   do_work(argc, argv);
   
   MPI_Finalize();

}
