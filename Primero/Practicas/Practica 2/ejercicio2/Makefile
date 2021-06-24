all: bin/ejercicio_2

clean:
	echo "Limpieza de archivos objeto y biblioteca...."
	rm obj/*.o lib/*.a

mrproper: clean
	rm bin/ejercicio_2

obj/Valor.o: src/Valor.cpp include/Valor.h
	g++ -c -o obj/Valor.o -Iinclude src/Valor.cpp

obj/utilidades.o: src/utilidades.cpp include/utilidades.h
	g++ -c -o obj/utilidades.o -Iinclude src/utilidades.cpp

lib/libformas.a: obj/Valor.o obj/utilidades.o
	ar rvs lib/libformas.a obj/Valor.o obj/utilidades.o

obj/ejercicio2.o: src/ejercicio2.cpp include/Valor.h include/utilidades.h
	g++ -c -o obj/ejercicio2.o -Iinclude src/ejercicio2.cpp

bin/ejercicio_2: obj/ejercicio2.o lib/libformas.a
	g++ -Llib/ -o bin/ejercicio_2 obj/ejercicio2.o -lformas
