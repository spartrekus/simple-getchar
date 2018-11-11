getchar: getchar.c
	gcc -O2 -Wall -o $@ $<

clean:
	rm -rf *~ getchar
