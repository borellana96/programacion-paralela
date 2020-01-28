#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;
 
int main(int argc, char* argv[])
{
    int myRank;
    int reduction_result = 0;

	MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    MPI_Reduce(&myRank, &reduction_result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(myRank == 0)
    {
        printf("La suma de indices de procesos es %d.\n", reduction_result);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}

