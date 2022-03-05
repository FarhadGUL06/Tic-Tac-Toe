all: build

build: minimax.c
		gcc -g -Wall minimax.c -o minimax
clean:
		rm minimax