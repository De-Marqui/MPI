// Victor de Marqui - TIA: 32014287
// Talyta Scaramuzzo - TIA: 32079915
// Guilherme Rodrigues Santos - TIA: 32012209

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

static int myRank, procNum;

int main()
{
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Status status;

    double S = 0;
    double serie = 0;

   long long int start = myRank * 500000000 + 1;   
   long long int end = start + 499999999;        
    
    for(int i = start; i <= end; i++) 
        S += (1.0/i);
    
    if(myRank != 0) {
        MPI_Ssend(&S, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    } else {
        serie = S;
        for(int j = 1; j < 2; j++) { // Lembrete: [2] número de processador
                MPI_Recv(&S, 1, MPI_DOUBLE, j, 0, MPI_COMM_WORLD, &status);
                serie += S;
    }
        printf("Taylor(1000000000): %f\n", serie);
   }


    MPI_Finalize();
    return 0;
}
