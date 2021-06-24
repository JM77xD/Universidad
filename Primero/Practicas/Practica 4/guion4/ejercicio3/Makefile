all: bin/ejercicio3

clean:
	rm obj/*.o lib/*.a

mrproper: clean
	rm bin/ejercicio3

obj/valor.o: src/valor.cpp include/valor.h
	g++ -c -o obj/valor.o -Iinclude src/valor.cpp

obj/matrizdispersa.o: src/matrizdispersa.cpp include/valor.h include/matrizdispersa.h
	g++ -c -o obj/matrizdispersa.o -Iinclude src/matrizdispersa.cpp

obj/utilidades.o: src/utilidades.cpp include/utilidades.h include/valor.h include/matrizdispersa.h
	g++ -c -o obj/utilidades.o -Iinclude src/utilidades.cpp

lib/libformas.a: obj/valor.o obj/matrizdispersa.o obj/utilidades.o
	ar rvs lib/libformas.a obj/matrizdispersa.o obj/valor.o obj/utilidades.o

obj/ejercicio3.o: src/ejercicio3.cpp include/valor.h include/matrizdispersa.h include/utilidades.h
	g++ -c -o obj/ejercicio3.o -Iinclude src/ejercicio3.cpp

bin/ejercicio3: obj/ejercicio3.o lib/libformas.a
	g++ -Llib/ -o bin/ejercicio3 obj/ejercicio3.o -lformas