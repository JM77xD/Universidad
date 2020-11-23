all: documentacion bin/usopilas_max

# ************ Documentacion ******************
documentacion:
	doxygen Doxyfile

# ************ Compilación ************

bin/usopilas_max: lib/libformas.a obj/usopilas_max.o
	g++ -Llib/ -o bin/usopilas_max obj/usopilas_max.o -lformas

lib/libformas.a: obj/pila_max_cola.o obj/pila_max_VD.o
	ar rvs lib/libformas.a obj/pila_max_cola.o obj/pila_max_VD.o

obj/pila_max_cola.o: src/pila_max_cola.cpp include/pila_max_cola.h src/cola.cpp include/cola.h
	g++ -g -c -o obj/pila_max_cola.o -I./include src/pila_max_cola.cpp

obj/pila_max_VD.o: src/pila_max_VD.cpp include/pila_max_VD.h
	g++ -g -c -o obj/pila_max_VD.o -I./include src/pila_max_VD.cpp

obj/usopilas_max.o: src/usopilas_max.cpp include/pila_max.h include/pila_max_cola.h include/pila_max_VD.h
	g++ -g -c -o obj/usopilas_max.o -I./include src/usopilas_max.cpp



# ************ Limpieza ************
clean:
	-rm obj/* lib/*

mrproper: clean
	-rm -r bin/* doc/html

autor:
	@echo "Jose María Ramírez González"