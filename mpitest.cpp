#include <mpi.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

int main(){
	MPI_Init(NULL, NULL);

	int worldSize;
	MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
	std::cout << worldSize << std::endl;
	return 0;
}