all: bin/ejercicio_5

clean:
	echo "Limpieza de archivos objeto y bibliotecas..."
	rm obj/*.o lib/*.a

mrproper: clean
	rm bin/ejercicio_5

obj/utilidades.o: src/utilidades.cpp include/utilidades.h
	g++ -c -o obj/utilidades.o -Iinclude src/utilidades.cpp

lib/libformas.a: obj/utilidades.o
	ar rvs lib/libformas.a obj/utilidades.o

obj/ejercicio5.o: src/ejercicio5.cpp include/utilidades.h
	g++ -c -o obj/ejercicio5.o -Iinclude src/ejercicio5.cpp

bin/ejercicio_5: obj/ejercicio5.o lib/libformas.a
	g++ -Llib/ -o bin/ejercicio_5 obj/ejercicio5.o -lformas
