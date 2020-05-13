all: bin/ejercicio4

clean:
	echo "Limpieza de archivos objeto y bibliotecas..."
	rm obj/*.o lib/*.a

mrproper: clean
	rm bin/ejercicio4

obj/celda.o: src/celda.cpp include/celda.h
	g++ -c -o obj/celda.o -Iinclude src/celda.cpp

obj/lista.o: src/lista.cpp include/lista.h include/celda.h
	g++ -c -o obj/lista.o -Iinclude src/lista.cpp

lib/libformas.a: obj/lista.o obj/celda.o
	ar rvs lib/libformas.a obj/lista.o obj/celda.o

obj/ejercicio4.o: src/ejercicio4.cpp include/lista.h include/celda.h
	g++ -c -o obj/ejercicio4.o -Iinclude src/ejercicio4.cpp

bin/ejercicio4: obj/ejercicio4.o lib/libformas.a
	g++ -Llib/ -o bin/ejercicio4 obj/ejercicio4.o -lformas