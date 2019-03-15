// Feladat: Haladó / Sorozatok / Állatkertek * 
// Lezsák Domonkos
// TODO add_compile_options(-std=c++11 -DDEBUG)

#include <bits/stdc++.h>
using namespace std;

int m, n, k, l;
struct Allatfaj {
    string name;
    Allatfaj(string name) : name(name) {}
    int kuk_van=0;
    int rat_van=0;
    bool cserelheto(){
        return (kuk_van>=k) && (rat_van>=k);
    }
    bool kuk_adhato(){
        return (kuk_van>=l) && (rat_van==0);
    }
    bool rat_adhato(){
        return (kuk_van==0) && (rat_van>=l);
    }
};

map<string, Allatfaj*> fajok;
Allatfaj* faj(string name){
    if (fajok.find(name)==fajok.end()) {
        fajok[name]=new Allatfaj(name);
    }
    return fajok[name];
}

int main()
{
    cin>>n;
    for (int i=0; i<n; i++) {
        string name; cin>>name;
        Allatfaj* f=faj(name);
        cin>>f->kuk_van;
    }

    cin>>m;
    for (int i=0; i<m; i++) {
        string name; cin>>name;
        Allatfaj* f=faj(name);
        cin>>f->rat_van;
    }

    cin>>k>>l;
    cerr<<"THanks!"<<endl;

    for (auto f : fajok) cerr<<']'<<f.second->name<<' '<<f.second->kuk_van<<' '<<f.second->rat_van<<endl;

    for (auto f : fajok) if (f.second->cserelheto()) cout<<f.second->name<<' '; cout<<endl;
    for (auto f : fajok) if (f.second->kuk_adhato()) cout<<f.second->name<<' '; cout<<endl;
    for (auto f : fajok) if (f.second->rat_adhato()) cout<<f.second->name<<' '; cout<<endl;

    return 0;
}
