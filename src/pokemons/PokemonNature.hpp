#ifndef POKEMONNATURE_HPP
#define POKEMONNATURE_HPP

#include <string>

#include "attacks/StatsChanger.hpp"
#include "../Enums.hpp"


class PokemonNature {
public:
    
    
//==================// Public enum //=============//

    enum NatureID{
        Hardi, Solo, Rigide, Mauvais, Brave,
        Assure, Docile, Malin, Lache, Relax,
        Modeste, Doux, Pudique, Foufou, Discret,
        Calme, Gentil, Prudent, Bizarre, Malpoli,
        Timide, Presse, Jovial, Naif, Serieux
    };
    
//==================// Constructor //=============//
    
    
    /**
     * Constructor with a random Nature
     */
    PokemonNature();
    
    
    /**
     * Constructor with the specified pokemon nature
     * @param id the pokemon Nature as a NatureID
     */
    PokemonNature(NatureID id);
 
       
//==================// Public Methods //=============//
    
    
    /**
     * Save the Nature as a string
     * @return the string containing the saved nature
     */
    std::string saveAsString();
    
    
    /**
     * Get the nature as a formatted string
     * @return the nature as a displayable wstring
     */
    std::wstring toFormattedString();
    
    
    /**
     * Get the nature as a formatted string
     * @param natureID the Nature ID
     * @return the nature as a displayable wstring
     */
    static std::wstring toFormattedString(NatureID id);
        
    
//==================// Getters //=============//
        
    
    /**
     * Check if the Pokemon nature has an effect on some statistics
     * @return true if one of the stat is highered and another lowered
     */
    bool isChangingStat() const;
    
    /**
     * Get which statistc is highered by the Nature
     * @warning throws an exception if there are none
     * @return the StatName of the highered stat
     */
    StatName getHigheredStat() const;
    
    
    /**
     * Get which statistc is lowered by the Nature
     * @warning throws an exception if there are none
     * @return the StatName of the lowered stat
     */
    StatName getLoweredStat() const; 
    
    
private:
    
//==================// Static Attributes //=============//

    
    // Tab for the Highered stats 
    // (neutral natures have same values in both tabs)
    static const StatName higheredTab [];
    
    
    // Tab for the Lowered stats 
    static const StatName loweredTab [];
    
//==================// Attributes //=============//
    
    // The Nature ID
    NatureID m_id;
    
};

#endif /* POKEMONNATURE_HPP */

