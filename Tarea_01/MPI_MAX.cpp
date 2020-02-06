// mpiexec -n 5 ./MPI_MAX

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;
 
int main(int argc, char* argv[])
{
    int myRank;
    int reduction_result = 0;
    int v[5]={12,4,20,7,1};

	MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    MPI_Reduce(&v[myRank], &reduction_result, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);


    if(myRank == 0)
    {
        printf("El numero maximo es: %d.\n", reduction_result);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}

