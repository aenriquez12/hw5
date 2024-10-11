#include "pokedex.h"
#include "pokemon.h"
#include <fstream>
#include <iostream>


Pokedex::Pokedex() {
    for (int i = 0; i < 1000; ++i) {                          
        A[i] = nullptr;
    }
}

Pokedex::Pokedex(string filename) : Pokedex() {
    ifstream infile(filename);
    if(!infile){
        return;
    }
    string line;
    while(getline(infile, line)){
        Pokemon* p= new Pokemon(line);
        int ndex = p->Ndex();
        if(ndex>=0 && ndex < 1000){
            A[ndex] = p;
        }
    }
   infile.close();
}

void Pokedex::save(string filename) {
    ofstream outfile(filename);
    if(!outfile){
        return;
    }
    for (int i = 0; i < 1000; ++i) {
        if (A[i] != nullptr) {
            outfile << A[i]->summary() << endl;
        }
    }
    outfile.close();
}

void Pokedex::add(Pokemon* p) {
    if (p->Ndex() >= 0 && p->Ndex() < 1000) {
        A[p->Ndex()] = p;
    }
}

void Pokedex::remove(Pokemon* p) {
    if (p->Ndex() >= 0 && p->Ndex() < 1000) {
        A[p->Ndex()] = nullptr;
         
    }
}

Pokemon* Pokedex::lookup_by_name(string name) {
    for (int i = 0; i < 1000; ++i) {
        if (A[i] != nullptr && A[i]->name() == name) {
            return A[i];
        }
    }
    return nullptr;
}

Pokemon* Pokedex::lookup_by_Ndex(int ndex) {
    if (ndex >= 0 && ndex < 1000) {
        return A[ndex];
    }
    return nullptr;
}

int Pokedex::size() {
    int count = 0;
    for (int i = 0; i < 1000; ++i) {
        if (A[i] != nullptr) {
            count++;
        }
    }
    return count;
}
