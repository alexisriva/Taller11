#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

//Declaramos una estructura
typedef struct mi_estructuraTDA{
	int ini;
	int fin;
	int *array;
} estructura;

//Funcion que genera un entero aleatorio entre un rango especifico
int aleatorio(int min, int max){
	return (rand() % (max-min+1)) + min;
}

//Funcion para obtener el tiempo actual
double obtenerTiempoActual(){
	struct timespec tsp;
	clock_gettime(CLOCK_REALTIME, &tsp);
	double secs = (double)tsp.tv_sec;
	double nano = (double)tsp.tv_nsec/1000000000.0;
	return secs+nano;
}

//Funcion que recibe cada hilo para realizar la suma del subarreglo
void *funcionHilo(void *arg) {
	estructura *argumentos = (estructura *) arg;
	int *temp = argumentos->array;
	int suma = 0;

	for (int i=argumentos->ini; i<=argumentos->fin;i++)
		suma += *(temp+i);

	return (void *)suma;
}

//Main
int main(int argc, char *argv[]) {

	int arraySize = 0;
	int numOfThreads = 0;
	long sumatotal = 0;
	double elemxth = 0;
	double tiempoInicio = 0;
	double tiempoFin = 0;
	pthread_t ids[numOfThreads];

	if (argc != 3)
		printf("Uso: ./hilos <tamaño del arreglo> <numero de hilos>\n");
	else {
		tiempoInicio = obtenerTiempoActual();

		arraySize = atoi(argv[1]);
		numOfThreads = atoi(argv[2]);

		int *array = (int *)malloc(arraySize*sizeof(int));
		for (int i=0;i<arraySize;i++)
			*(array+i)=aleatorio(1,200);

		elemxth = arraySize/numOfThreads;
		
		//Cuando la división no es exacta
		if (arraySize % numOfThreads != 0){ 
			elemxth = ceil(elemxth);
			for (int i=0;i<numOfThreads;i+=elemxth) {
				estructura *structarg = malloc(sizeof(estructura));
				structarg->ini = i;
				if (i != numOfThreads-1){
					structarg->fin = elemxth-1;
					
				}
				else{
					structarg->fin = elemxth;
				}
				structarg->array = array;
				pthread_create(&ids[i],NULL,funcionHilo,(void *)structarg);
				elemxth+=elemxth;
			}
		}
		
		//Cuando la división es exacta
		else{	     
			for (int i=0;i<numOfThreads;i+=elemxth) {
				estructura *structarg = malloc(sizeof(estructura));
				structarg->ini = i;
				structarg->fin = elemxth-1;
				structarg->array = array;
				pthread_create(&ids[i],NULL,funcionHilo,(void *)structarg);
				elemxth+=elemxth;
			}
		}	
		
		void * sum_parcial = NULL;

		for (int i=0;i<numOfThreads;i++) {
			pthread_join(ids[i],&sum_parcial);
			sumatotal += (long)sum_parcial;
		}	
		
		tiempoFin = obtenerTiempoActual();
		printf("La suma total es: %lu\n", sumatotal);
		printf("El tiempo de ejecucion fue: %f\n", (tiempoFin-tiempoInicio));
	}
	
	return 0;

}


