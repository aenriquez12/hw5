#include "pokemon.h"  
#include <sstream>   
#include <iomanip>    

// Constructor for one type
Pokemon::Pokemon(string name, int ndex, Type type1) {
    _ndex = ndex;          // Set the ndex
    _name = name;          // Set the name
    type_count = 1;        // This Pokemon only has one type
    types[0] = type1;      // Store the first type
}

// Constructor for a two types
Pokemon::Pokemon(string name, int ndex, Type type1, Type type2) {
    _ndex = ndex;          // Set the ndex
    _name = name;          // Set the Pokemons name
    type_count = 2;        // This Pokemon has two types
    types[0] = type1;      // Store the first type
    types[1] = type2;      // Store the second type 
}


string Pokemon::name() {
    return _name;          // Return name 
}


int Pokemon::Ndex() {
    return _ndex;          // Return ndex
}


Pokemon::Type Pokemon::type1() {
    return types[0];       // Return the first type
}


bool Pokemon::is_multitype() {
    return type_count == 2;  // True if it has two types, false otherwise
}


Pokemon::Type Pokemon::type2() {
    if (type_count == 2) {   // If there's a second type,
        return types[1];     // return it.
    } else {
        return types[0];     // else just return the first type again
    }
}

float Pokemon::damage_multiplier(Type attack_type){
    float multiplier = 1.0;

    // Apply the multiplier for type1
    if (types[0] == Normal) {
        if (attack_type == Fighting) multiplier *= 2.0;
    } else if (types[0] == Fighting) {
        if (attack_type == Flying) multiplier *= 2.0;
        // Neutral damage for Poison-type attacks on Fighting types
        if (attack_type == Poison) multiplier *= 1.0;
    } else if (types[0] == Flying) {
        if (attack_type == Fighting) multiplier *= 0.5;
    } else if (types[0] == Poison) {
        if (attack_type == Fighting) multiplier *= 0.5;
        if (attack_type == Poison) multiplier *= 0.5;
    }

    // If Pokémon has a second type, apply the multiplier for type2
    if (type_count == 2) {
        if (types[1] == Normal) {
            if (attack_type == Fighting) multiplier *= 2.0;
        } else if (types[1] == Fighting) {
            if (attack_type == Flying) multiplier *= 2.0;
            // Neutral damage for Poison-type attacks on Fighting types
            if (attack_type == Poison) multiplier *= 1.0;
        } else if (types[1] == Flying) {
            if (attack_type == Fighting) multiplier *= 0.5;
        } else if (types[1] == Poison) {
            if (attack_type == Fighting) multiplier *= 0.5;
            if (attack_type == Poison) multiplier *= 0.5;
        }
    }

    return multiplier; 
}


/
Pokemon::Pokemon(string summary) {
    // Expected format: "Name, #005, type1," or "Name, #012, type1, type2,"
    
    // Find the first comma to extract the name
    size_t pos1 = summary.find(',');
    _name = summary.substr(0, pos1);

    // Find the second comma to extract the Ndex
    size_t pos2 = summary.find(',', pos1 + 1);
    string ndex_str = summary.substr(pos1 + 3, pos2 - pos1 - 3);  // Skips " #"
    _ndex = std::stoi(ndex_str);  // Convert to int

    // Find the third comma to extract the first type
    size_t pos3 = summary.find(',', pos2 + 1);
    string type1_str = summary.substr(pos2 + 2, pos3 - pos2 - 2);  // Extract type1 string
    types[0] = string_to_type(type1_str);
    type_count = 1;

    // If there is another type, extract it
    if (pos3 + 1 < summary.length()) {
        string type2_str = summary.substr(pos3 + 2, summary.length() - pos3 - 3);  // Remove the trailing comma
        types[1] = string_to_type(type2_str);
        type_count = 2;
    }
}


string Pokemon::summary() {                            // Get a string summary of the Pokémon
// Build the summary string from the Pokemons name, ndex, and types
    string result = _name + ", #" + (_ndex < 10 ? "00" : (_ndex < 100 ? "0" : "")) + std::to_string(_ndex) + ", " + type_to_string(types[0]) + ",";
    if (type_count == 2) {                             // If it has two types then include the second one
        result += " " + type_to_string(types[1]) + ",";
    }
    return result;                                     // Return the full summary string
}


string type_to_string(Pokemon::Type type) {           // Converts a Type enum to a string (so you can print it or save it)
    switch(type) {
        case Pokemon::Normal: return "Normal";
        case Pokemon::Fighting: return "Fighting";
        case Pokemon::Flying: return "Flying";
        case Pokemon::Poison: return "Poison";
        default: return "Normal";  // default case 
    }
}


Pokemon::Type string_to_type(string s) {              // Converts a string to a Type enum (so you can use it in the code)
    if (s == "Normal") return Pokemon::Normal;
    if (s == "Fighting") return Pokemon::Fighting;
    if (s == "Flying") return Pokemon::Flying;
    if (s == "Poison") return Pokemon::Poison;
    return Pokemon::Normal;                            // Default to Normal if string the names does not correspond
}
