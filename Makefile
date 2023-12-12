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
	python3 $(APPS)/generator.py

run: 
	$(BIN)/main
	python3 $(APPS)/show.py

clean:
	rm ./individuals/file* ./individuals/target* ./pics/pic* Evolution.mp4

commit: 
	git pull origin main
	git add .
	git commit -m "automatic commit"
	git push origin main

