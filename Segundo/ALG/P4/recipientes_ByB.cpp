#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

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

struct Nodo {

    vector<Recipiente> sol;

    vector<bool> visitados;


    bool operator<(const Nodo &otro) const {

        int tamLocal = 0, tamOtro = 0;

        for (bool visita : visitados)
            if (visita)
                tamLocal++;

        for (bool visita : otro.visitados)
            if (visita)
                tamOtro++;
        

        return (tamLocal < tamOtro and sol.size() >= otro.sol.size());
    }

    Nodo operator=(const Nodo &otro) {

        sol.clear();
        for(auto reci : otro.sol)
            sol.push_back(reci);

        visitados.clear();
        for(auto visi : otro.visitados)
            visitados.push_back(visi);

        return *this;
    }

};

int CS(vector<double> &elems) {
    vector<double> aux = elems;
    stable_sort(aux.begin(), aux.end());


    double front;
    vector<Recipiente> result;

    while (aux.size() > 0) {

        vector<double> menores = aux;
        reverse(menores.begin(), menores.end());

        front = aux[0];
        aux.erase(aux.begin());

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

    return result.size();
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

void podar(multiset<Nodo> &abiertos, int cota, int &Podas) {
    multiset<Nodo>::iterator it;
    while(!abiertos.empty() && (*abiertos.rbegin()).sol.size() >= cota) {
        it = abiertos.end();
        it--;
        abiertos.erase(it);
        Podas += 1;
    }
}

void addValorNodo(Nodo &nodo, const double elem) {
    double valor;
    Recipiente nuevo;
    nuevo.sumaElem = elem;
    nuevo.elementos.push_back(elem);
    valor = elem;
    
    if (nodo.sol.size() != 0)
        valor += nodo.sol.back().sumaElem;

    if (valor <= R && nodo.sol.size() != 0) {
        nodo.sol.back().elementos.push_back(elem);
        nodo.sol.back().sumaElem += elem;
    } else {
        nodo.sol.push_back(nuevo);
    }
}

vector<Recipiente> ByB(const vector<double> &Elementos, int &podas, int &exp, int &numVivos) {
    vector<Recipiente> sol = SolucionVoraz(Elementos);
    multiset<Nodo> Abiertos;

    int Coste = sol.size();
    const int CS = sol.size();

    Nodo inicial;
    

    inicial.visitados.assign(Elementos.size(), false);

    
    Abiertos.insert(inicial);

    while (!Abiertos.empty()) {
        Nodo x = (*Abiertos.begin());
        Abiertos.erase(Abiertos.begin());
        int count = 0;

        for (bool visita : x.visitados)
            if (visita)
                count++;

        if (count == Elementos.size()) {
            if(x.sol.size() <= Coste) {
                sol = x.sol;
                Coste = x.sol.size();
                podar(Abiertos, Coste, podas);
            }
        } else {
            exp++;
            Nodo y;
            for (int i = 0; i < Elementos.size(); i++) {
                y = x;
                if (!y.visitados[i]) {
                    y.visitados[i] = true;
                    //cout << "\nElemento a insertar: " << Elementos[i] << endl;
                    addValorNodo(y, Elementos[i]);
                    if (y.sol.size() <= CS) {
                        Abiertos.insert(y);
                    }
                }
            }
            if (numVivos < Abiertos.size())
                numVivos = Abiertos.size();
        }
        
    }

    return sol;
}

int main(int argc, char *argv[] ) {
    if (argc == 1) {
        cerr << "La forma correcta de ejecutar el programa es ./recipientes_backtracking <Tam1> <Tam2> ... <TamN>\n";
        return -1;
    }

    cout << "TamRecipiente: " << R << endl;

    vector<double> tamanios;
    for (int i = 1; i < argc; i++) {
        std::cout << argv[i] << "\t";
        tamanios.push_back(atof(argv[i]));
    }

    int podas = 0, expansiones = 0, nodosVivos = 0;

    chrono::high_resolution_clock::time_point tantes, tdespues;
    chrono::duration<double> tiempo;

    tantes = chrono::high_resolution_clock::now();

    vector<Recipiente> solucion = ByB(tamanios, podas, expansiones, nodosVivos);

    tdespues = chrono::high_resolution_clock::now();

    tiempo = chrono::duration_cast<chrono::duration<double>> (tdespues - tantes);

    std::cout << "\nSe ha tardado un tiempo de " << tiempo.count() << ".\nEl numero de podas ha sido " << podas << " y ha habido un total de " << expansiones << " expansiones.\n";
    std::cout << "Se ha llegado a un máximo de " << nodosVivos << " nodos vivos simultáneamente.\nEl resultado final ha sido el siguiente:\n" << solucion << endl;
    
}

