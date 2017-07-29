#include <mpi.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>

#define mark 500000

int prime(int start_num, int end_num){
	int primeStart = time(NULL);
	for(int i = start_num; i < end_num; i++){
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

		//Master node listens for the other nodes to finish
		while(finishedCount < worldSize){
			MPI_Recv(&finishedSign, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if(finishedSign == 1){
				finishedCount++;
			}
		}
		std::cout << "Finished in " << time(NULL) - mainStart << "s" << std::endl; 
	}
	else{
		//Designates the portion the node needs to do and start that work
		int rangeStart = round((worldRank-1)*(mark/worldSize-1));
		int rangeEnd = round(worldRank*(mark/worldSize-1));
		prime(rangeStart, rangeEnd);
		std::cout << "node" << worldRank << ": DONE" << "  " << rangeStart << "-" << rangeEnd << std::endl;

		//Signals the master node that the compute node has finished 
		finishedSign = 1;
		MPI_Send(&finishedSign, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}
