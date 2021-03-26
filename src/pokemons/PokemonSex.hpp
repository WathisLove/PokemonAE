#ifndef POKEMONSEX_HPP
#define POKEMONSEX_HPP


enum PokemonSex{
    Sx_Male,
    Sx_Female,
    Sx_None
};


/**
 * Generate a random sex between male and female
 * @return the pokemon sex as an enum
 */
PokemonSex generateRandomSex();


#endif /* POKEMONSEX_HPP */
