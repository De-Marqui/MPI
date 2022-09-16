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

    int start = rank * 5 + 1;//500 + 1;
    int end = start + 4;//999;
    
    printf("start %d\n", start);
    printf("end %d\n", end);
    
    for(int i = start; i <= end; i++) {
        ans += (1.0/i);
        printf("end %d\n", ans);
    }

    if(rank != 0) {
        MPI_Ssend(&ans, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    } else {
        total = ans;
        for(int j = 1; j < 2; j++) {
                MPI_Recv(&ans, 1, MPI_DOUBLE, j, 0, MPI_COMM_WORLD, &status);
                total += ans;
        }
        printf("Total is %lf\n", total);
        printf("Total Nodes is %d\n", nodes);
   }


    MPI_Finalize();
    return 0;
}
