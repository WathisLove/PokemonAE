#ifndef ITEMENUMS_HPP
#define ITEMENUMS_HPP


/**
 * An enum that stores the IDs of the items
 */
enum class ItemID{
    // PV
    potion,
    superPotion,
    hyperPotion,
    maxPotion,
    fullRestore,
    eauFraiche,
    sodaCool,
    limonade,
    laitMeumeu,
    
    // PP
    huile,
    huileMax,
    elixir,
    maxElixir,
    
    // Status
    antidote,
    antiPara,
    antiBrule,
    antiGel,
    reveil,
    totalSoin,
    
    // KO
    rappel,
    rappelMax,
    
    // Balls
    pokeball,
    superball,
    hyperball,
    
    // Berries
    berryOran,
    berryCeriz,
    berryMaron,
    berryPecha,
    berryFraive,
    berryWillia,
    berryKika,
    berryMepo,
    berryPrine,
    berrySitrus,
    
    // CT
    ct1, ct2, ct3, ct4, ct5, ct6, ct7, ct8, ct9,
    
    
    // Evolution stones
    pierreEclat,
    pierreNuit,
    pierreEau,
    pierreAube,
    pierreLune,
    pierreFeu,
    pierreFoudre,
    pierrePlante,
    
    // Training Items
    poignPouv,
    ceintPouv,
    lentPouv,
    bandPouv,
    chainePouv,
    poidsPouv,
    bracMacho,
    
    // Money and XP
    pieceRune,
    encensVeine,
    oeufChance,
    grelotZen,
    multiExp,
            
    // Meteo Boosters
    rocheHumide,
    rocheChaude,
    rocheLisse,
    rocheGlace,
    
    // Evolu Items
    evoluRoc,
    
    // Type boosters
    crocDragon,
    mouchSoie,
    encensMer,
    encensFleur,
    grainMiracl,
    encensVague,
    encensRoc,
    bizarEncens,
    charbon,
    cuillertordu,
    sableDoux,
    pierreDure,
    lunetNoires,
    poudreArg,
    ceintNoire,
    aimant,
    eauMystique,
    becPointu,
    peauMetal,
    picVenin,
    runeSort,
    glaceEternel,
    
    // Last item
    LAST_ITEM
};


/**
 * Item category in the bag
 */
enum class ItemCategory{
    Object,
    Medecine,
    Pokeball,
    Berry,
    CT,
    RareObject
};


/**
 * Usability out of battle
 */
enum class UseOutBattle{
    CANNOT_USE,
    CONSUMED_ON_ATTACK, // Use on an attack and consume on use
    CONSUMED_ON_USE, // Consumed on use on a pokemon
    NOT_ON_POKEMON, // Can be used but not on a pokemon
    TEACH_MOVE, // Teach Move
    USABLE, // Can be used and not be consumed
};


/**
 * Usability in battle 
 */
enum class UseInBattle{
    CANNOT_USE,
    POKEBALL,
    FLEE_ITEM,
    HOLD_CONSUMABLE,
    HOLD_ITEM,
    CONSUMED_ON_ATTACK,
    CONSUMED_ON_USE, // Usable and consumed on use
    USABLE_ON_POKEMON, // Usable on pokemon but do not consume
    USABLE
};


#endif /* ITEMENUMS_HPP */

