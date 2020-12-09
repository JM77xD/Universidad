INC = include
SRC = src
BIN = bin
OBJ = obj
LIB = lib
DOC = doc
CXX = g++
CPPFLAG = -I$(INC) -c

all: $(BIN)/usodiccionario $(BIN)/usoguia $(DOC)/html

$(BIN)/usodiccionario: $(SRC)/usodiccionario.cpp $(SRC)/diccionario.cpp $(INC)/diccionario.h
	$(CXX) -I$(INC) -I$(SRC) -o $@ $< 

$(DOC)/html: Doxyfile
	doxygen Doxyfile

$(BIN)/usoguia: $(OBJ)/usoguia.o $(LIB)/libguia.a
	$(CXX) -o $@ $< -L$(LIB) -lguia

$(LIB)/libguia.a: $(OBJ)/guiatlf.o
	ar -rvs $@ $^

$(OBJ)/guiatlf.o: $(SRC)/guiatlf.cpp $(INC)/guiatlf.h
	$(CXX) $(CPPFLAG) $< -o $@

$(OBJ)/usoguia.o: $(SRC)/usoguia.cpp $(INC)/guiatlf.h
	$(CXX) $(CPPFLAG) $< -o $@

clean:
	rm $(OBJ)/* $(LIB)/*

mrproper: clean
	rm -r $(BIN)/* $(DOC)/html

autor:
	@echo "José María Ramírez González"