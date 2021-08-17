#ifndef SPRITES_H
#define SPRITES_H

// INCLUDE RELEVANT HEADERS //
#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

/** Sprites Class
* @brief Contains all of the non-Jerome and non-Enemy figure sprites used throughout the game
* @details All of the functions return a pointer to their respective sprite
* @details declared in Sprites.cpp
* @author Kamal Gamir - Shahin, University of Leeds
* @version 1.0
* @date May 2019
* @code

Sprites sprites;
int main(){
    int *play;
    // Declare pointer
    play = sprites.get_play(); //CHANGE//
    // Create variable from pointer
    lcd.drawSprite(70,0,8,24,(int *)play); // Left-facing
    // (x-coord, y-coord,sprite width,sprite height,(int *)name_of_sprite)
        
    // NOTE: //
    // All of the sprite accessor methods work in the same way and so are not all individually documented
    // In order to draw a different sprite than the one shown in the example
    // use a different accessor method and change the sprite height and width
    // values used in the line marked with '//CHANGE//'
}
* @endcode
*/

class Sprites
{
public:
    /** Constructor */
    Sprites();
    /** Destructor */
    ~Sprites();
    
    // WELCOME PAGE SPRITES
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to play button sprite
    * @returns Pointer to sprite */
    int *get_play();
    
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to title sprite
    * @returns Pointer to sprite */
    int *get_title();
    
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to settings button sprite
    * @returns Pointer to sprite */
    int *get_settings();
    
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to arrow sprite
    * @returns Pointer to sprite */
    int *get_arrow();
    
    // IN GAME ICONS
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to 'J' icon sprite
    * @returns Pointer to sprite */
    int *get_j();
    
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to 'CPU' icon sprite
    * @returns Pointer to sprite */
    int *get_cpu(); 
    
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to Jerome KO sprite
    * @detials Used on KO splash screen when player wins a round
    * @returns Pointer to sprite */
    int *get_jerome_ko();
    
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer CPU KO sprite
    * @detials Used on KO splash screen when cpu wins a round
    * @returns Pointer to sprite */
    int *get_cpu_ko();
    
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to KO sprite
    * @detials Used on KO splash screen when either player or cpu wins a round
    * @returns Pointer to sprite */
    int *get_ko_icon();
    
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to life icon sprite
    * @detials Used during game to display how many lives the player has left
    * @returns Pointer to sprite */
    int *get_life_icon();
    
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to background sprite
    * @detials Used during game as background
    * @details The background sprite is purposefully larger than necessary (100x50)
    * @details when the size of the screen is (84x48).
    * @details This is to allow the parallax effects to be added later by moving
    * @details the position of the background depending on where Jerome is.
    * @details This is done in the JeromeEngine class function display_background(...)
    * @returns Pointer to sprite */
    int *get_background();
    
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to brightness icon sprite
    * @detials Used in settings menu
    * @returns Pointer to sprite */
    int *get_brightness_icon();
    
        /** Sprite ACCESSOR
    * @brief Creates and returns pointer to contrast icon sprite
    * @detials Used in settings menu
    * @returns Pointer to sprite */
    int *get_contrast_icon();
private:
};
#endif