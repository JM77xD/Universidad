all: bin/ejercicio1

clean:
	rm obj/*.o lib/*.a

mrproper: clean
	rm bin/ejercicio1

obj/bigint.o: src/bigint.cpp include/bigint.h
	g++ -c -o obj/bigint.o -Iinclude src/bigint.cpp

obj/utilidades.o: src/utilidades.cpp include/bigint.h include/utilidades.h
	g++ -c -o obj/utilidades.o -Iinclude src/utilidades.cpp

lib/libformas.a: obj/utilidades.o obj/bigint.o
	ar rvs lib/libformas.a obj/utilidades.o obj/bigint.o

obj/ejercicio1.o: src/ejercicio1.cpp include/bigint.h include/utilidades.h
	g++ -c -o obj/ejercicio1.o -Iinclude src/ejercicio1.cpp

bin/ejercicio1: obj/ejercicio1.o lib/libformas.a
	g++ -Llib/ -o bin/ejercicio1 obj/ejercicio1.o -lformas