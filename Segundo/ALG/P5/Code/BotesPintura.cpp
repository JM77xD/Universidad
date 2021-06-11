#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

struct Botes {
    int capacidad;
    int NumDisp;
    int coste;
};

pair<int,vector<int>> AlgoritmoDinamico(vector<Botes> &Botes, const int numLitros) {

    int CantMax = 0;
    for (auto botecito : Botes) {
        CantMax += botecito.capacidad*botecito.NumDisp;
    }

    if (CantMax < numLitros) {
        cerr << "No se puede satisfacer el pedido\n";
        exit(-1);
    }
    int **matrizCoste, **matrizRecipientes;

    matrizCoste = new int*[Botes.size()];
    matrizRecipientes = new int*[Botes.size()];
    for (int k = 0; k < Botes.size(); k++) {
        matrizCoste[k] = new int[numLitros+1];
        matrizRecipientes[k] = new int[numLitros+1];
    }

    int i, j, costeFinal;

    for (i = 0; i < Botes.size(); i++) {

        int costeActual = Botes[i].coste, capacidadActual = Botes[i].capacidad, numBotes = Botes[i].NumDisp, k;

        for (j = 0; j <= numLitros; j++) {
            
            if (j == 0) {
                
                matrizCoste[i][j] = 0;
                matrizRecipientes[i][j] = 0;

            } else if (i == 0) {
                if (j > capacidadActual*numBotes) {
                    matrizCoste[i][j] = 9999999;
                    matrizRecipientes[i][j] = 0;
                } else if (j > (matrizCoste[i][j-1]/costeActual)*capacidadActual) {
                    matrizCoste[i][j] = matrizCoste[i][j-1] + costeActual;
                    matrizRecipientes[i][j] = matrizRecipientes[i][j-1]+1;
                } else {
                    matrizCoste[i][j] = matrizCoste[i][j-1];
                    matrizRecipientes[i][j] = matrizRecipientes[i][j-1];
                }

            } else {
                if (j < capacidadActual) {
                    
                    if (min(matrizCoste[i-1][j], costeActual) == costeActual) {
                        matrizCoste[i][j] = costeActual;
                        matrizRecipientes[i][j] = 1;
                    } else {
                        matrizCoste[i][j] = matrizCoste[i-1][j];
                        matrizRecipientes[i][j] = 0;
                    }

                } else {
                    
                    matrizCoste[i][j] = matrizCoste[i-1][j];
                    matrizRecipientes[i][j] = 0;

                    for (k = 1; j >= capacidadActual*k && k <= numBotes; k++) {

                        if (matrizCoste[i-1][j-k*capacidadActual] + costeActual*k < matrizCoste[i][j]) {
                            matrizCoste[i][j] = matrizCoste[i-1][j-k*capacidadActual] + costeActual*k;
                            matrizRecipientes[i][j] = k;
                        }
                    }
                }
            }
        }
    }


    i = Botes.size()-1;
    j = numLitros;
    costeFinal = matrizCoste[i][j];

    vector<int> sol;

    for (int k = 0; k < Botes.size(); k++)
        sol.push_back(0);

    while ( j > 0) {

        if (matrizRecipientes[i][j] == 0) {
            if (i-1 < 0)
                break;
            else
                i--;
        } else {
            sol[i] = matrizRecipientes[i][j];
            j -= matrizRecipientes[i][j]*Botes[i].capacidad;
            i -= 1;
        }
    }

    for (int k = 0; k < Botes.size(); k++) {
        delete [] matrizCoste[k];
        delete [] matrizRecipientes[k];
    }
    delete [] matrizCoste;
    delete [] matrizRecipientes;

    return make_pair(costeFinal, sol);


}

int main (int argc, char * argv[]) {
    if (argc != 2) {
        cerr << "Ejecute el programa como ./<ejecutable> <numLitros>\n";
        return -1;
    }
    int numLitros = atoi(argv[1]);
    if (numLitros < 0) {
        cerr << "El número de litros introducido no puede ser negativo\n";
        return -1;
    }
    vector<Botes> Recipientes;
    Botes bote1 {
        .capacidad = 3,
        .NumDisp = 9,
        .coste = 5
    };
    Botes bote2 {
        .capacidad = 5,
        .NumDisp = 8,
        .coste = 9
    };
    Botes bote3 {
        .capacidad = 7,
        .NumDisp = 5,
        .coste = 12
    };
    Botes bote4 {
        .capacidad = 9,
        .NumDisp = 10,
        .coste = 15
    };
    Recipientes.push_back(bote1);
    Recipientes.push_back(bote2);
    Recipientes.push_back(bote3);
    Recipientes.push_back(bote4);

    chrono::high_resolution_clock::time_point tantes, tdespues;
    chrono::duration<double> tiempo;

    tantes = chrono::high_resolution_clock::now();

    pair<int,vector<int>> solucion = AlgoritmoDinamico(Recipientes, numLitros);

    tdespues = chrono::high_resolution_clock::now();

    tiempo = chrono::duration_cast<chrono::duration<double>> (tdespues - tantes);
    
    cout << "El coste total para " <<  numLitros << " litros es: " << solucion.first << "\nEl número de botes de cada tipo es:\n";
    for (int i = 0; i < solucion.second.size(); i++) {
        cout << "Bote de " << Recipientes[i].capacidad << " litros:\t" << solucion.second[i] << endl;
    }
    cout << "El tiempo de ejecución ha sido:\t" << tiempo.count() << endl;
    
    //cout << numLitros << " " << tiempo.count() << endl;
}