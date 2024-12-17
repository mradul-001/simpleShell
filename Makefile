shell: main.c
	@ gcc -c main.c -o main.o
	@ gcc main.o -o shell

clean:
	@ rm -f *.o
	@ rm -f shell