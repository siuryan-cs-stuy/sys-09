all: dir.c
	gcc -o dir dir.c

run: all
	./dir

clean:
	rm *.o
	rm *~
	rm dir
