SRC = src
LIB = lib
INC = include
OBJ = obj
DAT = datos
IMG = $(DAT)/imagenes
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g  -I$(INC) -c


# ************ Compilación del ejecutable ******************

all: $(BIN)/rutas_aereas documentacion

$(BIN)/rutas_aereas: $(OBJ)/rutas_aereas.o $(LIB)/libimagenes.a	$(LIB)/libpaises.a $(LIB)/librutas.a
	$(CXX) -I$(INC) -o $@ $< -L$(LIB) -limagenes -lpaises -lrutas
		
$(OBJ)/rutas_aereas.o: $(SRC)/rutas_aereas.cpp $(INC)/imagen.h $(INC)/almacen_rutas.h $(INC)/Paises.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(LIB)/libimagenes.a: $(OBJ)/imagenes.o $(OBJ)/imagenES.o
	ar -rvs $@ $^

$(OBJ)/imagenes.o: $(SRC)/imagen.cpp $(INC)/imagenES.h
	$(CXX) $(CPPFLAGS) -o $@ $<

$(OBJ)/imagenES.o: $(SRC)/imagenES.cpp
	$(CXX) $(CPPFLAGS) -o $@ $<

$(LIB)/libpaises.a: $(OBJ)/Paises.o $(OBJ)/Pais.o
	ar -rvs $@ $^

$(OBJ)/Paises.o: $(SRC)/Paises.cpp $(INC)/Pais.h
	$(CXX) $(CPPFLAGS) -o $@ $<

$(OBJ)/Pais.o: $(SRC)/Pais.cpp
	$(CXX) $(CPPFLAGS) -o $@ $<

$(LIB)/librutas.a: $(OBJ)/almacen_rutas.o $(OBJ)/ruta.o
	ar -rvs $@ $^

$(OBJ)/almacen_rutas.o: $(SRC)/almacen_rutas.cpp $(INC)/ruta.h
	$(CXX) $(CPPFLAGS) -o $@ $<

$(OBJ)/ruta.o: $(SRC)/ruta.cpp
	$(CXX) $(CPPFLAGS) -o $@ $<


# ************ Generación de documentación ******************
documentacion: doc/doxys/Doxyfile
	doxygen doc/doxys/Doxyfile


# ************ Limpieza ************
clean :
	@echo "Limpiando archivos objetos, librerías y fotos .ppm y .pgm"
	-rm $(OBJ)/* $(LIB)/* ./*.ppm ./*.pgm

mrproper : clean
	@echo "Limpiando ejecutable y documentación"
	-rm $(BIN)/* doc/html/*

# ************ Autoría ************

autor:
	@echo "Jose María Ramírez González"
