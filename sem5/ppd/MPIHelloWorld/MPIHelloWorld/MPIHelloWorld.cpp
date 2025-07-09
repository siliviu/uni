#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>

using namespace std;

MPI_Request recv_request[10];



int main(int argc, char** argv) {

	int  namelen, myid, numprocs;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	//printf("Process %d / %d  : Hello world\n", myid, numprocs);

	char* mymessage = new char[50];
	strcpy_s(mymessage, 50, "Hello from ");

	char* sirTotal = new char[50 * numprocs];
	sirTotal[0] = '\0';

	if (myid == 0) {
		strcat_s(mymessage, 50, "0");
		strcat_s(sirTotal, 50, mymessage);
		MPI_Status status;
		for (int i = 1; i < numprocs; i++) {
			MPI_Recv(mymessage, 50, MPI_CHAR, i, 111, MPI_COMM_WORLD, &status);
			//printf("STATUS SOURCE %d\n", status.MPI_SOURCE);
			strcat_s(sirTotal, 50, mymessage);
		}
		printf("%s\n", sirTotal);
	}
	else {
		char* buf = new char[10];
		_itoa_s(myid, buf, 10, 10);
		strcat_s(mymessage, 50, buf);
		MPI_Send(mymessage, strlen(mymessage) + 1, MPI_CHAR, 0, 111, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}