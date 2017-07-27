all: hilos

hilos: hilos.c 
	gcc -Wall -g $^ -o $@

clean:
rm -rf hilos
