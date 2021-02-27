#include <stdio.h>
#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	int ProcNum, ProcRank, RecvRank;
	int m = 1, value = 1;
	bool F = true;
	MPI_Status Status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	int* getValue = new int[ProcNum];
	for (int i = 0; i < m; i++)
	{

		if (ProcRank == 0) {
			
			MPI_Scatter(getValue, 1, MPI_INT, &value, 1, MPI_INT, 0, MPI_COMM_WORLD);
			printf("\nSend 0 to all process \n");
			
		}else {
			MPI_Gather(&value, 1, MPI_INT, getValue, 1, MPI_INT, 0, MPI_COMM_WORLD);
			printf("\nMess from %d to 0 process \n", ProcRank);
			
		}
		if (ProcRank == 0) {
			for (int i = 1; i < ProcNum; i++) {
				if (getValue[i] == 0) {
					F = false;
				}
			}
		}
		if (ProcRank == 0) {
			if (F) {
				printf("\nTrue\n");
			}
			else
				printf("\nFalse\n");
		}
	}
	MPI_Finalize();
}
