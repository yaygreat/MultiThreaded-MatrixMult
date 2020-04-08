#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include<iostream>
using namespace std;


#define SIZE 1000
#define NO_THREADS 25

int matA[SIZE][SIZE];
int matB[SIZE][SIZE];
int matC[SIZE][SIZE];
int slice = 0;

void* matrix_multiplication(void* arg)
{
	slice = slice + 1;
	// Each thread will solve a slice of matrix. In this case,
	// one thread will solve 1/25th of the elements of matrix C
	for (int i = slice * SIZE / 25; i < (slice + 25) * SIZE / 25; i++)
		for (int j = 0; j < SIZE; j++)
			for (int k = 0; k < SIZE; k++)
				matC[i][j] += matA[i][k] * matB[k][j];
}

int main()
{
	// Generating matrix tables with random values
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			matA[i][j] = rand() % 2000;
			matB[i][j] = rand() % 2000;
		}
	}

	/*// Displaying contents of Matrix A
	cout << endl << "Matrix A" << endl;
	for (int i = 0; i < SIZE; i++) 
	{
		for (int j = 0; j < SIZE; j++)
			cout << matA[i][j] << " ";
		cout << endl;
	}

	// Displaying contents of Matrix B
	cout << endl << "Matrix B" << endl;
	for (int i = 0; i < SIZE; i++) 
	{
		for (int j = 0; j < SIZE; j++)
			cout << matB[i][j] << " ";
		cout << endl;
	}*/

	// Declaring 25 threads
	pthread_t threads[NO_THREADS];

	// Creating 25 threads where each thread evaluates its own slice of the matrix
	for (int i = 0; i < NO_THREADS; i++) {
		int* p;
		pthread_create(&threads[i], NULL, matrix_multiplication, (void*)(p));
	}

	// Joining and waiting for all threads to complete
	for (int i = 0; i < NO_THREADS; i++)
		pthread_join(threads[i], NULL);
	/*
	// Displaying the result matrix
	cout << endl << "Multiplication of A and B" << endl;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++)
			cout << matC[i][j] << " ";
		cout << endl;
	}*/
	return 0;
}