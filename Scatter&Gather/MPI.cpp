#include <stdio.h>
#include "mpi.h"
#include <iostream>

using namespace std;

// cd C:\Users\8182160\source\repos\MPI\Debug\
// mpiexec -n 4 MPI.exe

int main(int argc, char* argv[])
{
	int ProcNum, ProcRank, RecvRank;
	int m = 1, g = 0;
	bool F = true;
	MPI_Status Status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	int* getValue = new int[ProcNum];
	int* value = new int[ProcNum];
	for (int i = 0; i < ProcNum; i++) {
		getValue[i] = 0;
		value[i] = 1;
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < ProcNum; j++) {
			if (ProcRank == j) {
				MPI_Scatter(value, 1, MPI_INT, getValue, 1, MPI_INT, j, MPI_COMM_WORLD);
				printf("\nSend %d to all process \n", j);
			}
			else {
				
				MPI_Gather(value, 1, MPI_INT, getValue, 1, MPI_INT, j, MPI_COMM_WORLD);
				printf("\nRequest from %d to %d process \n", ProcRank, j);
			}
		}
		MPI_Reduce(value, getValue, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
		printf("\ngetValue: %d\n", getValue[0]);
		printf("Summ %d", MPI_SUM);
			if (getValue[0] != 1) {
				F = false;
			}

		if (ProcRank == ProcNum - 1) {
			if (F) {
				printf("\nTrue\n");
			}
			else
				printf("\nFalse\n");
		}
	}
	MPI_Finalize();
}
