#include<list>
#include<set>
#include<iostream>

using namespace std;

bool proper_subset(const list<set<int>> &L) {

    list<set<int>>::const_iterator it_ini = L.begin(), it_sig = L.begin();
    it_sig++;
    bool coincide = true;
    while (it_sig != L.end() && coincide) {
        int coincidencias = 0;
        set<int>::const_iterator set_ini= (*it_ini).begin(), set_sig = (*it_sig).begin();

        for (set_ini; set_ini != (*it_ini).end() && *it_ini != *it_sig; set_ini++) {
            for (set_sig; set_sig != (*it_sig).end(); set_sig++) {
                if (*set_ini == *set_sig)
                    coincidencias++;
            }
        }

        if (coincidencias < (*it_ini).size())
            coincide = false;
        it_ini++;
        it_sig++;
    }

    return coincide;

}