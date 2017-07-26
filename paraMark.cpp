#include <mpi.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <ctime>

int prime(){
	int primeStart = time(NULL);
	for(int i = 1; i < 500000; i++){
		bool foundPrime = true;
		for(int n = 2; n < i; n++){
			if(i % n == 0){
				foundPrime = false;
				break;
			}
		}
	}
	return time(NULL) - primeStart;
}

int main(){
	MPI_Init(NULL, NULL);

	int worldSize;
	MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

	int worldRank;
	MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
	
	int finishedSign;
	int finishedCount = 0;

	if(worldRank == 0){
		int mainStart = time(NULL);
		while(finishedCount < worldSize){
			MPI_Recv(&finishedSign, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if(finishedSign == 1){
				finishedCount++;
			}
		}
		std::cout << "Finished in " << time(NULL) - mainStart << "s" << std::endl; 
	}
	else{
		prime();
		finishedSign = 1;
		MPI_Send(&finishedSign, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}
