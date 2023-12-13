APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src

all: libed myapps

libed:
	gcc -Wall -Werror -Wpedantic -O3 -march=native -c $(SRC)/functions.c -I $(INCLUDE) -o $(OBJ)/functions.o

myapps:
	gcc -Wall -Werror -Wpedantic -O3 -march=native $(APPS)/main.c $(OBJ)/*.o -I $(INCLUDE) -o $(BIN)/main

func1: 
	python3 $(APPS)/generator.py

func2: 
	python3 $(APPS)/generator2.py

run: 
	$(BIN)/main
	python3 $(APPS)/show.py	

clean:
	rm ./individuals/file* ./individuals/target* fitness.txt ./pics/pic* Evolution.mp4

commit:
	make clean
	git add .
	git commit -m "Ajustes finais"
	git push origin main

