shell: main.c
	@ gcc main.c interactive.c batch.c -o shell

clean:
	@ rm -f *.o
	@ rm -f shell