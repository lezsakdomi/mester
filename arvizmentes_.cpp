// Feladat: Haladó / Sorozatok / Árvízmentes folyószakaszok átlagos hossza * 
// Lezsák Domonkos
// TODO add_compile_options(-std=c++11 -DDEBUG)

//#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <utility>
#include <limits>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <list>
using namespace std;

#ifndef DEBUG
#define cerr if(false) cerr
#endif

bool arviz(int meres) {
    return meres > 800;
}

struct Szakasz {
    int kezdet;
    int veg;
    Szakasz(int kezdet, int veg) : kezdet(kezdet), veg(veg) {}
};

int main() {
    map<int, int> A;
    int N; cin >> N;

    for (int i=1; i<=N; i++) {
        int meres; cin >> meres;
        A[i] = meres;
    }

    vector<Szakasz> mentes_szakaszok;
    Szakasz aktualis_szakasz(1, 0);
    bool elozo_mentes = true;
    for ( int i=1; i<=N; i++ ) {
        if ( arviz(A[i]) ) {
            elozo_mentes = false;
        } else { // i mentes
            if ( elozo_mentes ) {
                aktualis_szakasz.veg = i;
            } else { // előző árvíz
                mentes_szakaszok.push_back(aktualis_szakasz);
                aktualis_szakasz.kezdet = i;
                aktualis_szakasz.veg = i;
            }
            elozo_mentes = true;
        }
    }
    if ( elozo_mentes ) {
        mentes_szakaszok.push_back(aktualis_szakasz);
    }

    // első sor
    cout << mentes_szakaszok.size() << endl;

    if ( mentes_szakaszok.size() > 0 ) {
        // második sor
        for ( Szakasz szakasz : mentes_szakaszok ) {
            cout << szakasz.kezdet << " " << szakasz.veg << " ";
        } cout << endl;

        // harmadik sor
        for ( Szakasz szakasz : mentes_szakaszok ) {
            cout << szakasz.veg - szakasz.kezdet + 1 << " ";
        } cout << endl;

        int szum = 0;
        int cnt = 0;
        for ( Szakasz szakasz : mentes_szakaszok ) {
            szum += szakasz.veg - szakasz.kezdet + 1;
            cnt++;
        }

        // negyedik sor
        cout << (double)szum / cnt << endl;
    }
}
