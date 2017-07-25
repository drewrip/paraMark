#include <mpi.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

int main(){
	MPI_Init(NULL, NULL);

	int worldSize;
	MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

	int worldRank;
	MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
	std::cout << worldRank << "/" <<  worldSize << std::endl;
	MPI_Finalize();
	return 0;
}
