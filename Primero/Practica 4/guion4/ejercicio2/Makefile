all: bin/ejercicio2

clean:
	rm obj/*.o lib/*.a

mrproper: clean
	rm bin/ejercicio2

obj/punto.o: src/punto.cpp include/punto.h
	g++ -c -o obj/punto.o -Iinclude src/punto.cpp

obj/polilinea.o: src/polilinea.cpp include/punto.h include/polilinea.h
	g++ -c -o obj/polilinea.o -Iinclude src/polilinea.cpp

obj/utilidades.o: src/utilidades.cpp include/punto.h include/polilinea.h include/utilidades.h
	g++ -c -o obj/utilidades.o -Iinclude src/utilidades.cpp

lib/libformas.a: obj/punto.o obj/polilinea.o obj/utilidades.o
	ar rvs lib/libformas.a obj/polilinea.o obj/punto.o obj/utilidades.o

obj/ejercicio2.o: src/ejercicio2.cpp include/punto.h include/polilinea.h include/utilidades.h
	g++ -c -o obj/ejercicio2.o -Iinclude src/ejercicio2.cpp

bin/ejercicio2: obj/ejercicio2.o lib/libformas.a
	g++ -Llib/ -o bin/ejercicio2 obj/ejercicio2.o -lformas