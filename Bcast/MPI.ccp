#include <stdio.h>
#include "mpi.h"
#include <iostream>
// cd C:\Users\8182160\source\repos\MPI\Debug\
// mpiexec -n 4 MPI.exe
using namespace std;
int main(int argc, char* argv[])
{
	int ProcNum, ProcRank;// RecvRank;
	int m = 1, value = 1, sum = 0;
	MPI_Status Status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < ProcNum; j++) {
			
			if (ProcRank == j) {
      				MPI_Bcast(&ProcRank, 1, MPI_INT, j, MPI_COMM_WORLD);
				printf("\nSend from %d to all process \n", ProcRank);
			}
			else {
				printf("\nRequest from %d to %d process \n", j, ProcRank);
			}
		}
	}
	MPI_Finalize();
}
