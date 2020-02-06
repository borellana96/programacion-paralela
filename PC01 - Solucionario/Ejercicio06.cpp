/* EJERCIO 6:
 * Utilizando MPI, implemente un algoritmo que determine el número de veces
 * que un elemento x(2) aparezca en un vector A con n (16) elementos enteros.
 * Se puede asumir que su algoritmo comienza con los elementos ya distribuidos
 * entre los p procesos (n/p para cada uno)
 */

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int rank, m_size;
	int cont_global, cont_local=0;

	int A[16]={2,5,7,9,12,2,0,11,2,8,4,6,19,2,21,2};

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &m_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int A_length = sizeof(A)/sizeof(*A); 	//tamaño del vector
	int local_n = A_length / m_size; 		//número de elementos por cada proceso

	int pos_local = local_n * rank;			//posición que iterará cada proceso

	for(int i=0; i<local_n; i++){
		if(A[pos_local] == 2){
			cont_local++;
		}
		pos_local++;
	}

	MPI_Reduce(&cont_local, &cont_global, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank ==0){
		printf("El número de veces de 2 calculado en %d procesos del vector es: %d \n", m_size, cont_global);
	}


	MPI_Finalize();

	return EXIT_SUCCESS;
}

