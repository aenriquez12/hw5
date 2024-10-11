#include "pokedex.h"
#include "pokemon.h"
#include <fstream>
#include <iostream>


Pokedex::Pokedex() {
    for (int i = 0; i < 1000; ++i) {                // Loop through all 1000 possible Pokemon slots
        A[i] = nullptr;                             // Set each slot to nullptr
    }
}

Pokedex::Pokedex(string filename) : Pokedex() {
    ifstream infile(filename);                      // open the file to read the Pokedex
    if (!infile) {                                  // If the file cant be opened, just return
        return;
    }
    string line;
    while (getline(infile, line)) {
        Pokemon* p = new Pokemon(line);            // Create a new Pokemon object using the line data
        int ndex = p->Ndex();                      // Get the Pokemons ndex
        if (ndex >= 0 && ndex < 1000) {            // If the ndex is within valid bounds
            A[ndex] = p;                           // Store the Pokemon in the correct spot in the pokedex
        }
    }
    infile.close();                                // Close the file once done
}

void Pokedex::save(string filename) {
    ofstream outfile(filename);                    // Open the file to write
    if (!outfile) {                                // If the file cant be opened, then return
        return;
    }
    for (int i = 0; i < 1000; ++i) {                // Loop through all 1000 slots in the Pokedex
        if (A[i] != nullptr) {                     // If there is a Pokemon in this slot
            outfile << A[i]->summary() << endl;    // Write the Pokemons data to the file
        }
    }
    outfile.close();                               // Close the file after saving
}

void Pokedex::add(Pokemon* p) {
    if (p->Ndex() >= 0 && p->Ndex() < 1000) {      // Check if the ndex is good
        A[p->Ndex()] = p;                          // Add the Pokemon to the correct slot in the Pokedex
    }
}

void Pokedex::remove(Pokemon* p) {
    if (p->Ndex() >= 0 && p->Ndex() < 1000) {      // Check if the ndex is good
        A[p->Ndex()] = nullptr;                    // Remove the Pokemon by setting its slot to nullptr
    }
}

Pokemon* Pokedex::lookup_by_name(string name) {
    for (int i = 0; i < 1000; ++i) {              // Loop through all slots in the Pokedex
        if (A[i] != nullptr && A[i]->name() == name) {  // If we find a matching name
            return A[i];                          // Return the Pokemon
        }
    }
    return nullptr;                               // If no match is found, return nullptr
}

Pokemon* Pokedex::lookup_by_Ndex(int ndex) {
    if (ndex >= 0 && ndex < 1000) {               // Check if the ndex is good
        return A[ndex];                           // Return the Pokemon in on the correct place
    }
    return nullptr;                               // If wrong Ndex or no Pokemon found, then return nullptr
}

int Pokedex::size() {
    int count = 0;                                // Initialize a counter to 0
    for (int i = 0; i < 1000; ++i) {              // Loop through all slots in the Pokedex
        if (A[i] != nullptr) {                    // If a slot has a Pokemon
            count++;                              // Increment the counter
        }
    }
    return count;                                  // Return the total count of Pokemon in the Pokedex
}
