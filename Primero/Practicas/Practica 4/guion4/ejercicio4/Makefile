all: bin/ejercicio4

clean:
	rm obj/*.o lib/*.a

mrproper: clean
	rm bin/ejercicio4

obj/pareja.o: src/pareja.cpp include/pareja.h
	g++ -c -o obj/pareja.o -Iinclude src/pareja.cpp

obj/precuencias.o: src/precuencias.cpp include/precuencias.h include/pareja.h
	g++ -c -o obj/precuencias.o -Iinclude src/precuencias.cpp

obj/utilidades.o: src/utilidades.cpp include/pareja.h include/utilidades.h include/precuencias.h
	g++ -c -o obj/utilidades.o -Iinclude src/utilidades.cpp

lib/libformas.a: obj/utilidades.o obj/pareja.o obj/precuencias.o
	ar rvs lib/libformas.a obj/utilidades.o obj/pareja.o obj/precuencias.o

obj/ejercicio4.o: src/ejercicio4.cpp include/pareja.h include/utilidades.h include/precuencias.h
	g++ -c -o obj/ejercicio4.o -Iinclude src/ejercicio4.cpp

bin/ejercicio4: obj/ejercicio4.o lib/libformas.a
	g++ -Llib/ -o bin/ejercicio4 obj/ejercicio4.o -lformas