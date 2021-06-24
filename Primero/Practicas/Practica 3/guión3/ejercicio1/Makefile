all: bin/ejercicio1

clean:
	echo "Limpieza de archivos objeto y bibliotecas..."
	rm obj/*.o lib/*.a

mrproper: clean
	rm bin/ejercicio1

obj/utilidades.o: src/utilidades.cpp include/utilidades.h
	g++ -c -o obj/utilidades.o -Iinclude src/utilidades.cpp

lib/libformas.a: obj/utilidades.o
	ar rvs lib/libformas.a obj/utilidades.o

obj/ejercicio1.o: src/ejercicio1.cpp include/utilidades.h
	g++ -c -o obj/ejercicio1.o -Iinclude src/ejercicio1.cpp

bin/ejercicio1: obj/ejercicio1.o lib/libformas.a
	g++ -Llib/ -o bin/ejercicio1 obj/ejercicio1.o -lformas
