/*
 ============================================================================
 Name        : Project_Prob07.c
 Author      : Diego Elias Soto
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */
#include <math.h> 
#include "mpi.h" 
#include <iostream>
using namespace std;

void Get_Input(int size, int rank, int* n_p);
 
int main(void) {

	int rank;
	int size;
	int n;
	int local_n;
	int local_a, 
	int local_b;
	int total;
	int local_int;

	MPI_Init(NULL, NULL);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	Get_Input(size, rank, &n);

	local_n = n / size;

	local_a = 1 + rank*local_n;
	local_b = local_a + local_n - 1;

	local_int = 1;

	for (int i = local_a; i <= local_b; i++ ){
		local*= i;
	}
	
 	//utilizamos el MPI reduce para realizar el producto de todo los valores de local:int
	MPI_Reduce(&local_int, &total_int, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

	if ( rank == 0) {
		printf("El factorial es: %d\n", total);
	}

	MPI_Finalize();

	return 0;

}

void Get_Input(int comm_sz, int my_rank, int* n_p ) {

	if ( my_rank  == 0) {
		printf("Ingrese el numero que desea hallar su factorial\n");
		scanf("%d", n_p);
	}

	MPI_Bcast(n_p, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

