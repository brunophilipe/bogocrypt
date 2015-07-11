all: main

bogocrypt:
	gcc bogocrypt.c -c -o bogocrypt.o

main: bogocrypt
	mkdir -p bin
	gcc main.c bogocrypt.o -o ./bin/bogocrypt
	rm -f *.o

clean:
	rm -f *.o ./bin/bogocrypt