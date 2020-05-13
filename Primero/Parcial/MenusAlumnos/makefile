OBJ=obj
BIN=bin
SRC=src
INC=include

all: $(BIN)/menu

# Ejecutables
$(BIN)/menu: $(OBJ)/main.o $(OBJ)/menu.o 
	g++ -o $(BIN)/menu $^

#Objetos

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/menu.h
	g++ -c -o $(OBJ)/main.o $< -I$(INC)

$(OBJ)/menu.o: $(SRC)/menu.cpp $(INC)/menu.h
	g++ -c -o $(OBJ)/menu.o	$< -I$(INC)


clean:
	rm $(OBJ)/* $(BIN)/*
