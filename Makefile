APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src
FLAGS = -Wall -Werror -Wpedantic -O3 -march=native #-fsanitize=address 

all: libed myapps

libed:
	@gcc $(FLAGS) -c $(SRC)/functions.c -I $(INCLUDE) -o $(OBJ)/functions.o

myapps:
	@gcc $(FLAGS) $(APPS)/main.c $(OBJ)/*.o -I $(INCLUDE) -o $(BIN)/main

func1: 
	@python3 $(APPS)/generator.py

func2: 
	@python3 $(APPS)/generator2.py

run: 
	@$(BIN)/main
	@python3 $(APPS)/show.py	

clean:
	@rm ./individuals/file* ./individuals/target* fitness.txt ./pics/pic* ./bin/* ./obj/* Evolution.mp4

commit:
	make clean
	git add .
	git commit -m "Ajustes finais"
	git push origin main

debug: clean all func1 run