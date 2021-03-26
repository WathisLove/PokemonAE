#include "ItemPredicate.hpp"
#include "../inventory/Item.hpp"


// A predicate for the healing items
const std::function<bool(ItemID)> ItemPredicate::healing =
[](ItemID id) {
    // Check if the item heals
    auto it = Item::healHPs.find(id);
    return it != Item::healHPs.end();
};


// A predicate for the curing Status items
const std::function<bool(ItemID, MainStatusName)> ItemPredicate::curingStatus =
[](ItemID id, MainStatusName status) {
    // Check if the item heals the status
    auto itStatus = Item::statusHealed.find(id);
    if(itStatus != Item::statusHealed.end())
        return itStatus->second == status;
    
    // Check if heal any status
    auto itStatusAny = Item::allStatusHealed.find(id);    
    return itStatusAny != Item::allStatusHealed.end();
};



ItemPredicate::ItemPredicate(ItemSearched search) :
m_target(search){

}



ItemPredicate::ItemPredicate(ItemSearched search, MainStatusName status) :
m_target(search),
m_status(status){

}



bool ItemPredicate::operator()(ItemID id) {
    switch(m_target){
        case ItemSearched::Healing:
            return healing(id);
        case ItemSearched::CuringStatus:
            return curingStatus(id, m_status);
        default:
            throw std::string("Not known function for item predicate ") + toString((int)m_target);
    }
}
