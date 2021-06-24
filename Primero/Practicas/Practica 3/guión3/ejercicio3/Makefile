all: bin/ejercicio3

clean:
	echo "Limpieza de archivos objeto y bibliotecas..."
	rm obj/*.o lib/*.a

mrproper: clean
	rm bin/ejercicio3

obj/utilidades.o: src/utilidades.cpp include/utilidades.h
	g++ -c -o obj/utilidades.o -Iinclude src/utilidades.cpp

lib/libformas.a: obj/utilidades.o
	ar rvs lib/libformas.a obj/utilidades.o

obj/ejercicio3.o: src/ejercicio3.cpp include/utilidades.h
	g++ -c -o obj/ejercicio3.o -Iinclude src/ejercicio3.cpp

bin/ejercicio3: obj/ejercicio3.o lib/libformas.a
	g++ -Llib/ -o bin/ejercicio3 obj/ejercicio3.o -lformas
