#ifndef TEAMENUM_HPP
#define TEAMENUM_HPP


/**
 * Set the wether the pokemon should be displayed as an ennemy or an allied
 */
enum Team{
    allied,
    ennemy
};


/**
 * Name of the differents statistics of a pokemon
 */
enum StatName{
    health,
    attack,
    defense,
    special_attack,
    special_defense,
    speed,
    evasion,
    accuracy
};



enum MovementType{
    NoMove,
    GoUp,
    GoRight,
    GoDown,
    GoLeft,
    LookUp,
    LookRight,
    LookDown,
    LookLeft
};



enum ReactionType{
    RSmile,
    RSad,
    RSurprised,
    RHeart,
    RExclamation
};



enum class MainStatusName{
    NoMainStatus,
    Burn,
    Freeze,
    Paralysis,
    Poison,
    BadlyPoison,
    Sleep
};



enum XPCurveType{
    XP_Erratic,
    XP_Fast,
    XP_MediumFast,
    XP_MediumSlow,
    XP_Slow,
    XP_Fluctuating
};



enum class StrategicRole{
    DEFAULT,
    WALL_BREAKER, 
    SUICIDE_LEAD,
};



enum class BonusType{
    Additive,
    Multiplicative
};


#endif /* TEAMENUM_HPP */