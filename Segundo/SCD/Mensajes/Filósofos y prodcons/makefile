.SUFFIXES:
.PHONY:    pc,pc2,pcm,fp,f,fi,fc,clean

compilador := mpicxx -std=c++11
flagsc     := -g -Wall

pcm: prodcons2-mu_exe
	mpirun --oversubscribe -np  4 ./$<

f: filosofos_exe
	mpirun --use-hwthread-cpus --oversubscribe -np 10 ./$<

fc: filosofos-cam_exe
	mpirun --use-hwthread-cpus --oversubscribe -np 11 ./$<

%_exe: %.cpp
	$(compilador) $(flagsc) -o $@ $<

clean:
	rm -rf *_exe *.dSYM
