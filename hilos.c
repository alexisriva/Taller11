#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

int main(int argc, char *argv[]) {

	int arraySize = 0;
	int numOfThreads = 0;

	if (argc != 3)
		printf("Uso: ./hilos <tamaño del arreglo> <numero de hilos>\n");
	else {
		arraySize = argv[1];
		numOfThreads = argv[2];
	}

	return 0;

}

int aleatorio(int min, int max){
	return (rand() % (max-min+1)) + min;
}

double obtenerTiempoActual(){
	struct timespec tsp;
	clock_gettime(CLOCK_REALTIME, &tsp);
	double secs = (double)tsp.tv_sec;
	double nano = (double)tsp.tv_nsec/1000000000.0
	return secs+nano;
}
