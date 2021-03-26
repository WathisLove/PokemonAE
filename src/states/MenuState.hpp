/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MenuState.hpp
 * Author: Redbuzard
 *
 * Created on 3 avril 2019, 12:21
 */

#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "State.hpp"


class MenuState : public State{
public:
    
    MenuState(StateStack* stack, Character* c);
    
    virtual ~MenuState() ;


    
    //==================// Public Methods //===================//
    
    
    /**
     * Draw the state
     */
    virtual void draw();
    
    /**
     * Update the State
     * @param dt time elapsed since last frame
     * @return false if the next State in the stack must not be updated
     */
    virtual bool update(float dt);
    
    
    /**
     * @return true if the State must be popped
     */
    virtual bool isCompleted() const;
    
    /**
     * Act on the stack when the goal of the state is achieved
     */
    virtual void actionOnCompletion();
    
    /**
     * Manage an incoming Event
     * @return false if the next State must not handle Events
     */
    virtual bool handleEvent(sf::Event& event);
    
    

private:
    
    //==================// Private Methods //===================//
    
    /**
     * Draw the circles for the background and for the icons
     */
    void drawCircles(sf::RenderWindow& window);
    
    
    /**
     * Draw one of the small circles behind the icons
     * @param window the target window
     * @param center the coordinates of the center of the circle
     */
    void drawIconCircle(sf::RenderWindow& window, sf::Vector2f center);
    
    
    /**
     * Update the Content of the Text Object
     */
    void updateText();
    
    
    /**
     * Set the parameters for the 2 background Circles
     */
    void setBGCircles();
    
    
    /**
     * Set the Text Object position according to its content
     */
    void setTextPosition();
    
    
    
    //==================// Attributes //===================//
    
    // A pointer to the character
    Character* m_character;
    
    // Slected Icon
    int m_selectedIcon;
    
    
    // The distance to the icons
    const float m_iconDistance;
    
    // The AngularPos in degrees
    float m_currentAngularPos;
    
    // Time in seconds of a rotation of an item
    const float m_rotationTime;
    
    
    // Time left before the end of the rotation
    float m_timeLeft;
    
    
    
    //==================// Graphical Attributes //===================//
    
    // Vector of sprites for the icons
    std::vector<sf::Sprite*> m_icons;
    
    // Arrow that points to the selected menu
    sf::Sprite m_arrow;
    
    // Background circles
    sf::CircleShape m_bgLarge;
    sf::CircleShape m_bgSmall;
    
    // Text to display the menu selected
    sf::Text m_text;
};

#endif /* MENUSTATE_HPP */

