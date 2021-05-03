#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>
#include <chrono>

using namespace std;

bool encontrado = false;
int posicion = -1;

double uniforme() //Genera un numero uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

void lineal(vector<int> &vector, int inicio, int fin) {
    for (int i = inicio; i < fin && !encontrado; i++) {
        if (vector.at(i) == i ) {
            encontrado = true;
            posicion = i;
        }
    }
}

void divide_venceras(vector<int> &vect, int inicio, int fin) {
    int tam = fin - inicio + 1;
    if (tam > 10 && !encontrado) {
        int half = tam/2;
        half += inicio;
        if (vect.at(half) == half) {
            encontrado = true;
            posicion = half;
        } else if(vect.at(half) > half){
            divide_venceras(vect, inicio, half);
        } else{
            divide_venceras(vect, half, fin);
        }

    } else if(!encontrado){
        lineal(vect, inicio, fin);
    }
}

int main(int argc, char * argv[]) {

    if (argc != 2) {
        cerr << "Formato " << argv[0] << " <num_elem>" << endl;
        return -1;
    }

    int n = atoi(argv[1]);
    int m=2*n-1;

    int * T = new int[n];
    assert(T);

    int * aux = new int[m];
    assert(aux);

    srand(time(0));
    //genero todos los enteros entre -(n-1) y n-1
    for (int j=0; j<m; j++) aux[j]=j-(n-1);

    //algoritmo de random shuffling the Knuth (permutacion aleatoria) 
    for (int j=m-1; j>0; j--) {
        double u=uniforme();
        int k=(int)(j*u);
        int tmp=aux[j];
        aux[j]=aux[k];
        aux[k]=tmp;
    }

    //me quedo con los n primeros del vector
    for (int j=0; j<n; j++) T[j]=aux[j];


    //Y ahora ordeno el vector T
    vector<int> myvector (T, T+n);
    vector<int>::iterator it;

    stable_sort(myvector.begin(),myvector.end());

    /*

    for (it=myvector.begin(); it!=myvector.end(); ++it)
        cout << " " << *it;

    cout << endl;
    
    */

    delete [] aux;

    chrono::high_resolution_clock::time_point tantes, tdespues;
    chrono::duration<double> tiempo;

    tantes = chrono::high_resolution_clock::now();

    divide_venceras(myvector, 0, myvector.size() - 1);

    tdespues = chrono::high_resolution_clock::now();

    tiempo = chrono::duration_cast<chrono::duration<double>> (tdespues - tantes);

    cout << n << " " << tiempo.count() << endl;

}