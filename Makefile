all: 
	gcc -Wall -Werror -Wpedantic -O3 -march=native -c functions.c -I functions.h -o functions.o
	gcc -Wall -Werror -Wpedantic -O3 -march=native gpt.c functions.o -I functions.h -o main
	./main