#include <iostream>
#include <list>
using namespace std;
int sumaCuadrado(list<int> lista)
{
    int suma = 0;
    std::list<int>::iterator it;
    for (it = lista.begin(); it != lista.end(); ++it)
    {
        suma += (*it) * (*it);
    }
    return suma;
}
/*
    * Encontrar los conjuntos de numeros
    * que suman un numero pasado como parámetro
    */

list<int> aux;
list<list<int>> ex;
int exmal = 2000000000;
class Subset_Sum
{
public:
    // BACKTRACKING ALGORITHM
    void suma_Backtracking(int Set[], int pos, int sum, int tmpsum, int size, bool &found)
    {
        int suma;
        if (sum == tmpsum)
        {
            found = true;
            suma = sumaCuadrado(aux);
            if (suma < exmal)
            {
                exmal = suma;
                if (ex.size() > 0)
                    ex.pop_back();
                ex.push_back(aux);
            }
        }
        // generar los nodos del arbol de soluciones
        for (int i = pos; i < size; i++)
        {
            if (tmpsum + Set[i] <= sum)
            {
                tmpsum += Set[i];
                aux.push_back(Set[i]);

                // pasamos al siguiente nivel
                suma_Backtracking(Set, i + 1, sum, tmpsum, size, found);

                tmpsum -= Set[i];
                aux.pop_back();
            }
        }
    }
};

int main(int argc, char **argv)
{
    clock_t t0, t1;

    int i, n, sum;
    Subset_Sum S;
    list<list<int>> mayores;

    if (argc < 2)
    {
        cout << "Error: debe introducir un numero" << endl;
        exit(-1);
    }

    n = atoi(argv[1]);

    int a[n];

    for (i = 1; i < n; i++)
    {
        a[i] = i;
    }
    cout << endl;
    sum = n;
    bool f = false;

    t0=clock();
    S.suma_Backtracking(a, 0, sum, 0, n, f);
    t1=clock();
    
    // if (f)
    // {
    //     std::list<list<int>>::iterator it1;
    //     std::list<int>::iterator it2;

    //     cout << "El minimal es:" << exmal << endl;
    //     for (it1 = ex.begin(); it1 != ex.end(); ++it1)
    //     {
    //         cout << "[ ";
    //         for (it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
    //         {
    //             cout << *it2 << " ";
    //         }
    //         cout << "]\n";
    //     }
    //     cout << endl;
    // }
    // else
    //     cout << "Error: no se ha encontrado conjunto" << endl;

    //cout << "Tiempo: " << ((double)(t1 - t0)) / CLOCKS_PER_SEC << " s" << endl;
    cout << n << " " << ((double)(t1 - t0)) / CLOCKS_PER_SEC << endl;

}