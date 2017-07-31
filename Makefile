hilos: hilos.c 
	gcc -Wall -g hilos.c -lm -o hilos -pthread

.PHONY: clean
clean:
	rm -rf hilos
