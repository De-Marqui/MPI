#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

static int rank, nodes;

int main()
{
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nodes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    double ans = 0;
    double total = 0;

   long long int start = rank * 500000000 + 1;   //500 + 1;  500 000 000
   long long int end = start + 499999999;        //999;
    
    //printf("start %d\n", start);
   // printf("end %d\n", end);
    
    for(int i = start; i <= end; i++) {
        ans += (1.0/i);
    }

    if(rank != 0) {
        MPI_Ssend(&ans, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    } else {
        total = ans;
        for(int j = 1; j < 2; j++) { // Esse 2 é quantia aceita de processadores
                MPI_Recv(&ans, 1, MPI_DOUBLE, j, 0, MPI_COMM_WORLD, &status);
                total += ans;
        }
        printf("Total: %f\n", total);
        printf("Total de Separacoes: %d\n", nodes);
   }


    MPI_Finalize();
    return 0;
}
