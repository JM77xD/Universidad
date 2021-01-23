#include<vector>
#include<list>
#include<bintree.h>
#include<iostream>

using namespace std;

int avancesHastanivel(int nivel) {
    if (nivel == 1)
        return 1;
    else
        return avancesHastanivel(nivel-1) + nivel;
}

bool esHoja()

vector<list<int>> secuenciascaminos(bintree<int> A, int nivel) {
    int avances = avancesHastanivel(nivel);
    bintree<int>::level_iterator it = A.begin_level();
    for (int i = 0; i < avances; i++)
        ++it;

    
}