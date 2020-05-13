#ifndef menu_h
#define menu_h

#include <iostream>
#include <cstring>
using namespace std;

class Menu{
    private:
       char *titulo;
       int nopc;
       char **opc;
        
    public:

        Menu();
        Menu(const char *titulo, const char *opcion);
        Menu(const Menu &copia);
        ~Menu();
        void setTitulo(const char * titulo);
        void setNumeroOpciones(int nopc);
        const char * getTitulo();
        int getNumeroOpciones();
        void agregarOpcion(const char * nuevaOpcion);
        friend ostream & operator << ( ostream &os, Menu &m);            
};

#endif