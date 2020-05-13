all: bin/ejercicio6

clean:
	echo "Limpieza de archivos objeto y bibliotecas..."
	rm obj/*.o lib/*.a

mrproper: clean
	rm bin/ejercicio6

obj/columnas.o: src/columnas.cpp include/columnas.h
	g++ -c -o obj/columnas.o -Iinclude src/columnas.cpp

obj/fila.o: src/fila.cpp include/fila.h include/columnas.h
	g++ -c -o obj/fila.o -Iinclude src/fila.cpp

obj/matriz2d.o: src/matriz2d.cpp include/fila.h include/columnas.h include/matriz2d.h
	g++ -c -o obj/matriz2d.o -Iinclude src/matriz2d.cpp

lib/libformas.a: obj/columnas.o obj/fila.o obj/matriz2d.o
	ar rvs lib/libformas.a obj/columnas.o obj/fila.o obj/matriz2d.o

obj/ejercicio6.o: src/ejercicio6.cpp include/fila.h include/columnas.h include/matriz2d.h
	g++ -c -o obj/ejercicio6.o -Iinclude src/ejercicio6.cpp

bin/ejercicio6: obj/ejercicio6.o lib/libformas.a
	g++ -Llib/ -o bin/ejercicio6 obj/ejercicio6.o -lformas