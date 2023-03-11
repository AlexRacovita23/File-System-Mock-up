build:
	gcc -std=c99 -o tema3 Tarb.c main.c -g

run:
	./tema3

clean:
	rm -f *.o tema3