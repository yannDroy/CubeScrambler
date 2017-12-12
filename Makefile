GC = gcc
OPTIONS = -Wall -g -lSDL -lSDL_ttf

CubeScrambler : display.o scramble.o menu.o file_rw.o timer.o main.o
	$(GC) -o CubeScrambler display.o scramble.o menu.o file_rw.o timer.o main.o $(OPTIONS)

main.o : main.c const.h
	$(GC) $(OPTIONS) -c main.c

scramble.o : scramble.c scramble.h
	$(GC) $(OPTIONS) -c scramble.c

display.o : display.c display.h
	$(GC) $(OPTIONS) -c display.c

menu.o : menu.c menu.h
	$(GC) $(OPTIONS) -c menu.c

file_rw.o : file_rw.c file_rw.h
	$(GC) $(OPTIONS) -c file_rw.c

timer.o : timer.c timer.h
	$(GC) $(OPTIONS) -c timer.c

clean :
	rm -f *.o CubeScrambler
