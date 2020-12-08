
INC = include
SRC = src
BIN = bin
OBJ = obj
LIB = lib
DOC = doc
CXX = g++
CPPFLAG = -I$(INC) -c

all: $(BIN)/usoguia $(DOC)/html

$(BIN)/usoguia: $(OBJ)/usoguia.o $(LIB)/libguia.a
	$(CXX) -o $@ $< -L$(LIB) -lguia

$(LIB)/libguia.a: $(OBJ)/guiatlf.o
	ar -rvs $@ $^

$(OBJ)/guiatlf.o: $(SRC)/guiatlf.cpp $(INC)/guiatlf.h
	$(CXX) $(CPPFLAG) $< -o $@

$(OBJ)/usoguia.o: $(SRC)/usoguia.cpp $(INC)/guiatlf.h
	$(CXX) $(CPPFLAG) $< -o $@

$(DOC)/html: Doxyfile
	doxygen Doxyfile

clean:
	rm $(OBJ)/* $(LIB)/*

mrproper: clean
	rm -r $(BIN)/* $(DOC)/html

autor:
	@echo "José María Ramírez González"