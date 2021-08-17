#ifndef ENEMY_H
#define ENEMY_H

// INCLUDE RELEVANT HEADERS //
#include "mbed.h"
#include "N5110.h"
#include "Jerome.h"
#include <iostream>
#include <ctime>

/** Enemy Frame struct */
/** @details Struct holds variables used to determine how long to show particular sprites on screen.*/
/** @details Used in Jerome::hold_sprite_frame function.*/
struct EnemyFrames {
    int punch; /**< integer to store number of punch frames */
    int kick; /**< integer to store number of kick frames */
    int number; /**< integer to store number of frames to hold for */
};

/** Enemy's action
 * @brief List of actions that the Enemy can execute
 */
enum EnemyAction {
    E_PUNCH,
    E_KICK,
    E_NOTHING
};
/** Enemy's movement
 * @brief List of movements that the Enemy can execute
 */
enum EnemyMove {
    E_LEFT, /**< Moving leftwards */
    E_RIGHT, /**< Moving rightwards */
    E_JUMP, /**< Jumping */
    E_STILL /**< Not moving */
};

/** Enemy Class
* @brief Contains functions, variables and sprites relating to the Enemy (cpu) character.
* @brief Public functions allow the updating and drawing of the Enemy sprite to be controlled from the JeromeEngine class.
* @brief Private functions control how the Enemy sprite responds to the actions
* @brief of the user.
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
Enemy cpu;
Direction _direction;
int main() {
    _level = 1;
    read_input(pad);
    init_players();
    // EXAMPLE OF HOW TO GET ENEMY POSITION
    _enemy_pos = cpu.get_enemy_pos(); //
    ////
    _distance = set_distance(_jerome_pos,_enemy_pos, _distance); //SET DISTANCE IN MAIN FUNCTION
    _e_a = choose_enemy_action(_level);
    _e_m = choose_enemy_movement(); // CHOOSE MOVEMENT IN MAIN FUNCTION 
    cpu.enemy_update(_level, _e_m, _distance); // UPDATE IN MAIN FUNCTION
    draw(lcd); // DRAW IN MAIN FUNCTION
}

Vector2D set_distance(Vector2D jerome_pos, Vector2D enemy_pos, Vector2D &distance)
{
    _jerome_pos = jerome_pos;
    _enemy_pos = enemy_pos;
    _distance = distance;

    Vector2D _distance = {_distance.x,_distance.y}; // SET Vector2D DISTANCE VARIABLE TO INPUT PARAMETERS
    _distance.x = (_enemy_pos.x) - (_jerome_pos.x);
    _distance.y = (_enemy_pos.y) - (_jerome_pos.y);
    //cout << "INTERNAL Distance x = " <<_distance.x << std::endl;
    //cout << "INTERNAL Distance y = " <<_distance.y << std::endl << std::endl;
    return _distance;
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
// SET ENEMY'S ACTION
EnemyAction choose_enemy_action(int level)
{
    // CONTROL DIFFICULTY //
    if (level < 7) { // Progressing difficulty
        _random_action = random_number_generator(3*(7-level));
    } else { // Max difficulty;7
        _random_action = random_number_generator(3);
    }

    // CHOOSE ENEMY ACTION //
    if (_random_action == 0) {
        _e_a = E_PUNCH;
        //cout << "CPU PUNCH" << std::endl;

    } else if (_random_action == 1) {
        _e_a = E_KICK;
        //cout << "CPU KICK" << std::endl;
    } else {
        _e_a = E_NOTHING;
        //cout << "CPU NOTHING" << std::endl;
    }
    return _e_a;
}

// EXAMPLE OF HOW TO DRAW ENEMY ON LCD
void draw(N5110 &lcd)
{
    cpu.enemy_draw(lcd, _o, _e_a);
}

// EXAMPLE OF HOW TO INITIALISE ENEMY
void init_players()
{
    cpu.init(70,0);
}

// EXAMPLE OF HOW TO UPDATE ENEMY
void update(Gamepad &pad, N5110 &lcd)
{
    cpu.enemy_update(_level, _e_m, _distance);
}

// EXAMPLE OF HOW TO USE SPRITE ACCESSORS
void draw_random_enemy(N5110 &lcd){
    int *enemy;
    // Declare pointer
    enemy = cpu.get_left_kick(); //CHANGE//
    // Create variable from pointer
    lcd.drawSprite(70,0,13,11,(int *)enemy); // Left-facing
    // (x-coord, y-coord,sprite width,sprite height,(int *)name_of_sprite)
        
    // NOTE: //
    // All of the sprite accessor methods work in the same way and so are not all individually documented
    // In order to draw a different sprite than the one shown in the example
    // use a different accessor method in the line marked with '//CHANGE//'
}
* @endcode
*/

class Enemy
{

public:
    /** Constructor */
    Enemy();
    /** Destructor */
    ~Enemy();

    // ENEMY SPRITES //
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to Enemy right-facing Sprite
    * @returns Pointer to sprite */
    int *get_right();
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to Enemy left-facing Sprite
    * @returns Pointer to sprite */
    int *get_left();
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to Enemy right-facing punch Sprite
    * @returns Pointer to sprite */
    int *get_right_punch();
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to Enemy right-facing kick Sprite
    * @returns Pointer to sprite */
    int *get_right_kick();
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to Enemy left-facing punch Sprite
    * @returns Pointer to sprite */
    int *get_left_punch();
    /** Sprite ACCESSOR
    * @brief Creates and returns pointer to Enemy left-facing kick Sprite
    * @returns Pointer to sprite */
    int *get_left_kick();

    /**
    * @brief Takes in coordinates x and y and sets Enemy's location to those coordinates
    * @param x @details x-coordinate
    * @param y @details y-coordinate
    */
    void init(int x, int y);

    /**
    * @brief Updates the location and state of the Enemy sprite
    * @details This function uses the input parameters to determine how to move
    * @details and how quickly and what action to perform (e.g. jump)
    * @param level @details Integer used in determining how fast the character moves and how frequently it strikes.
    * @param _e_m @details EnemyMove enum used in determining how the enemy should move
    * @param _distance @details 2 dimensional vector representing the horizontal and vertical distance between the Jerome and the enemy sprites.
    */
    void enemy_update(int level, EnemyMove _e_m, Vector2D _distance);

    /**
    * @brief Draws Enemy sprite on lcd display
    * @param &lcd @details The lcd display (pass by reference)
    * @param _o @details Orientation enum used to determine the way in which the Enemy sprites should face
    * @param _e_a @details EnemyAction enum used in determining which sprite to draw
    */
    void enemy_draw(N5110 &lcd, Orientation _o, EnemyAction _e_a);

    /** Two-dimensional vector storing location of Jerome
    * @brief Gets position of Jerome
    * @returns The two dimensional coordinates of Jerome's position (Vector2D struct)
    */
    Vector2D get_enemy_pos();

private:
    // ENEMY MOVEMENT FUNCTIONS
    void hold_sprite_frame(EnemyAction _e_a, int frames);
    void enemy_boundary();
    void jump();
    void gravity_force();

    // ENEMY PARAMETERS
    Vector2D _velocity;
    Vector2D _enemy_pos;
    int _height;
    int _gravity;
    int _level;

    // CREATE OBJECTS
    Orientation _o;
    EnemyMove _e_m;
    EnemyFrames _EnemyFrames;
};
#endif