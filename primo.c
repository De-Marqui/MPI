//Talyta Scaramuzzo - 32079915

#include "mpi.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXSIZE 5000

int isPrime(int numero)
{
  int raiz, fator;
  raiz = (int)sqrt((double)numero);
  for (fator = 2; fator <= raiz; fator++)
    if (numero % fator == 0)
    {
      return 0;
    }
  return 1;
}

int main(int argc, char **argv)
{
  int myid, numprocs;
  int myTotalPrimes = 0, totalPrimes = 0;
  int *primes;
  int *myPrimes;
  int i, range, low, high;
  int j, k;
  myPrimes = (int *)malloc(sizeof(int) * 1);
  primes = (int *)malloc(sizeof(int) * MAXSIZE);

  j = strtol(argv[1], NULL, 10);
  k = strtol(argv[2], NULL, 10);

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  range = round((k - j) / numprocs);
  low = ((myid * range) + j) + myid;
  high = low + range;
  if (high > k)
    high = k;

  for (i = low + 1; i <= high; i++)
  {
    if (isPrime(i))
    {
      myPrimes[myTotalPrimes] = i;
      myTotalPrimes++;
      myPrimes = (int *)realloc(myPrimes, (myTotalPrimes) * sizeof(int));
    }
  }

  char hostname[30];
  gethostname(hostname, 30);
  printf("I got %d from %d - %s\n", myTotalPrimes, myid, hostname);
  printf("I got %d from %d - %s\n", myTotalPrimes, myid, hostname);

  MPI_Reduce(&myTotalPrimes, &totalPrimes, 1, MPI_INT, MPI_SUM, 0,
             MPI_COMM_WORLD);

  MPI_Gather(myPrimes, myTotalPrimes, MPI_INT, primes, myTotalPrimes, MPI_INT,
             0, MPI_COMM_WORLD);

  if (myid == 0)
  {
    printf("The total primes is %d.\n", totalPrimes);

 //   for (int i = 0; i < totalPrimes + 1; i++)
   // {
     // printf("%d\n", primes[i]);
    //}
    //SPEEDUP
    int main(int argc, char** argv){
  double startwtime = 0.0, endwtime;
  int quant = 1000000000,
  i,
  localSum = 0,
  globalSum = 0, tmp;
// comm
  int myrank, nprocs;
// split
  int split,
  begin,
  end;
  printf("time: \t%f\n", endwtime - startwtime);
  fflush(stdout);
  }

  MPI_Finalize();
  return 0;
}
