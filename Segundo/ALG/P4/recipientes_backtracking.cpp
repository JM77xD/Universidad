#include <iostream>
#include <queue>
#include <map>
#include <list>
#include <vector>

using namespace std;

const float R = 1.00;

struct Nodo {

    list<list<float>> result;
    bool last;

    friend ostream & operator<<(ostream &o, Nodo &container);

    inline bool operator==(const Nodo &otro) {
        return result == otro.result;
    }

    inline bool operator!=(const Nodo &otro) {
        return !(*this == otro);
    }

    inline Nodo operator=(const Nodo &otro) {
        result = otro.result;
        last = otro.last;
        return *this;
    }

    inline bool operator<(const Nodo &otro) const {
        return (otro.last);
    }

};
/*
template <> struct hash<Nodo> {
	typedef Nodo argument_type;
	typedef std::size_t result_type;
	*
	 * @brief Función hash para map con clave Nodo
	 *
	std::size_t operator()(const Nodo &id) const noexcept {
		return std::hash<int>()(id.result.back().size() << 4 || id.last << 5 || id.result.size() << 9);
	}
};
*/
ostream & operator<<(ostream &o, Nodo &container ) {
    list<list<float>>::const_iterator it = container.result.begin(), it_end = container.result.end();
    o << "Se usan " << container.result.size() << " recipìentes en la siguiente configuración:\n";
    o << "[";
    for (it; it != it_end; it++) {
        list<float> aux = *it;
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

vector<pair<Nodo, int>> siguientes(const Nodo &actual, float tam, bool ultimo, int contador) {
    vector<pair<Nodo, int>> siguientes;
    
    Nodo next1, next2;
    next1 = actual;
    next2 = actual;
    int cont = contador;
    cont++;

    list<float> nueva;
    nueva.push_back(tam);

    next1.result.push_back(nueva);

    if (ultimo) {
        next1.last = true;
        next2.last = true;
    }

    if (!next2.result.empty()) {
        next2.result.back().push_back(tam);
        
        list<float>::iterator it = next2.result.back().begin();
        cout << "Valor del 1er elemento: " << *it << "\nValor del elem actual: " << tam << endl;
        float suma = 0;

        for (it; it != next2.result.back().end() && !next2.result.empty(); it++)
            suma += *it;

        if (suma <= R)
            siguientes.push_back(make_pair(next2, cont));
    }

    siguientes.push_back(make_pair(next1, cont));

    return siguientes;

}

int main (int argc, char * argv[]) {

    if (argc == 1) {
        cerr << "La forma correcta de ejecutar el programa es ./recipientes_backtracking <Tam1> <Tam2> ... <TamN>\n";
        return -1;
    }

    vector<float> tamanios;
    for (int i = 1; i < argc; i++) {
        cout << argv[i] << "\t";
        tamanios.push_back(atof(argv[i]));
    }
    cout << endl;

    map<Nodo, pair<Nodo, int>> Cerrados; //Primer nodo -> Hijo, segundo nodo ->Padre, int -> contador de la pos en el vector
    queue<pair<Nodo,int>> Abiertos;   //Nos interesa una búsqueda en profundidad
    
    int contador = 0;
    float actual;

    Nodo current{
        .last = false
    };

    Cerrados[current] = make_pair(current, contador);
    Abiertos.push(make_pair(current, contador));

    actual = tamanios[contador];

    while (!Abiertos.empty() && contador < tamanios.size()) {
        Abiertos.pop();
        cout << "Actualmente contador = " << contador << endl;
            
        for (pair<Nodo,int> next : siguientes(current, actual, contador==tamanios.size() - 1, contador)) {
            Cerrados[next.first] = make_pair(current, contador);
            Abiertos.push(next);
        }


        if (!Abiertos.empty()) {
            current = Abiertos.front().first;
            contador = Abiertos.front().second;
            actual = tamanios[contador];
        }

    }


    map<Nodo, pair<Nodo, int>>::iterator it = Cerrados.begin();

    Nodo * optimo = 0;

    for (it; it != Cerrados.end(); it++) {
        if ((*it).first.last) {
            if (!optimo) {
                optimo = new Nodo;
                *optimo = (*it).first;
            }


            if ((*it).first.result.size() < (*optimo).result.size())
                *optimo = (*it).first;
        }
    }


    cout << *optimo;

    delete optimo;

    return 0;
    
}