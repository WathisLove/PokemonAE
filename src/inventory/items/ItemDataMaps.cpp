/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "../Item.hpp"


const std::map<ItemID, sf::String> Item::itemNames = {
    // LAST ITEM
    {ItemID::LAST_ITEM, sf::String("~ Unknown Name ~")},
    
    // Potions Names
    {ItemID::potion, sf::String(L"Potion")},
    {ItemID::superPotion, sf::String(L"Super Potion")},
    {ItemID::hyperPotion, sf::String(L"Hyper Potion")},
    {ItemID::maxPotion, sf::String(L"Potion Max")},
    {ItemID::fullRestore, sf::String(L"Guérison")},
    {ItemID::eauFraiche, sf::String(L"Eau Fraiche")},
    {ItemID::sodaCool, sf::String(L"Soda Cool")},
    {ItemID::limonade, sf::String(L"Limonade")},
    {ItemID::laitMeumeu, sf::String(L"Lait Meumeu")},

    // Rappels
    {ItemID::rappel, sf::String(L"Rappel")},
    {ItemID::rappelMax, sf::String(L"Rappel Max")},

    // Other Medicines
    {ItemID::huile, sf::String(L"Huile")},
    {ItemID::huileMax, sf::String(L"Huile Max")},
    {ItemID::elixir, sf::String(L"Elixir")},
    {ItemID::maxElixir, sf::String(L"Max Elixir")},
    {ItemID::antidote, sf::String(L"Antidote")},
    {ItemID::antiPara, sf::String(L"Anti-Para")},
    {ItemID::antiBrule, sf::String(L"Anti-Brule")},
    {ItemID::antiGel, sf::String(L"Anti-Gel")},
    {ItemID::reveil, sf::String(L"Réveil")},
    {ItemID::totalSoin, sf::String(L"Total Soin")},

    // Pokeball names
    {ItemID::pokeball, sf::String(L"Poke Ball")},
    {ItemID::superball, sf::String(L"Super Ball")},
    {ItemID::hyperball, sf::String(L"Hyper Ball")},


    // Berry names
    {ItemID::berryOran, sf::String(L"Baie Oran")},
    {ItemID::berryCeriz, sf::String(L"Baie Cerriz")},
    {ItemID::berryMaron, sf::String(L"Baie Maron")},
    {ItemID::berryPecha, sf::String(L"Baie Pecha")},
    {ItemID::berryFraive, sf::String(L"Baie Fraive")},
    {ItemID::berryWillia, sf::String(L"Baie Willia")},
    {ItemID::berryKika, sf::String(L"Baie Kika")},
    {ItemID::berryMepo, sf::String(L"Baie Mepo")},
    {ItemID::berryPrine, sf::String(L"Baie Prine")},
    {ItemID::berrySitrus, sf::String(L"Baie Sitrus")},
    
    // CT
    {ItemID::ct1, sf::String("CT 1")},
    {ItemID::ct2, sf::String("CT 2")},
    {ItemID::ct3, sf::String("CT 3")},
    {ItemID::ct4, sf::String("CT 4")},
    {ItemID::ct5, sf::String("CT 5")},
    {ItemID::ct6, sf::String("CT 6")},
    {ItemID::ct7, sf::String("CT 7")},
    {ItemID::ct8, sf::String("CT 8")},
    {ItemID::ct9, sf::String("CT 9")},
    
        
    // Evolution Stones
    {ItemID::pierreEclat, "Pierre Eclat"},
    {ItemID::pierreNuit, "Pierre Nuit"},
    {ItemID::pierreEau, "Pierre Eau"},
    {ItemID::pierreAube, "Pierre Aube"},
    {ItemID::pierreLune, "Pierre Lune"},
    {ItemID::pierreFeu, "Pierre Feu"},
    {ItemID::pierreFoudre, "Pierre Foudre"},
    {ItemID::pierrePlante, "Pierre Plante"},
    
    // Training Items
    {ItemID::poignPouv, sf::String("Poignet Pouvoir")},
    {ItemID::ceintPouv, sf::String("Ceinture Pouvoir")},
    {ItemID::lentPouv, sf::String("Anneau Pouvoir")},
    {ItemID::bandPouv, sf::String("Bandeau Pouvoir")},
    {ItemID::chainePouv, sf::String(L"Chaîne. Pouvoir")},
    {ItemID::poidsPouv, sf::String("Poids Pouvoir")},
    {ItemID::bracMacho, sf::String("Bracelet Macho")},

    // Money and XP
    {ItemID::pieceRune, sf::String(L"Pièce Rune")},
    {ItemID::encensVeine, sf::String("Encens Veine")},
            
    {ItemID::oeufChance, sf::String("Oeuf Chance")},
    {ItemID::grelotZen, sf::String("Grelot Zen")},
    {ItemID::multiExp, sf::String("Multi Exp.")},
    
    // Meteo Boosters
    {ItemID::rocheHumide, sf::String("Roche Humide")},
    {ItemID::rocheChaude, sf::String("Roche Chaude")},
    {ItemID::rocheLisse, sf::String("Roche Lisse")},
    {ItemID::rocheGlace, sf::String("Roche Glace")},
    
    // Type boosters
    {ItemID::crocDragon, sf::String("Croc Dragon")},
    {ItemID::mouchSoie, sf::String("Mouchoir Soie")},
    {ItemID::encensMer, sf::String("Encens Mer")},
    {ItemID::encensFleur, sf::String("Encens Fleur")},
    {ItemID::grainMiracl, sf::String("Grain Miracle")},
    {ItemID::encensVague, sf::String("Encens Vague")},
    {ItemID::encensRoc, sf::String("Encens Roc")},
    {ItemID::bizarEncens, sf::String("Encens Bizarre")},
    {ItemID::charbon, sf::String("Charbon")},
    {ItemID::cuillertordu, sf::String("Cuiller Tordue")},
    {ItemID::sableDoux, sf::String("Sable Doux")},
    {ItemID::pierreDure, sf::String("Pierre Dure")},
    {ItemID::lunetNoires, sf::String("Lunettes Noires")},
    {ItemID::poudreArg, sf::String(L"Poudre Argentée")},
    {ItemID::ceintNoire, sf::String("Ceinture Noire")},
    {ItemID::aimant, sf::String("Aimant")},
    {ItemID::eauMystique, sf::String("Eau Mystique")},
    {ItemID::becPointu, sf::String("Bec Pointu")},
    {ItemID::peauMetal, sf::String(L"Peau Métal")},
    {ItemID::picVenin, sf::String("Pic Venin")},
    {ItemID::runeSort, sf::String("Rune Sort")},
    {ItemID::glaceEternel, sf::String("Glace Eternelle")},
    
    // Evolu Items
    {ItemID::evoluRoc, sf::String("EvoluRoc")},
};



const std::map<ItemID, sf::String> Item::itemDescriptions = {
    // LAST ITEM
    {ItemID::LAST_ITEM, sf::String("~ MISSING DESCRIPTION ~")},
    
    // Medecine Description
    {ItemID::potion, sf::String(L"Une potion qui rend 20 PV à un pokemon.")},
    {ItemID::superPotion, sf::String(L"Une potion qui rend 50 PV à un pokemon.")},
    {ItemID::hyperPotion, sf::String(L"Une potion qui rend 200 PV à un pokemon.")},
    {ItemID::maxPotion, sf::String(L"Une potion qui rend tous ses PV à un pokemon.")},
    {ItemID::fullRestore, sf::String(L"Restaure tous les PV et soigne le statut \nd'un pokemon.")},
    {ItemID::eauFraiche, sf::String(L"Une eau fraîche qui restaure jusqu'à 30 PV.")},
    {ItemID::sodaCool, sf::String(L"Un soda qui rend 60 PV à un pokemon.")},
    {ItemID::limonade, sf::String(L"Une boisson qui rend 80 PV à un pokemon.")},
    {ItemID::laitMeumeu, sf::String(L"Un lait pur et blanc qui rend 100 PV \nà un pokemon.")},

    // Rappels
    {ItemID::rappel, sf::String(L"Soinge un pokemon KO.")},
    {ItemID::rappelMax, sf::String(L"Soigne un pokemon KO et lui rend ses PV.")},


    // Pokeball descriptions
    {ItemID::pokeball, sf::String(L"Une pokeball pour capturer des pokemons.")},
    {ItemID::superball, sf::String(L"Une ball plus efficace qu'une simple pokeball.")},
    {ItemID::hyperball, sf::String(L"Une ball beaucoup plus efficace qu'une \npokeball.")},

    // Berry descriptions
    {ItemID::berryOran, sf::String(L"Une baie qui rend 10 PV à un pokemon.")},
    {ItemID::berryCeriz, sf::String(L"Une baie qui soigne la paralysie d'un \npokemon.")},
    {ItemID::berryMaron, sf::String(L"Une baie qui réveille un pokemon.")},
    {ItemID::berryPecha, sf::String(L"Une baie qui soigne le poison d'un pokemon.")},
    {ItemID::berryFraive, sf::String(L"Une baie qui soigne les brûlures d'un \npokemon.")},
    {ItemID::berryWillia, sf::String(L"Une baie capable de dégeler un pokemon.")},
    {ItemID::berryKika, sf::String(L"Une baie qui sort un pokemon de sa \nconfusion.")},
    {ItemID::berryMepo, sf::String(L"Une baie qui rend 10 PP à un pokemon.")},
    {ItemID::berryPrine, sf::String(L"Une baie qui soigne tous les problèmes de \nstatut.")},
    {ItemID::berrySitrus, sf::String(L"Une baie qui rend un quart de la vie d'un \npokemon.")},


    // Evolution Stones Descriptions
    {ItemID::pierreEclat, sf::String(L"Une pierre étrange qui brille d’une lumière \naveuglante.")},
    {ItemID::pierreNuit, sf::String(L"Une pierre étrange sombre comme une nuit \nsans lune.")},
    {ItemID::pierreEau, sf::String(L"Une pierre étrange d'un bleu profond.")},
    {ItemID::pierreAube, sf::String(L"Une pierre étrange qui brille d'une lumière \nchaleureuse.")},
    {ItemID::pierreLune, sf::String(L"Une pierre étrange noire comme la nuit.")},
    {ItemID::pierreFeu, sf::String(L"Une pierre étrange qui dégage une chaleur \n réconfortante.")},
    {ItemID::pierreFoudre, sf::String(L"Une pierre étrange qui picote au toucher.")},
    {ItemID::pierrePlante, sf::String(L"Une pierre étrange parcourue de racines.")},
    
    
    // Training Items
    {ItemID::poignPouv, sf::String(L"Un lourd objet qui augmente l’Attaque de son \nporteur lors des montées de niveau.")},
    {ItemID::ceintPouv, sf::String(L"Un lourd objet qui augmente la Défense de son \nporteur lors des montées de niveau.")},
    {ItemID::lentPouv, sf::String(L"Un lourd objet qui augmente l’Attaque spéciale \nde son porteur lors des montées de niveau.")},
    {ItemID::bandPouv, sf::String(L"Un lourd objet qui augmente la Défense \nSpéciale de son porteur lors des montées \nde niveau.")},
    {ItemID::chainePouv, sf::String(L"Un lourd objet qui augmente la Vitesse de son \nporteur lors des montées de niveau.")},
    {ItemID::poidsPouv, sf::String(L"Un lourd objet qui augmente les PV de son \nporteur lors des montées de niveau.")},
    {ItemID::bracMacho, sf::String(L"Un objet lourd améliorant l'entraînement.")},
            
    
    // Money and XP
    {ItemID::pieceRune, sf::String(L"Objet à tenir augmentant l'argent gagné si \nle porteur se joint au combat")},
    {ItemID::encensVeine, sf::String(L"Un lourd objet à faire tenir pour augmenter \nl'argent gagné si le porteur se joint au combat")},
            
    {ItemID::oeufChance, sf::String(L"Un oeuf rempli de joie qui augmente \nl'expérience gagnée par son porteur.")},
    {ItemID::grelotZen, sf::String(L"Un grelot dont le carillon calme le porteur \net favorise l'amitié.")},
    {ItemID::multiExp, sf::String(L"Un objet à faire tenir. Le porteur reçoit une \npartie de l'expérience au combat.")},
    
    
    // Meteo Boosters
    {ItemID::rocheHumide, sf::String(L"Objet à tenir augmentant la durée de la capacité Danse Pluie utilisée par le porteur.")},
    {ItemID::rocheChaude, sf::String(L"Objet à tenir augmentant la durée de la capacité Zénith utilisée par le porteur.")},
    {ItemID::rocheLisse, sf::String(L"Objet à tenir augmentant la durée de la capacité Tempêtesable utilisée par le porteur.")},
    {ItemID::rocheGlace, sf::String(L"Objet à tenir augmentant la durée de la capacité Grêle utilisée par le porteur.")},
    
    // Type boosters
    {ItemID::crocDragon, sf::String(L"Un croc dur et pointu montant la puissance des capacités de type Dragon.")},
    {ItemID::mouchSoie, sf::String(L"Un mouchoir somptueux montant la puissance des capacités de type Normal.")},
    {ItemID::encensMer, sf::String(L"Encens au parfum curieux qui augmente la puissance des capacités de type Eau.")},
    {ItemID::encensFleur, sf::String(L"Encens au parfum exotique augmentant la puissance des capacités de type Plante.")},
    {ItemID::grainMiracl, sf::String(L"Graine remplie de vie qui monte la puissance des capacités de type Plante.")},
    {ItemID::encensVague, sf::String(L"Encens au parfum exotique augmentant la puissance des capacités de type Eau.")},
    {ItemID::encensRoc, sf::String(L"Encens au parfum exotique augmentant la puissance des capacités de type Roche.")},
    {ItemID::bizarEncens, sf::String(L"Encens au parfum exotique augmentant la puissance des capacités de type Psy.")},
    {ItemID::charbon, sf::String(L"Combustible montant la puissance des capacités de type Feu.")},
    {ItemID::cuillertordu, sf::String(L"Cuillère contenant un pouvoir télékinésique montant la puissance des capacités de type Psy.")},
    {ItemID::sableDoux, sf::String(L"Sable fin et soyeux montant la puissance des capacités de type Sol.")},
    {ItemID::pierreDure, sf::String(L"Pierre incassable qui monte la puissance des capacités de type Roche.")},
    {ItemID::lunetNoires, sf::String(L"Paire de lunettes à l’aspect louche qui monte la puissance des capacités de type Ténèbre.")},
    {ItemID::poudreArg, sf::String(L"Poudre d’argent brillante qui monte la puissance des capacités de type Insecte.")},
    {ItemID::ceintNoire, sf::String(L"Ceinture qui augmente la détermination et la puissance des capacités de type Combat.")},
    {ItemID::aimant, sf::String(L"Aimant puissant montant la puissance des capacités de type Électrik.")},
    {ItemID::eauMystique, sf::String(L"Gemme en forme de goutte d’eau montant la puissance des capacités de type Eau")},
    {ItemID::becPointu, sf::String(L"Bec long et pointu montant la puissance des capacités de type Vol.")},
    {ItemID::peauMetal, sf::String(L"Pellicule métallique spéciale qui monte la puissance des capacités de type Acier.")},
    {ItemID::picVenin, sf::String(L"Petit pic empoisonné montant la puissance des capacités de type Poison.")},
    {ItemID::runeSort, sf::String(L"Plaque sinistre et étrange montant la puissance des capacités de type Spectre.")},
    {ItemID::glaceEternel, sf::String(L"Morceau de glace qui réfléchit la chaleur et monte la puissance des capacités de type Glace.")},
    
    // Evolu Items
    {ItemID::evoluRoc, sf::String(L"Une pierre aux pouvoirs étranges qui rend les pokemons \nplus résistants s'ils peuvent encore évoluer.")},
};



const std::map<ItemID, ItemCategory> Item::itemCategories {
    // === // Medecines
    // PV
    {ItemID::potion, ItemCategory::Medecine},
    {ItemID::superPotion, ItemCategory::Medecine},
    {ItemID::hyperPotion, ItemCategory::Medecine},
    {ItemID::maxPotion, ItemCategory::Medecine},
    {ItemID::fullRestore, ItemCategory::Medecine},
    {ItemID::eauFraiche, ItemCategory::Medecine},
    {ItemID::sodaCool, ItemCategory::Medecine},
    {ItemID::limonade, ItemCategory::Medecine},
    {ItemID::laitMeumeu, ItemCategory::Medecine},
    // PP
    {ItemID::huile, ItemCategory::Medecine},
    {ItemID::huileMax, ItemCategory::Medecine},
    {ItemID::elixir, ItemCategory::Medecine},
    {ItemID::maxElixir, ItemCategory::Medecine},
    // Status
    {ItemID::antidote, ItemCategory::Medecine},
    {ItemID::antiPara, ItemCategory::Medecine},
    {ItemID::antiBrule, ItemCategory::Medecine},
    {ItemID::antiGel, ItemCategory::Medecine},
    {ItemID::reveil, ItemCategory::Medecine},
    {ItemID::totalSoin, ItemCategory::Medecine},
    // KO
    {ItemID::rappel, ItemCategory::Medecine},
    {ItemID::rappelMax, ItemCategory::Medecine},
            
            
    // === // Balls
    {ItemID::pokeball, ItemCategory::Pokeball},
    {ItemID::superball, ItemCategory::Pokeball},
    {ItemID::hyperball, ItemCategory::Pokeball},
            
            
    // === // Berries
    {ItemID::berryOran, ItemCategory::Berry},
    {ItemID::berryCeriz, ItemCategory::Berry},
    {ItemID::berryMaron, ItemCategory::Berry},
    {ItemID::berryPecha, ItemCategory::Berry},
    {ItemID::berryFraive, ItemCategory::Berry},
    {ItemID::berryWillia, ItemCategory::Berry},
    {ItemID::berryKika, ItemCategory::Berry},
    {ItemID::berryMepo, ItemCategory::Berry},
    {ItemID::berryPrine, ItemCategory::Berry},
    {ItemID::berrySitrus, ItemCategory::Berry},
            
            
    // === // CT
    {ItemID::ct1, ItemCategory::CT},
    {ItemID::ct2, ItemCategory::CT},
    {ItemID::ct3, ItemCategory::CT},
    {ItemID::ct4, ItemCategory::CT},
    {ItemID::ct5, ItemCategory::CT},
    {ItemID::ct6, ItemCategory::CT},
    {ItemID::ct7, ItemCategory::CT},
    {ItemID::ct8, ItemCategory::CT},
    {ItemID::ct9, ItemCategory::CT},
    
            
    // === // Evolution stones
    {ItemID::pierreEclat, ItemCategory::Object},
    {ItemID::pierreNuit, ItemCategory::Object},
    {ItemID::pierreEau, ItemCategory::Object},
    {ItemID::pierreAube, ItemCategory::Object},
    {ItemID::pierreLune, ItemCategory::Object},
    {ItemID::pierreFeu, ItemCategory::Object},
    {ItemID::pierreFoudre, ItemCategory::Object},
    {ItemID::pierrePlante, ItemCategory::Object},
    // Training Items
    {ItemID::poignPouv, ItemCategory::Object},
    {ItemID::ceintPouv, ItemCategory::Object},
    {ItemID::lentPouv, ItemCategory::Object},
    {ItemID::bandPouv, ItemCategory::Object},
    {ItemID::chainePouv, ItemCategory::Object},
    {ItemID::poidsPouv, ItemCategory::Object},
    {ItemID::bracMacho, ItemCategory::Object},
    
    // Money and XP
    {ItemID::pieceRune, ItemCategory::Object},
    {ItemID::encensVeine, ItemCategory::Object},
    {ItemID::oeufChance, ItemCategory::Object},
    {ItemID::grelotZen, ItemCategory::Object},
    {ItemID::multiExp, ItemCategory::Object},
            
    // Meteo Boosters
    {ItemID::rocheHumide, ItemCategory::Object},
    {ItemID::rocheChaude, ItemCategory::Object},
    {ItemID::rocheLisse, ItemCategory::Object},
    {ItemID::rocheGlace, ItemCategory::Object},
    // Type boosters
    {ItemID::crocDragon, ItemCategory::Object},
    {ItemID::mouchSoie, ItemCategory::Object},
    {ItemID::encensMer, ItemCategory::Object},
    {ItemID::encensFleur, ItemCategory::Object},
    {ItemID::grainMiracl, ItemCategory::Object},
    {ItemID::encensVague, ItemCategory::Object},
    {ItemID::encensRoc, ItemCategory::Object},
    {ItemID::bizarEncens, ItemCategory::Object},
    {ItemID::charbon, ItemCategory::Object},
    {ItemID::cuillertordu, ItemCategory::Object},
    {ItemID::sableDoux, ItemCategory::Object},
    {ItemID::pierreDure, ItemCategory::Object},
    {ItemID::lunetNoires, ItemCategory::Object},
    {ItemID::poudreArg, ItemCategory::Object},
    {ItemID::ceintNoire, ItemCategory::Object},
    {ItemID::aimant, ItemCategory::Object},
    {ItemID::eauMystique, ItemCategory::Object},
    {ItemID::becPointu, ItemCategory::Object},
    {ItemID::peauMetal, ItemCategory::Object},
    {ItemID::picVenin, ItemCategory::Object},
    {ItemID::runeSort, ItemCategory::Object},
    {ItemID::glaceEternel, ItemCategory::Object},
    
    // Evolu Items
    {ItemID::evoluRoc, ItemCategory::Object},
};



const std::map<ItemID, UseInBattle> Item::inBattleUses{
    // PV
    {ItemID::potion, UseInBattle::CONSUMED_ON_USE},
    {ItemID::superPotion, UseInBattle::CONSUMED_ON_USE},
    {ItemID::hyperPotion, UseInBattle::CONSUMED_ON_USE},
    {ItemID::maxPotion, UseInBattle::CONSUMED_ON_USE},
    {ItemID::fullRestore, UseInBattle::CONSUMED_ON_USE},
    {ItemID::eauFraiche, UseInBattle::CONSUMED_ON_USE},
    {ItemID::sodaCool, UseInBattle::CONSUMED_ON_USE},
    {ItemID::limonade, UseInBattle::CONSUMED_ON_USE},
    {ItemID::laitMeumeu, UseInBattle::CONSUMED_ON_USE},
            
    // PP
    {ItemID::huile, UseInBattle::CONSUMED_ON_ATTACK},
    {ItemID::huileMax, UseInBattle::CONSUMED_ON_ATTACK},
    {ItemID::elixir, UseInBattle::CONSUMED_ON_USE},
    {ItemID::maxElixir, UseInBattle::CONSUMED_ON_USE},
            
    // Status
    {ItemID::antidote, UseInBattle::CONSUMED_ON_USE},
    {ItemID::antiPara, UseInBattle::CONSUMED_ON_USE},
    {ItemID::antiBrule, UseInBattle::CONSUMED_ON_USE},
    {ItemID::antiGel, UseInBattle::CONSUMED_ON_USE},
    {ItemID::reveil, UseInBattle::CONSUMED_ON_USE},
    {ItemID::totalSoin, UseInBattle::CONSUMED_ON_USE},
            
    // KO
    {ItemID::rappel, UseInBattle::CONSUMED_ON_USE},
    {ItemID::rappelMax, UseInBattle::CONSUMED_ON_USE},
            
    // Balls
    {ItemID::pokeball, UseInBattle::POKEBALL},
    {ItemID::superball, UseInBattle::POKEBALL},
    {ItemID::hyperball, UseInBattle::POKEBALL},
            
    // Berries
    {ItemID::berryOran, UseInBattle::HOLD_CONSUMABLE},
    {ItemID::berryCeriz, UseInBattle::HOLD_CONSUMABLE},
    {ItemID::berryMaron, UseInBattle::HOLD_CONSUMABLE},
    {ItemID::berryPecha, UseInBattle::HOLD_CONSUMABLE},
    {ItemID::berryFraive, UseInBattle::HOLD_CONSUMABLE},
    {ItemID::berryWillia, UseInBattle::HOLD_CONSUMABLE},
    {ItemID::berryKika, UseInBattle::HOLD_CONSUMABLE},
    {ItemID::berryMepo, UseInBattle::CONSUMED_ON_ATTACK},
    {ItemID::berryPrine, UseInBattle::HOLD_CONSUMABLE},
    {ItemID::berrySitrus, UseInBattle::HOLD_CONSUMABLE},
            
    // CT
    {ItemID::ct1, UseInBattle::CANNOT_USE},
    {ItemID::ct2, UseInBattle::CANNOT_USE},
    {ItemID::ct3, UseInBattle::CANNOT_USE},
    {ItemID::ct4, UseInBattle::CANNOT_USE},
    {ItemID::ct5, UseInBattle::CANNOT_USE},
    {ItemID::ct6, UseInBattle::CANNOT_USE},
    {ItemID::ct7, UseInBattle::CANNOT_USE},
    {ItemID::ct8, UseInBattle::CANNOT_USE},
    {ItemID::ct9, UseInBattle::CANNOT_USE},            
            
    // Evolution stones
    {ItemID::pierreEclat, UseInBattle::CANNOT_USE},
    {ItemID::pierreNuit, UseInBattle::CANNOT_USE},
    {ItemID::pierreEau, UseInBattle::CANNOT_USE},
    {ItemID::pierreAube, UseInBattle::CANNOT_USE},
    {ItemID::pierreLune, UseInBattle::CANNOT_USE},
    {ItemID::pierreFeu, UseInBattle::CANNOT_USE},
    {ItemID::pierreFoudre, UseInBattle::CANNOT_USE},
    {ItemID::pierrePlante, UseInBattle::CANNOT_USE},
            
    // Training Items
    {ItemID::poignPouv, UseInBattle::HOLD_ITEM},
    {ItemID::ceintPouv, UseInBattle::HOLD_ITEM},
    {ItemID::lentPouv, UseInBattle::HOLD_ITEM},
    {ItemID::bandPouv, UseInBattle::HOLD_ITEM},
    {ItemID::chainePouv, UseInBattle::HOLD_ITEM},
    {ItemID::poidsPouv, UseInBattle::HOLD_ITEM},
    {ItemID::bracMacho, UseInBattle::HOLD_ITEM},
    
    // Money and XP
    {ItemID::pieceRune, UseInBattle::HOLD_ITEM},
    {ItemID::encensVeine, UseInBattle::HOLD_ITEM},
    {ItemID::oeufChance, UseInBattle::HOLD_ITEM},
    {ItemID::grelotZen, UseInBattle::HOLD_ITEM},
    {ItemID::multiExp, UseInBattle::HOLD_ITEM},
            
    // Meteo Boosters
    {ItemID::rocheHumide, UseInBattle::HOLD_ITEM},
    {ItemID::rocheChaude, UseInBattle::HOLD_ITEM},
    {ItemID::rocheLisse, UseInBattle::HOLD_ITEM},
    {ItemID::rocheGlace, UseInBattle::HOLD_ITEM},
            
    // Type boosters
    {ItemID::crocDragon, UseInBattle::HOLD_ITEM},
    {ItemID::mouchSoie, UseInBattle::HOLD_ITEM},
    {ItemID::encensMer, UseInBattle::HOLD_ITEM},
    {ItemID::encensFleur, UseInBattle::HOLD_ITEM},
    {ItemID::grainMiracl, UseInBattle::HOLD_ITEM},
    {ItemID::encensVague, UseInBattle::HOLD_ITEM},
    {ItemID::encensRoc, UseInBattle::HOLD_ITEM},
    {ItemID::bizarEncens, UseInBattle::HOLD_ITEM},
    {ItemID::charbon, UseInBattle::HOLD_ITEM},
    {ItemID::cuillertordu, UseInBattle::HOLD_ITEM},
    {ItemID::sableDoux, UseInBattle::HOLD_ITEM},
    {ItemID::pierreDure, UseInBattle::HOLD_ITEM},
    {ItemID::lunetNoires, UseInBattle::HOLD_ITEM},
    {ItemID::poudreArg, UseInBattle::HOLD_ITEM},
    {ItemID::ceintNoire, UseInBattle::HOLD_ITEM},
    {ItemID::aimant, UseInBattle::HOLD_ITEM},
    {ItemID::eauMystique, UseInBattle::HOLD_ITEM},
    {ItemID::becPointu, UseInBattle::HOLD_ITEM},
    {ItemID::peauMetal, UseInBattle::HOLD_ITEM},
    {ItemID::picVenin, UseInBattle::HOLD_ITEM},
    {ItemID::runeSort, UseInBattle::HOLD_ITEM},
    {ItemID::glaceEternel, UseInBattle::HOLD_ITEM},
    
    // Evolu Items
    {ItemID::evoluRoc, UseInBattle::HOLD_ITEM},
};



const std::map<ItemID, UseOutBattle> Item::outBattleUses{
    // PV
    {ItemID::potion, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::superPotion, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::hyperPotion, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::maxPotion, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::fullRestore, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::eauFraiche, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::sodaCool, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::limonade, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::laitMeumeu, UseOutBattle::CONSUMED_ON_USE},
            
    // PP
    {ItemID::huile, UseOutBattle::CONSUMED_ON_ATTACK},
    {ItemID::huileMax, UseOutBattle::CONSUMED_ON_ATTACK},
    {ItemID::elixir, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::maxElixir, UseOutBattle::CONSUMED_ON_USE},
            
    // Status
    {ItemID::antidote, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::antiPara, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::antiBrule, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::antiGel, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::reveil, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::totalSoin, UseOutBattle::CONSUMED_ON_USE},
            
    // KO
    {ItemID::rappel, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::rappelMax, UseOutBattle::CONSUMED_ON_USE},
            
    // Balls
    {ItemID::pokeball, UseOutBattle::CANNOT_USE},
    {ItemID::superball, UseOutBattle::CANNOT_USE},
    {ItemID::hyperball, UseOutBattle::CANNOT_USE},
            
    // Berries
    {ItemID::berryOran, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::berryCeriz, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::berryMaron, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::berryPecha, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::berryFraive, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::berryWillia, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::berryKika, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::berryMepo, UseOutBattle::CONSUMED_ON_ATTACK},
    {ItemID::berryPrine, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::berrySitrus, UseOutBattle::CONSUMED_ON_USE},
            
    // CT
    {ItemID::ct1, UseOutBattle::TEACH_MOVE},
    {ItemID::ct2, UseOutBattle::TEACH_MOVE},
    {ItemID::ct3, UseOutBattle::TEACH_MOVE},
    {ItemID::ct4, UseOutBattle::TEACH_MOVE},
    {ItemID::ct5, UseOutBattle::TEACH_MOVE},
    {ItemID::ct6, UseOutBattle::TEACH_MOVE},
    {ItemID::ct7, UseOutBattle::TEACH_MOVE},
    {ItemID::ct8, UseOutBattle::TEACH_MOVE},
    {ItemID::ct9, UseOutBattle::TEACH_MOVE},            
            
    // Evolution stones
    {ItemID::pierreEclat, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::pierreNuit, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::pierreEau, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::pierreAube, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::pierreLune, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::pierreFeu, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::pierreFoudre, UseOutBattle::CONSUMED_ON_USE},
    {ItemID::pierrePlante, UseOutBattle::CONSUMED_ON_USE},
            
    // Training Items
    {ItemID::poignPouv, UseOutBattle::CANNOT_USE},
    {ItemID::ceintPouv, UseOutBattle::CANNOT_USE},
    {ItemID::lentPouv, UseOutBattle::CANNOT_USE},
    {ItemID::bandPouv, UseOutBattle::CANNOT_USE},
    {ItemID::chainePouv, UseOutBattle::CANNOT_USE},
    {ItemID::poidsPouv, UseOutBattle::CANNOT_USE},
    {ItemID::bracMacho, UseOutBattle::CANNOT_USE},
    
    // Money and XP
    {ItemID::pieceRune, UseOutBattle::CANNOT_USE},
    {ItemID::encensVeine, UseOutBattle::CANNOT_USE},
    {ItemID::oeufChance, UseOutBattle::CANNOT_USE},
    {ItemID::grelotZen, UseOutBattle::CANNOT_USE},
    {ItemID::multiExp, UseOutBattle::CANNOT_USE},
            
    // Meteo Boosters
    {ItemID::rocheHumide, UseOutBattle::CANNOT_USE},
    {ItemID::rocheChaude, UseOutBattle::CANNOT_USE},
    {ItemID::rocheLisse, UseOutBattle::CANNOT_USE},
    {ItemID::rocheGlace, UseOutBattle::CANNOT_USE},
            
    // Type boosters
    {ItemID::crocDragon, UseOutBattle::CANNOT_USE},
    {ItemID::mouchSoie, UseOutBattle::CANNOT_USE},
    {ItemID::encensMer, UseOutBattle::CANNOT_USE},
    {ItemID::encensFleur, UseOutBattle::CANNOT_USE},
    {ItemID::grainMiracl, UseOutBattle::CANNOT_USE},
    {ItemID::encensVague, UseOutBattle::CANNOT_USE},
    {ItemID::encensRoc, UseOutBattle::CANNOT_USE},
    {ItemID::bizarEncens, UseOutBattle::CANNOT_USE},
    {ItemID::charbon, UseOutBattle::CANNOT_USE},
    {ItemID::cuillertordu, UseOutBattle::CANNOT_USE},
    {ItemID::sableDoux, UseOutBattle::CANNOT_USE},
    {ItemID::pierreDure, UseOutBattle::CANNOT_USE},
    {ItemID::lunetNoires, UseOutBattle::CANNOT_USE},
    {ItemID::poudreArg, UseOutBattle::CANNOT_USE},
    {ItemID::ceintNoire, UseOutBattle::CANNOT_USE},
    {ItemID::aimant, UseOutBattle::CANNOT_USE},
    {ItemID::eauMystique, UseOutBattle::CANNOT_USE},
    {ItemID::becPointu, UseOutBattle::CANNOT_USE},
    {ItemID::peauMetal, UseOutBattle::CANNOT_USE},
    {ItemID::picVenin, UseOutBattle::CANNOT_USE},
    {ItemID::runeSort, UseOutBattle::CANNOT_USE},
    {ItemID::glaceEternel, UseOutBattle::CANNOT_USE},
    
    // Evolu Items
    {ItemID::evoluRoc, UseOutBattle::CANNOT_USE},
};



const std::map<ItemID, int> Item::itemPrices {
    // Potions
    {ItemID::potion, 300},
    {ItemID::superPotion, 700},
    {ItemID::hyperPotion, 1200},
    {ItemID::maxPotion, 2500},
    {ItemID::fullRestore, 3000},
            
    // Revives
    {ItemID::rappel, 2000},
    {ItemID::rappelMax, 4000},
    
    // Medicine
    {ItemID::antiBrule, 300}, 
    {ItemID::antiPara, 300}, 
    {ItemID::antiGel, 300}, 
    {ItemID::antidote, 300}, 
    {ItemID::reveil, 300},
    

    // Pokeballs
    {ItemID::pokeball, 200},
    {ItemID::superball, 600},
    {ItemID::hyperball, 1200},
            
    
    // Evolution stones
    {ItemID::pierreEclat, 15000},
    {ItemID::pierreNuit, 15000},
    {ItemID::pierreEau, 15000},
    {ItemID::pierreAube, 15000},
    {ItemID::pierreLune, 15000},
    {ItemID::pierreFeu, 15000},
    {ItemID::pierreFoudre, 15000},
    {ItemID::pierrePlante, 15000},
            
            
    // Training Items
    {ItemID::poignPouv, 15000},
    {ItemID::ceintPouv, 15000},
    {ItemID::lentPouv, 15000},
    {ItemID::bandPouv, 15000},
    {ItemID::chainePouv, 15000},
    {ItemID::poidsPouv, 15000},
    {ItemID::bracMacho, 15000},
            
    {ItemID::pieceRune, 40000},
    {ItemID::encensVeine, 40000},
            
    {ItemID::oeufChance, 22000},
    {ItemID::grelotZen, 8000},
    {ItemID::multiExp, 30000},
    
    // Evolu Items
    {ItemID::evoluRoc, 45000},
};



const std::vector<ItemID> Item::firstRowItems{
    ItemID::potion,
    ItemID::pokeball,
    ItemID::berryOran,
    ItemID::ct1,
    ItemID::pierreEclat,
    ItemID::poignPouv,
    ItemID::rocheHumide
};
    
    
    
const std::map<ItemID, float> Item::speedModifier{
    {ItemID::poignPouv, 0.5},
    {ItemID::ceintPouv, 0.5},
    {ItemID::lentPouv, 0.5},
    {ItemID::bandPouv, 0.5},
    {ItemID::chainePouv, 0.5},
    {ItemID::poidsPouv, 0.5},
    {ItemID::bracMacho, 0.5},
    {ItemID::encensVeine, 0.5},
};



const std::map<ItemID, AttackID> Item::teachedAttacks{
    {ItemID::ct1, AttackID::Avalanche},
    {ItemID::ct2, AttackID::Hypnose},
    {ItemID::ct3, AttackID::UltraLaser},
    {ItemID::ct4, AttackID::BoueBombe},
    {ItemID::ct5, AttackID::EclatGlace},
    {ItemID::ct6, AttackID::Flammeche},
    {ItemID::ct7, AttackID::PoingKarate},
    {ItemID::ct8, AttackID::LanceSoleil},
    {ItemID::ct9, AttackID::SouffleGlace},
};