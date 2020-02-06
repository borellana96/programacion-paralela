// mpiexec -n 5 ./MPI_MIN

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;
 
int main(int argc, char* argv[])
{
    int myRank;
    int size;

    int productoTotal = 1;

	MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(myRank!=0)
		MPI_Reduce(&myRank, &productoTotal, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
	else
		MPI_Reduce(&myRank + 1, &productoTotal, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);


    if(myRank == 0)
    {
        printf("El producto de los numeros del 1 al n procesos es: %d.\n", productoTotal);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}

