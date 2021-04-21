#include <stdio.h>
#include "mpi.h"
#include <iostream>
#include <time.h>

using namespace std;

// cd C:\Users\8182160.SIPC.000\source\repos\MPI\Debug
// mpiexec -n 4 MPI.exe
void showMatrix(int** m, int size);
int main(int argc, char* argv[])
{
	srand(time(NULL));
	int ProcNum, ProcRank, RecvRank;
	int m = 1, g = 0, n = 3, A = 2;
	bool F = true;
	MPI_Status Status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	int** matrix = new int*[n];
	int** buffmatrix;
	buffmatrix = new int* [n];
	for (int i = 0; i < n; i++) {
		buffmatrix[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];		
	}
	int count = 0;
	//for (int k = 0; k < A; k++) {
		for (int j = 0; j < n; j++) {
			for (int i = 0; i < n; i++) {
				matrix[i][j] = 1 + rand() % 10;
			}
		}
		for (int j = 0; j < n; j++) {
			for (int h = 0; h < n; h++) {
				//int h = 0;
				if (ProcRank == j) {
					for (int i = 0; i < n; i++) {
						count += matrix[h][i] * matrix[i][h];
					}
					MPI_Send(&count, count, MPI_INT, 0, j, MPI_COMM_WORLD);
				}
				if (ProcRank == 0) {
					MPI_Recv(&buffmatrix[h][j], 1, MPI_INT, j, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
				}
			}
			//h++;
		}
	//}
	if (ProcRank == 0) {
		showMatrix(buffmatrix, n);
	}
	

	MPI_Finalize();
}

void showMatrix(int** m, int size) {
	for (int j = 0; j < size; j++) {
		cout << endl;
		for (int i = 0; i < size; i++) {
			cout << m[i][j] << " ";
		}
	}
}
