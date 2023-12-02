
main:
	gcc -c main.c
	gcc -o DSSimul main.o

clean:
	rm DSSimul *.o