all: main clean

main: main.o filework.o git.o
	gcc main.o filework.o git.o -lpthread -o main
	
main.o: main.c
	gcc -c main.c
	
filework.o: filework.c
	gcc -c filework.c
	
git.o: git.c
	gcc -c git.c

clean:
	rm *.o
