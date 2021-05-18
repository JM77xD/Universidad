#include <iostream>
#include <ctime>
#include <climits>
#include <chrono>
#include <algorithm>
#include <vector>

using namespace std;

const double R = 1.000000001;

struct Recipiente {

    vector<double> elementos;

    double sumaElem = 0;

    inline bool operator<(const Recipiente &otro) {
        return sumaElem > otro.sumaElem;
    }

    Recipiente operator = (const Recipiente & otro) {
        elementos = otro.elementos;
        sumaElem = otro.sumaElem;
        return *this;
    }

};

ostream & operator<<(ostream &o, const vector<Recipiente> &container ) {
    vector<Recipiente>::const_iterator it = container.begin(), it_end = container.end();
    o << "Número de recipientes: " << container.size() << endl;
    o << "[";
    for (it; it != it_end; it++) {
        vector<double> aux = (*it).elementos;
        o << "[";
        vector<double>::iterator it = aux.begin(), it_end = aux.end();
        it_end--;
        for (it; it != aux.end(); it++) {
            o << *it;
            if (it != it_end)
                o << ", ";
        }
        o << "]";
    }
    o << "]\n";

    return o;
}

double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

vector<Recipiente> SolucionVoraz(const vector<double> &elementos) {
    vector<double> aux = elementos;
    sort(aux.begin(), aux.end());


    double front;
    vector<Recipiente> result;

    while (aux.size() > 0) {


        front = aux[0];
        aux.erase(aux.begin());

        vector<double> menores = aux;
        reverse(menores.begin(), menores.end());

        Recipiente actual;

        actual.sumaElem = front;
        actual.elementos.push_back(front);

        for (double menor : menores) {
            if (menor+actual.sumaElem <= R && aux.size() > 0){
                vector<double>::const_iterator it = aux.end();
                it--;
                aux.erase(it);
                actual.sumaElem += menor;
                actual.elementos.push_back(menor);
            }
        }

        result.push_back(actual);

    }

    return result;
}


int main(int argc, char *argv[] ) {

    if (argc != 2) {
        cerr << "La forma correcta de ejecutar el programa es ./recipientes_backtracking <NumElementos>\n";
        return -1;
    }

    //cout << "TamRecipiente: " << R << endl;

    int numElems = atoi(argv[1]);

    vector<double> tamanios;
    double valor;
    srand(time(0));

    for (int i = 0; i < numElems; i++) {
        valor = uniforme();
        //cout << valor << "\t";
        tamanios.push_back(valor);
    }

    chrono::high_resolution_clock::time_point tantes, tdespues;
    chrono::duration<double> tiempo;

    tantes = chrono::high_resolution_clock::now();

    vector<Recipiente> solucion = SolucionVoraz(tamanios);

    tdespues = chrono::high_resolution_clock::now();

    tiempo = chrono::duration_cast<chrono::duration<double>> (tdespues - tantes);

    cout << numElems << " " << tiempo.count() << endl;

}