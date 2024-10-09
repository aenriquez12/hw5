#include "pokemon.h"

// Constructor for single-type Pokemon
Pokemon::Pokemon(string name, int ndex, Type type1){
    _ndex = ndex;
    _name = name;
    type_count = 1;
    types[0] = type1;
}

// Constructor for multi-type Pokemon
Pokemon::Pokemon(string name, int ndex, Type type1, Type type2){
    _ndex = ndex;
    _name = name;
    type_count = 2;
    types[0] = type1;
    types[1] = type2;
}

// Returns the name of the Pokemon
string Pokemon::name() {
    return _name;
}

// Returns the Ndex (national index) of the Pokemon
int Pokemon::Ndex() {
    return _ndex;
}

// Returns the first type of the Pokemon
Pokemon::Type Pokemon::type1() {
    return types[0];
}

bool Pokemon::is_multitype() {
    return type_count == 2;
}

Pokemon::Type Pokemon::type2() {
    if (type_count == 2) {
        return types[1];
    } else {
        return types[0];
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

