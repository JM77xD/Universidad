INC = include
SRC = src
BIN = bin
OBJ = obj
LIB = lib
DOC = doc
CXX = g++
CPPFLAG = -I$(INC) -I$(SRC) -o

all: $(BIN)/usodiccionario $(DOC)/html

$(BIN)/usodiccionario: $(SRC)/usodiccionario.cpp $(SRC)/diccionario.cpp $(INC)/diccionario.h
	$(CXX) $(CPPFLAG) $@ $< 

$(DOC)/html: Doxyfile
	doxygen Doxyfile

mrproper:
	rm -r $(BIN)/* $(DOC)/html

autor:
	@echo "José María Ramírez González"