#include <stdio.h>
#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	int ProcNum, ProcRank, RecvRank;
	int m = 1;
	MPI_Status Status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	for (int i = 0; i < m; i++)
	{
		if (ProcRank == 0) {
				MPI_Send(&ProcRank, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
				printf("\nProcess %d send to 1 process \n", ProcRank, 1);
				MPI_Recv(&RecvRank, 1, MPI_INT, ProcNum - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);	
				printf("\nAnswer from process %d to %d process \n", RecvRank, ProcRank);
		}
		
		if (ProcRank < ProcNum - 1 && ProcRank > 0)
		{
			MPI_Recv(&RecvRank, 1, MPI_INT, ProcRank - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
			printf("\nMessage received from process %d to %d process \n", RecvRank, ProcRank);
			MPI_Send(&ProcRank, 1, MPI_INT, ProcRank + 1, 0, MPI_COMM_WORLD);
			printf("\nSend %d to %d process \n", ProcRank, ProcRank + 1);
		}	
		
		if(ProcRank == ProcNum - 1 ){
			MPI_Recv(&RecvRank, 1, MPI_INT, ProcNum - 2, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
			printf("\nMessage received from process %d to %d process \n", RecvRank, ProcRank);
			MPI_Send(&ProcRank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
			printf("\nSend %d to %d process \n", ProcRank, 0);
		}
	}
	MPI_Finalize();
}
