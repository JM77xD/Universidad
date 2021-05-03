#include <iostream>
#include <list>

using namespace std;

double R = 1.0;

ostream & operator<<(ostream &o,list<list<double>> &container ) {
    list<list<double>>::iterator it = container.begin(), it_end = container.end();
    o << "[";
    for (it; it != it_end; it++) {
        list<double> aux = *it;
        o << "[";
        int tam = aux.size();
        for (int i = 0; i < tam; i++) {
            o << aux.front();
            aux.pop_front();
            if (aux.size() != 0)
                o << ", ";
        }
        o << "]";

    }
    o << "]\n";

    return o;
}

int main(int argc, char * argv[]) {

    list<double> elementos;
    double elem, suma = 0;
    int num_recipientes = 1;

    cout << "Introduzca los elementos de la lista (negativo o mayor que 1 para terminar, tenga en cuenta que le tam del recipiente es 1):\n";

    cin >> elem;

    while (elem > 0 && elem < 1) {
        elementos.emplace_back(elem);
        cin >> elem;
    }

    elementos.sort();
    elementos.reverse();

    list<list<double>> containers;
    list<list<double>>::iterator actual = containers.begin();

    list<double>::iterator it = elementos.begin(), it_end = elementos.end();

    list<double> aux;

    for (it; it != it_end; it++) {
        elem = *it;
        if ((suma + elem) <= R ) {
            suma += elem;
            containers.remove(aux);
            aux.push_back(elem);
            containers.push_back(aux);
        } else {
            aux.clear();
            num_recipientes++;
            suma = elem;
            aux.push_back(elem);
            containers.push_back(aux);
        }
        
    }

    cout << containers << "\nNum de recipientes: " << num_recipientes << endl;

}