#ifndef JEROME_H
#define JEROME_H

// INCLUDE RELEVANT HEADERS //
#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"
#include "Jerome.h"
#include <iostream>
#include <ctime>

/** Collision struct
 * @brief List of collisions that the Jerome can have with the enemy
 * @details The corresponding boolean value is set to true if collision detected
 * @details e.g. if the enemy is touching the right side of Jerome, bool right is set to true.
 * @details configured in Jerome::collision_detect(...)
 */
struct Collision {
    bool left; /**< boolean for left-side collison */
    bool right; /**< boolean for right-side collison */
    bool above; /**< boolean for collison from above */
};

/** Frame struct */
/** @details Struct holds variables used to determine how long to show particular sprites on screen.*/
/** @details Used in Enemy::hold_sprite_frame function.*/

struct Frames {
    int punch; /**< integer to store number of punch frames */
    int kick; /**< integer to store number of kick frames */
    int number; /**< integer to store number of frames to hold for */
};

/** Jerome's orientation
 * @brief List of directions Jerome can face
 */
enum Orientation {
    LEFT, /**< Oriented leftwards  */
    RIGHT /**< Oriented rightwards  */
};

/** Jerome's action
 * @brief List of actions Jerome can execute
 */
enum Action {
    PUNCH, /**< Punching  */
    KICK, /**< Kicking  */
    NOTHING /**< Doing nothing  */
};

/** Jerome Class
* @brief Contains functions, variables and sprites relating to the Jerome (user) character.
* @brief Public functions allow the updating and drawing of the Jerome sprite to be controlled from the JeromeEngine class.
* @brief Private functions control how the Jerome sprite responds to inputs.
* @author Kamal Gamir - Shahin, University of Leeds
* @version 1.0
* @date May 2019

* @code
#include "Jerome.h"
#include "Gamepad.h"
#include "mbed.h"
#include "N5110.h"
#include "Enemy.h"

Jerome player;
Direction _direction;
int main() {
    read_input(pad);
    init_players();
    _distance = set_distance(_jerome_pos,_enemy_pos, _distance);
    _START = false;
    update(pad,lcd);
    draw(lcd);

    // EXAMPLE OF HOW TO GET JEROME'S POSITION
    _jerome_pos = player.get_jerome_pos();
}

void read_input(Gamepad &pad)
{
    // GAMEPAD CLASS METHODS
    _d = pad.get_direction();
    _mag = pad.get_mag();

    _A = pad.check_event(Gamepad::A_PRESSED);
    _B = pad.check_event(Gamepad::B_PRESSED);
    _X = pad.check_event(Gamepad::X_PRESSED);
    _Y = pad.check_event(Gamepad::Y_PRESSED);
    _BACK = pad.check_event(Gamepad::BACK_PRESSED);
    _START = pad.check_event(Gamepad::START_PRESSED);
}

// EXAMPLE OF HOW TO INITIALISE JEROME
void init_players()
{
    player.init(0,0);
}

Vector2D set_distance(Vector2D jerome_pos, Vector2D enemy_pos, Vector2D &distance)
{
    _jerome_pos = jerome_pos;
    _enemy_pos = enemy_pos;
    _distance = distance;

    Vector2D _distance = {_distance.x,_distance.y};
    _distance.x = (_enemy_pos.x) - (_jerome_pos.x);
    _distance.y = (_enemy_pos.y) - (_jerome_pos.y);
    //cout << "INTERNAL Distance x = " <<_distance.x << std::endl;
    //cout << "INTERNAL Distance y = " <<_distance.y << std::endl << std::endl;
    return _distance;
}


// EXAMPLE OF HOW TO UPDATE JEROME
void update(Gamepad &pad, N5110 &lcd)
{
    if (_START == true) {
        _paused = !_paused;
        wait(0.5);
    }
    if (_paused) {
        display_pause(lcd);
        //wait(0.2);

    } else {
        // POSITIONING //
        _jerome_pos = player.get_jerome_pos();
        _distance = set_distance(_jerome_pos,_enemy_pos, _distance);

        // UPDATING GAME //
        player.update(_d,_mag,_A, _B, _X, _o, _distance);
    }
}

// EXAMPLE OF HOW TO DRAW JEROME ON SCREEN
void draw(N5110 &lcd)
{
    _B == true;
    _X == false;
    _o = RIGHT;
    player.draw(_d, lcd, _B, _X, _o);
}

// EXAMPLE OF HOW TO USE SPRITE ACCESSORS
void draw_random_jerome_sprite(N5110 &lcd){
    
    int *jerome; //
    // Declare pointer
    jerome = cpu.get_jerome_right(); //CHANGE//
    // Create variable from pointer
    lcd.drawSprite(70,0,13,11,(int *)jerome);
    // (x-coord, y-coord,sprite width,sprite height,(int *)name_of_sprite) `
    
    // NOTE: //
    // All of the sprite accessor methods work in the same way and so are not all individually documented
    // In order to draw a different sprite than the one shown in the example
    // use a different accessor method in the line marked with '//CHANGE//'
}
* @endcode
*/

class Jerome
{
public:
    /** Constructor */
    Jerome();
    /** Destructor */
    ~Jerome();

    // SPRITES //
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to Jerome right-facing Sprite
    * @returns Pointer to sprite */
    int *get_jerome_right();
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to Jerome left-facing Sprite
    * @returns Pointer to sprite */
    int *get_jerome_left();
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to Jerome right-facing punch Sprite
    * @returns Pointer to sprite */
    int *get_jerome_right_punch();
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to Jerome right-facing kick Sprite
    * @returns Pointer to sprite */
    int *get_jerome_right_kick();
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to Jerome left-facing punch Sprite
    * @returns Pointer to sprite */
    int *get_jerome_left_punch();
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to Jerome left-facing kick Sprite
    * @returns Pointer to sprite */
    int *get_jerome_left_kick();
    ////

    /**
    * @brief Position MUTATOR
    * @details Takes in coordinates x and y and sets Jerome's location to those coordinates
    * @param x @details x-coordinate
    * @param y @details y-coordinate
    */
    void init(int x, int y);

    /**
    * @brief Draws Jerome sprite on lcd display
    * @details ACCESSORS and MUTATORS
    * @param d @details The current direction the player is moving in (to determine which sprites to draw)
    * @param &lcd @details The lcd display (pass by reference)
    * @param _B @details Boolean variable representing whether button B is pressed or not (punch)
    * @param _X @details Boolean variable representing whether button X is pressed or not (kick)
    * @param _o @details enum for the current direction Jerome is facing (to determine which sprites to draw)
    */
    void draw(Direction d, N5110 &lcd, bool _B, bool _X, Orientation _o);

    /**
    * @brief Updates the location and state of the Jerome sprite
    * @details ACCESSORS and MUTATOR
    * @param d @details The current direction the player is moving in (to determine which sprites to draw)
    * @param mag @details The magnitude of the joystick
    * @param _A @details Boolean variable representing whether button B is pressed or not (jump)
    * @param _B @details Boolean variable representing whether button B is pressed or not (punch)
    * @param _X @details Boolean variable representing whether button X is pressed or not (kick)
    * @param _o @details enum for the current direction Jerome is facing (to determine which sprites to draw)
    * @param _distance @details 2 dimensional vector representing the horizontal and vertical distance between the Jerome and the enemy sprites.
    */
    void update(Direction d, float mag, bool _A, bool _B, bool _X, Orientation _o, Vector2D _distance);

    /** Two-dimensional vector storing location of Jerome
    * @brief ACCESSOR
    * @brief Gets position of Jerome
    * @returns The two dimensional coordinates of Jerome's position (Vector2D struct)
    */
    Vector2D get_jerome_pos();

    /**
    * @brief ACCESSOR
    * @brief Sets the Action enum to PUNCH or KICK depending on which buttons are pressed
    * @details The JeromeEngine class uses the position of the Jerome character to configure the enemy movement and actions
    * @returns The Action enum PUNCH or KICK
    */
    Action get_jerome_hit(bool _B, bool _X);

private:
    // JEROME MOVEMENT FUNCTIONS
    bool on_surface();
    void jump();
    void gravity_force();
    bool collision_detect(Vector2D _distance);
    void jerome_boundary(Vector2D _distance);

    // JEROME PARAMETERS
    Vector2D _pos;
    Vector2D _velocity;
    int _height;
    float _gravity;
    bool _punch;
    bool _kick;

    // MISCELLANEOUS FUNCTIONS
    void hold_sprite_frame(bool _B, bool _X, int frames);

    // CREATE OBJECTS
    Action _a;
    Orientation _o;
    Collision _collision;
    Frames _frames;
};
#endif