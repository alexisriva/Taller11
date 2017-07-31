hilos: hilos.c 
	gcc -Wall -g $^ -lm -o $@ -pthread

.PHONY: clean
clean:
	rm -rf hilos
