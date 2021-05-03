#include <list>
#include <iostream>
#include <map>
#include <random>
#include <chrono>

using namespace std;

/**
 * @class Grafo
 * 
 * @brief permite el manejo de Grafos
 * 
 * Guarda el número de nodos/vértices del Grafo y usa el algoritmoo de kruskal para encontrar el árbol de recorrido mínimo de los vértices de un grafo. 
 * 
 */
class Grafo {
    private:

        int nodes;

        multimap <int, pair<int,int> > graph;

        int *dj, *rank;

        /**
         * @brief Genera un peso aleatorio (entre -50 y 50) para una arista entre 2 vértices
         * 
         * @return Devuelve el valor del peso asociado a una arista concreta.
         */
        int generador_peso() {
            random_device rd;
            uniform_int_distribution<int> dist(-50, 50);
            return dist(rd);
        }

        /**
         * @brief Encuentra el set al que pertenece un nodo/vértice
         * 
         * @param a Nodo/vértice para el que buscar el set
         * @return Devuelve un entero con el que indicamos el set al que pertenece 
         */
        int find_set(int a) {
            if (dj[a] != a)
                return dj[a]=find_set(dj[a]);
            else
                return a;
        }

        /**
         * @brief Comprueba si una pareja pertenece al mismo set o no
         * 
         * @param pareja Pareja a comprobar
         * @return Devuelve True si pertenece al mismo set y False si no pertenecen al mismo set
         */
        bool same_set(pair<int, int> pareja) {
            return(find_set(pareja.first) == find_set(pareja.second));
        }

        /**
         * @brief Hace que una pareja de vertices quede unida, de forma que si usamos find_set llegamos a si pertenecen al mismo set o no
         * 
         * @param pareja Pareja de vertices a unir en el set
         */
        void union_set(pair<int, int> pareja){
            int x = find_set(pareja.first), y = find_set(pareja.second);
            if (rank[x]>rank[y])
                dj[y] = x;
            else {
                dj[x] = y;
                if (rank[x] == rank[y])
                    rank[y]++;
            }
        }

    public:

        Grafo() {nodes = 0;}

        /**
         * @brief Constructor especificando el número de nodos
         * 
         * @param num_nodos Número de nodos (o vértices que tiene nuestro grafo)
         */
        Grafo(int num_nodos) {
            
            pair<int, int> vertices;

            nodes = num_nodos;

            for (int i = 0; i<num_nodos; i++){
                for (int j=i+1; j<num_nodos; j++) {
                    pair<int, int> vertices(i, j);
                    int peso = generador_peso();
                    graph.emplace(make_pair(peso, vertices));
                }
            }
            
            dj = new int[nodes];
            for (int i = 0; i < nodes; i++)
                dj[i] = i;
            rank = new int[nodes];
            for (int i = 0; i < nodes; i++)
                rank[i] = 0;
        }

        /**
         * @brief Destructor de las variables dinámicas
         * 
         */
        ~Grafo() {
            delete [] dj;
            delete [] rank;
        }

        /**
         * @brief Algoritmo de Kruskal
         * 
         * @return Devuelve una lista que contiene parejas con el peso y una pareja de vertices
         */
        list< pair< int, pair<int, int> > > kruskal() {
            int vertices = 0;
            multimap <int, pair<int, int> >::iterator it=graph.begin(), it_end = graph.end();
            bool conseguido = false;

            list< pair< int, pair<int, int> > > result;

            for (it; it != it_end && !conseguido; it++) {
                pair< int, pair<int, int> > actual = *it;
                pair<int, int> UV = actual.second;
                if (!same_set(UV)) {
                    union_set(UV);
                    result.emplace_back(actual);

                    vertices++;
                    if(vertices == nodes - 1)
                        conseguido = true;
                    
                }
            }

            return result;
        }

        friend ostream & operator<<(ostream &o, Grafo &grafo);

};

//Mostrar grafos por pantalla de la siguiente manera:
//peso  (v1, v2)

ostream & operator<<(ostream &o, Grafo &grafo) {
    multimap <int, pair<int, int> >::iterator it=grafo.graph.begin(), it_end = grafo.graph.end();
    o << "El grafo es:\n";
    for (it; it != it_end; it++)
        o << (*it).first << "\t(" << (*it).second.first << ", " << (*it).second.second << ")\n";

    return o;
}

ostream & operator<<(ostream &o, list< pair< int, pair<int, int> > > camino) {
    list< pair< int, pair<int, int> > >::iterator it = camino.begin(), it_end = camino.end();
    o << "El camino mínimo está formado por:\n";
    int suma_total = 0;
    for (it; it != it_end; it++) {
        suma_total += (*it).first;
        o << (*it).first << "\t(" << (*it).second.first << ", " << (*it).second.second << ")\n";
    }

    o << "Y la suma total de los pesos es " << suma_total << endl;

    return o;

}

int main(int argc, char * argv[]) {
    
    if (argc != 2) {
        cerr << "Formato " << argv[0] << " <num_nodos>" << endl;
        return -1;
    }

    int num_nodos = atoi(argv[1]);

    Grafo grafo(num_nodos);

    chrono::high_resolution_clock::time_point tantes, tdespues;
    chrono::duration<double> tiempo;

    tantes = chrono::high_resolution_clock::now();

    grafo.kruskal();

    tdespues = chrono::high_resolution_clock::now();

    tiempo = chrono::duration_cast<chrono::duration<double>> (tdespues - tantes);

    cout << num_nodos << " " << tiempo.count() << endl;
}