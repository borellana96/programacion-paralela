/* EJERCIO 7:
 * Desarrolle un algoritmo en MPI, utilizando p procesadores para calcular !n
 */

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int rank, m_size;
	int n, prod_global=1, prod_local=1;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &m_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank==0){
		printf("Ingrese el numero para calcular su factorial: \n");
		scanf("%d", &n);							//numero factorial n
	}

	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);	//Todos los procesos almacenan el valor de n

	int local_n = n / m_size; 						//número de elementos por cada proceso (n/p)

	int myRank_local = local_n * rank + 1;			//rango inicial cada proceso
	for(int i=0; i<local_n; i++){					//iterará en cada proceso local_n (n/p) veces
		prod_local = prod_local * myRank_local;
		myRank_local++;
	}

	//En la practica hice esto
	/*
	int myRank_local = local_n * rank + local_n;			//rango inicial cada proceso
	for(int i=0; i<local_n; i++){					//iterará en cada proceso local_n (n/p) veces
		prod_local = prod_local * myRank_local;
		myRank_local--;
	}*/

	MPI_Reduce(&prod_local, &prod_global, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

	if (rank ==0){
		printf("El factorial de %d en %d procesos es: %d \n", n, m_size, prod_global);
	}

	MPI_Finalize();

	return EXIT_SUCCESS;
}

