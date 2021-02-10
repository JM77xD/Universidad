#include<set>
#include<vector>
#include<iostream>

using namespace std;

bool en_todos(vector<set<int>> &V) {
    vector<set<int>>::const_iterator it_ini = V.begin(), it_sig = V.begin(), aux;
    it_sig++;
    bool coincide = true, continuar;

    while (aux != V.end() && coincide) {
        set<int>::const_iterator set_ini = (*it_ini).begin(), set_sig;

        for (set_ini; set_ini != (*it_ini).end() && aux != V.end(); set_ini++) {
            continuar = true;

            set_sig = (*it_sig).find(*set_ini);

            aux = it_sig;

            if (set_sig == (*it_sig).end()) {
                coincide = false;
            }

            while (set_sig != (*it_sig).end() && continuar) {
                aux++;
                if (aux == V.end()) {
                    coincide = true;
                }
                set_sig = (*aux).find(*set_ini);
                if(set_sig == (*aux).end()) {
                    continuar = false;
                    coincide = false;
                }
            }


        }

    }

    return coincide;
}