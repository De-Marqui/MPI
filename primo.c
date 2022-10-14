#include <mpi.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdio.h>

int process_count;  
int my_rank; 

int isPrime(int n) {
   int top,d;
   top = (int)(sqrt((double)n)+0.0001);
   for (d = 2; d <= top; d++)
      if ( n % d == 0 )
         return 0;
   return 1;
}

void primeCalc(int lowerRange, int upperRange) {
   double delta = (double)upperRange / process_count;
   int min, max; 

   min = (my_rank == 0)? lowerRange : (int)(my_rank*delta) + 1;
   max = (my_rank == process_count-1)? upperRange : (int)((my_rank+1)*delta);

   int count = 0;  
   int i;

   if ( my_rank != 0) {
      for (i = min; i <= max; i++)    
         if (isPrime(i))
            count++;
      int data_to_send[3];
      data_to_send[0] = count;
      data_to_send[1] = min;
      data_to_send[2] = max;
      MPI_Send( data_to_send, 3, MPI_INT, 0, 0, MPI_COMM_WORLD);
   }
   else {
      double start = MPI_Wtime();
      for (i = min; i <= max; i++)    
         if (isPrime(i))
            count++;
      printf("Processo 0 Encontrou %d Numeros Primos entre %d e %d.\n", count, min, max);
      int ct;
      for (ct = 1; ct < process_count; ct++) {
         int data_received[3];
         MPI_Status status;
         MPI_Recv( data_received, 3, MPI_INT, MPI_ANY_SOURCE,
                        MPI_ANY_TAG, MPI_COMM_WORLD, &status );
         count += data_received[0];
         printf("Processo %d Encontrou %d Numeros Primos entre %d e %d.\n", 
              status.MPI_SOURCE, data_received[0], data_received[1], data_received[2]);
      }
      printf("\nNumero de Primos Encontrados no Total entre: %d e %d:  %d.\n", lowerRange, upperRange, count);
      double elapsed = MPI_Wtime() - start;
      printf("\nTempo de Execução:  %1.3f seconds.\n", elapsed);
   }
}


int main() {
   int number1, number2;
   
   MPI_Init(NULL , NULL);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
   MPI_Comm_size(MPI_COMM_WORLD, &process_count);
   printf("\nDigite um intervalo de 2 numeros formato: %d %d:\n");
   scanf("%d %d", &number1, &number2);
   primeCalc(number1, number2);
   MPI_Finalize();
}
