all: bin/ejercicio_7

clean:
	echo "Limpieza de archivos objeto y bibliotecas..."
	rm obj/*.o lib/*.a

mrproper: clean
	rm bin/ejercicio_7

obj/utilidades.o: src/utilidades.cpp include/utilidades.h
	g++ -c -o obj/utilidades.o -Iinclude src/utilidades.cpp

lib/libformas.a: obj/utilidades.o
	ar rvs lib/libformas.a obj/utilidades.o

obj/ejercicio7.o: src/ejercicio7.cpp include/utilidades.h
	g++ -c -o obj/ejercicio7.o -Iinclude src/ejercicio7.cpp

bin/ejercicio_7: obj/ejercicio7.o lib/libformas.a
	g++ -Llib/ -o bin/ejercicio_7 obj/ejercicio7.o -lformas
