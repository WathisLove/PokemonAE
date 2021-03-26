#include <cassert>

#include "CharacterBody.hpp"
#include "../../Constants.hpp"
#include "../../zones/Zone.hpp"

CharacterBody::CharacterBody(sf::Sprite& sprite, float speed, Zone* zone) :
m_sprite(sprite),
m_moveTime(1./speed),
m_direction(Direction::South),
m_zone(zone),
m_timePassed(0),
m_isFrozen(false),
m_isJumping(false),
m_jumpSpeed(0.5),
m_isRunning(false),
m_framesWithoutMoving(0){
    m_sprite.setTextureRect(sf::IntRect(16, 44, 16, 22));
    lookDown();
}



void CharacterBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}



void CharacterBody::update(float dt) {
    // Update the Time passed
    m_timePassed += dt;
    
    // Set the Sprite position
    if(m_isJumping)
        setJumpSpritePosition();
    else
        setSpritePosition();
    
    // If the Character us not moving
    if(!isMoving())
        m_framesWithoutMoving++;
    else
        m_framesWithoutMoving = 0;
    
    
    // Set the Sprite texture Rect
    setTextureRect();
}



void CharacterBody::freeze(bool frozen){
    m_isFrozen = frozen;
    
    // Set the Texture Rect
    if(frozen == true)
        update(0);
}



void CharacterBody::manageMove(MovementType move){
    // Check first if we are already moving
    if(isMoving() || m_isFrozen)
        return;

    // check the move and react accordingly
    switch(move){
        // Looking in a direction
        case MovementType::LookLeft: 
            lookLeft(); break;
        case MovementType::LookRight: 
            lookRight(); break;
        case MovementType::LookUp: 
            lookUp(); break;
        case MovementType::LookDown: 
            lookDown(); break;
            
        case MovementType::GoLeft: 
            goLeft(); break;
        case MovementType::GoRight: 
            goRight(); break;
        case MovementType::GoUp: 
            goUp(); break;
        case MovementType::GoDown: 
            goDown(); break;
    }
}



void CharacterBody::toggleRun() {
    // Change speed
    if(m_isRunning)
        m_moveTime *= 2.;
    else
        m_moveTime /= 2.;
    
    // Toggle running
    m_isRunning = !m_isRunning;
}



void CharacterBody::setPosition(sf::Vector2i pos) {
    // Update the Position and Next position
    m_pos = pos;
    m_nextPos = pos;
    
    // Set the Sprite
    setSpritePosition();
}



sf::Vector2i CharacterBody::getNextPosition() const{
    // Be sure the Character is moving
    assert(isMoving());
    
    return m_nextPos;
}



sf::Vector2i CharacterBody::getPosition() const {
    return m_pos;
}



bool CharacterBody::isMoving() const {
    return m_pos != m_nextPos;
}



bool CharacterBody::wasMoving() const {
    return m_framesWithoutMoving == 1;
}



bool CharacterBody::isJumping() const {
    return m_isJumping;
}



void CharacterBody::setDirection(Direction dir){
    // Change the Body to look in the Direction dir
    switch(dir){
        case Direction::North:
            lookUp();
            break;
        case Direction::East:
            lookRight();
            break;
        case Direction::South:
            lookDown();
            break;
        case Direction::West:
            lookLeft();
            break;
    }
}



Direction CharacterBody::getDirection() const {
    return m_direction;
}



bool CharacterBody::isFrozen() const {
    return m_isFrozen;
}



sf::Vector2i CharacterBody::getFrontCase(int distance) const {
    return getCaseFacing(m_direction, m_pos, distance);
}



bool CharacterBody::hasReachedNextPosition() {
    // Check if the jump is complete
    if(m_isJumping){
        if(m_isRunning)
            return m_jumpSpeed * m_timePassed * 0.5 >= m_moveTime;
        else
            return m_jumpSpeed * m_timePassed >= m_moveTime;
    }
    else
        // Compare the time passed and time between moves
        return m_timePassed >= m_moveTime;
}



void CharacterBody::reachNextPosition() {
    // Reset the Time passed
    m_timePassed = 0;
    
    // Stop jumping
    m_isJumping = false;
    
    // Set the Character to the reached position;
    setPosition(m_nextPos);
    
    // Update the Teture rect
    setTextureRect();
}



void CharacterBody::endMovement() {
    m_nextPos = m_pos;
}



void CharacterBody::resetTime() {
    m_timePassed = 0;
}



void CharacterBody::setTextureRect() {
    // The Texture rect
    sf::IntRect rect = m_sprite.getTextureRect();
    
    // If the Character is moving, change the texture rect
    if(isMoving()){
        // Switch between left and right feets
        if((m_pos.x+m_pos.y)%2 == 0)
            rect.left = 0;
        else
            rect.left = 2*rect.width;
    }
    // Else set it to 0
    else
        rect.left = rect.width;
    
    // Set the Running Texture
    if(m_isRunning)
        rect.left += rect.width*4;
    
    // Reset the TextureRect if we didn't move for more than a frame
    if(m_framesWithoutMoving > 1)
        rect.left = rect.width;
    
    // Set the Texture Rect
    m_sprite.setTextureRect(rect);
}



void CharacterBody::setSpritePosition() {
    // Get the Current Case position
    sf::Vector2f casePos = m_zone->getCaseCenter(m_pos);
    
    // The Size of a Tile
    sf::Vector2f tileSize = ZoneLayer::tileSize * GAME_ZOOM;
    
    // If the Character is moving, place the sprite between the cases
    if(isMoving()){
        // Get the difference between the pos and next pos
        sf::Vector2i diff = m_nextPos - m_pos;
        
        // Stop moving if the target was reached
        if(hasReachedNextPosition()){
            reachNextPosition();
            setSpritePosition();
        }
        // Set the sprite position
        else{
            // Offset ratio
            float offset = m_timePassed / m_moveTime;
        
            sf::Vector2f pos = casePos;
            pos.x += diff.x * offset * tileSize.x;
            pos.y += diff.y * offset * tileSize.y;
            
            m_sprite.setPosition(pos);
        }
    }
    // Else Fix the sprite at the current case
    else
        m_sprite.setPosition(casePos);
}



void CharacterBody::setJumpSpritePosition(){
    // Get the Current Case position
    sf::Vector2f casePos = m_zone->getCaseCenter(m_pos);
    
    // The Size of a Tile
    sf::Vector2f tileSize = ZoneLayer::tileSize * GAME_ZOOM;
    
    // If the Character is moving, place the sprite between the cases
    if(isMoving()){
        // Stop moving if the target was reached
        if(hasReachedNextPosition()){
            hasReachedNextPosition();
            setSpritePosition();
        }
        // Set the sprite in jump position
        else{
            // Offset ratio
            float offset = m_jumpSpeed * m_timePassed / m_moveTime;        
            
            // Change the offset if running to jump at the same speed than walking
            if(m_isRunning)
                offset *= 0.5;

            // The height of the jump
            int height(25);

            // Get the difference between the pos and next pos
            sf::Vector2i diff = m_nextPos - m_pos;

            // The vector offset during the jump
            sf::Vector2f offsetVec;

            offsetVec.x = offset * diff.x * tileSize.x;
            offsetVec.y = offset * diff.y * tileSize.y - height*std::sin(3.14*offset);


            m_sprite.setPosition(casePos + offsetVec);
        }
    }
    // Else Fix the sprite at the current case
    else{
        m_sprite.setPosition(casePos);
    }
}



void CharacterBody::jump(){
    // Reset the Movement Timer
    resetTime();
        
    // Set the body to jump
    m_isJumping = true;

    // Get the target pos
    switch(m_direction){
        case Direction::North: 
            m_nextPos = m_pos + sf::Vector2i(0, -2); 
            break;
        case Direction::East: 
            m_nextPos = m_pos + sf::Vector2i(2, 0); 
            break;
        case Direction::South: 
            m_nextPos = m_pos + sf::Vector2i(0, 2); 
            break;
        case Direction::West: 
            m_nextPos = m_pos + sf::Vector2i(-2, 0); 
            break;
    }
}



void CharacterBody::lookUp() {
    // Set the top of the new TextureRect
    sf::IntRect rect = m_sprite.getTextureRect();
    rect.top = 0;
    
    // Set the Sprite Texture Rect
    m_sprite.setTextureRect(rect);
    
    // Set the Direction
    m_direction = Direction::North;
}



void CharacterBody::lookDown() {
    // Set the top of the new TextureRect
    sf::IntRect rect = m_sprite.getTextureRect();
    rect.top = 2*rect.height;
    
    // Set the Sprite Texture Rect
    m_sprite.setTextureRect(rect);
    
    // Set the Direction
    m_direction = Direction::South;
}



void CharacterBody::lookRight() {
    // Set the top of the new TextureRect
    sf::IntRect rect = m_sprite.getTextureRect();
    rect.top = rect.height;
    
    // Set the Sprite Texture Rect
    m_sprite.setTextureRect(rect);
    
    // Set the Direction
    m_direction = Direction::East;
}



void CharacterBody::lookLeft() {
    // Set the top of the new TextureRect
    sf::IntRect rect = m_sprite.getTextureRect();
    rect.top = 3*rect.height;
    
    // Set the Sprite Texture Rect
    m_sprite.setTextureRect(rect);
    
    // Set the Direction
    m_direction = Direction::West;
}



void CharacterBody::goUp() {
    // Be sure to look up
    lookUp();

    // Jump over a case if possible
    if(m_zone->canJumpOverCase(getFrontCase(), m_direction)){
        jump();
    }
    else if(m_zone->canWalkOnCase(getFrontCase())){
        // Update the Next position
        m_nextPos = m_pos + sf::Vector2i(0, -1);

        resetTime();
    }
}



void CharacterBody::goDown() {
    // Be sure to look down
    lookDown();

    // Jump over a case if possible
    if(m_zone->canJumpOverCase(getFrontCase(), m_direction)){
        jump();
    }
    else if(m_zone->canWalkOnCase(getFrontCase())){
        // Update the Next position
        m_nextPos = m_pos + sf::Vector2i(0, 1);

        resetTime();
    }
}



void CharacterBody::goRight() {
    // Be sure to look right
    lookRight();

    // Jump over a case if possible
    if(m_zone->canJumpOverCase(getFrontCase(), m_direction)){
        jump();
    }
    else if(m_zone->canWalkOnCase(getFrontCase())){
        // Update the Next position
        m_nextPos = m_pos + sf::Vector2i(1, 0);

        resetTime();
    }
}



void CharacterBody::goLeft() {
    // Be sure to look left
    lookLeft();

    // Jump over a case if possible
    if(m_zone->canJumpOverCase(getFrontCase(), m_direction)){
        jump();
    }
    else if(m_zone->canWalkOnCase(getFrontCase())){
        // Update the Next position
        m_nextPos = m_pos + sf::Vector2i(-1, 0);

        resetTime();
    }
}



bool CharacterBody::mustJump() const {
    return m_zone->canJumpOverCase(getFrontCase(), m_direction);
}
