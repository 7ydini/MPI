#include <stdio.h>
#include "mpi.h"
#include <iostream>
      
using namespace std;
// Я усовершенствовал программу. Теперь нулевой процесс отправляет всем остальным, а они в свою очередь принимают и отправляют обратно нулевому.

int main(int argc, char* argv[])
{
	int ProcNum, ProcRank, RecvRank;
	int m = 1, value = 1, sum = 0;
	MPI_Status Status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	for (int i = 0; i < m; i++)
	{

		if (ProcRank == 0) {
			MPI_Bcast(&ProcRank, 1, MPI_INT, 0, MPI_COMM_WORLD);
			printf("\nSend 0 to all process \n");
			for (int i = 1; i < ProcNum; i++)
			{
				MPI_Recv(&RecvRank, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
				printf("\nRequest from %d to 0 process\n", RecvRank);
			}
		}else {
			MPI_Reduce(&value, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
			printf("\nRequest from 0 to %d process \n", ProcRank);
		}
      
		if (ProcRank != 0) {
			MPI_Send(&ProcRank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
			printf("\nSend from %d to 0 process \n", ProcRank);
		}
	}
	MPI_Finalize();
}
