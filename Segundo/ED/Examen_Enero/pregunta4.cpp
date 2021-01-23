#include<iostream>
#include<vector>
#include<list>

using namespace std;

class matrizSingular {

    private:

        vector<list<unsigned int>> datos;


    public:

        matrizSingular(const matrizSingular &otra) {
            datos = otra.datos;
        }

        matrizSingular() = default;

        matrizSingular(const vector<list<unsigned int>> &listaNum ) {
            datos = listaNum;
        }

        unsigned int & operator()(int fila, int col) {
            list<unsigned int> filaCorrespondiente = datos[fila];

            list<unsigned int>::iterator it = filaCorrespondiente.begin();

            //Suponemos que empezamos a contar desde la columna 0
            for (int i = 0; i < col; i++)
                it++;

            return *it;
        }

        class iterator_impar {

            private:
                vector<list<unsigned int>>::iterator it_fila;

                list<unsigned int>::iterator it_col;

            public:

                iterator_impar() {}

                iterator_impar(const vector<list<unsigned int>>::iterator &fila, list<unsigned int>::iterator &col) {
                    it_fila = fila;
                    it_col = col;
                }

                iterator_impar(const iterator_impar &otro) {
                    it_fila = otro.it_fila;
                    it_col = otro.it_col;
                }

                iterator_impar & operator = (const iterator_impar &otro) {
                    it_fila = otro.it_fila;
                    it_col = otro.it_col;
                    return *this;
                }

                unsigned int & operator *() {
                    return *it_col;
                }

                bool operator==(const iterator_impar & otro) {
                    return it_fila == otro.it_fila && it_col == otro.it_col;
                }

                bool operator!=(const iterator_impar & otro) {
                    return it_fila != otro.it_fila && it_col != otro.it_col;
                }

                iterator_impar & operator++() {
                    it_col++;

                    while (it_fila != datos.end() && *it_col %2 != 1) {
                        while (it_col != (*it_fila).end() && *it_col %2 != 1) {
                            it_col++;
                        }
                        it_fila++;
                        it_col = (*it_fila).begin();
                    }

                    return *this;
                }

                iterator_impar & operator++() {
                    if (it_col != (*it_fila).begin())
                        it_col--;

                    while (it_fila != datos.begin() && *it_col %2 != 1) {
                        while (it_col != (*it_fila).begin() && *it_col %2 != 1) {
                            it_col--;
                        }
                        it_fila--;
                        it_col = (*it_fila).end();
                    }

                    return *this;
                }

                friend class matrizSingular;
        };

        iterator_impar & begin() {
            vector<list<unsigned int>>::iterator it_fila = datos.begin();

            list<unsigned int>::iterator it_col = (*it_fila).begin();

            while (it_fila != datos.end() && *it_col %2 != 1) {
                while (it_col != (*it_fila).end() && *it_col %2 != 1) {
                    it_col++;
                }
                it_fila++;
                it_col = (*it_fila).begin();
            }

            iterator_impar nuevo(it_fila, it_col);

            return nuevo;

        }

        iterator_impar & end() {
            vector<list<unsigned int>>::iterator it_fila = datos.end();

            list<unsigned int>::iterator it_col = (*it_fila).end();

            while (it_fila != datos.begin() && *it_col %2 != 1) {
                while (it_col != (*it_fila).begin() && *it_col %2 != 1) {
                    it_col--;
                }
                it_fila--;
                it_col = (*it_fila).end();
            }

            iterator_impar nuevo(it_fila, it_col);

            return nuevo;
            
        }

};