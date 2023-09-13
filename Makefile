APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src

all: libed myapps gen

libed:
	gcc -Wall -Werror -Wpedantic -O3 -march=native -c $(SRC)/functions.c -I $(INCLUDE) -o $(OBJ)/functions.o

myapps:
	gcc -Wall -Werror -Wpedantic -O3 -march=native $(APPS)/main.c $(OBJ)/*.o -I $(INCLUDE) -o $(BIN)/main

gen: 
	python3 generator.py

run:
	$(BIN)/main

clear:
	rm ./individuals/file* ./pics/pic* values.txt