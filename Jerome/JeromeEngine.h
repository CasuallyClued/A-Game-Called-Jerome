#ifndef JEROMEENGINE_H
#define JEROMEENGINE_H

// INCLUDE RELEVANT HEADERS //
#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"
#include "Sprites.h"
#include "Jerome.h"
#include "Enemy.h"
#include <iostream>

/** Health struct
 * @brief Contains variables for the health of the player and the cpu
 */
struct Health {
    int player; /**< integer to store the player's health */
    int cpu; /**< integer to store the enemy's health */
};

/** JeromeEngine Class
* @brief Contains all the functions to allow the player to control Jerome and the AI to move the CPU Enemy character
* @brief Public functions allow the updating and drawing of the game to be controlled externally in main.cpp
* @brief Private functions create parameters to control the flow of the game
* @author Kamal Gamir - Shahin, University of Leeds
* @version 1.0
* @date May 2019
* @code

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"
#include "Sprites.h"
#include "Jerome.h"
#include "JeromeEngine.h"
#include <iostream>
// OBJECTS //
N5110 lcd(PTC9,PTC0,PTC7,PTD2,PTD1,PTC11); // LCD Constructor
Gamepad pad;
Sprites sprites;
Jerome jerome;
JeromeEngine game;

// FUNCTIONS //
void init();
void render();
void randomise();


int main()
{
    int fps = 15;
    init();
    welcome_draw(pad,fps);
    // GAME LOOP
    //cout << "Game loop initiated" << std::endl;
// EXAMPLE HOW TO USE UPDATE FUNCTION AND READ INPUT
    while (1) {
        game.read_input(pad); // EXAMPLE HOW TO READ INPUT
        game.update(pad,lcd);
        wait_ms(1000/fps);
        render();
    }
}

// EXAMPLE HOW TO USE DRAW FUNCTION
void render()
{
    lcd.clear();
    game.draw(lcd);
    lcd.refresh();
}

// EXAMPLE HOW TO USE RANDOM NUMBER GENERATOR
void randomise(){
    int random_number = random_number_generator(5);
    // Will create a random number between 0 and 4
}
* @endcode
*/

class JeromeEngine
{

public:
    /** Constructor */
    JeromeEngine();
    /** Destructor */
    ~JeromeEngine();

    /**
    * @brief Reads the input from the Gamepad
    * @details Takes in the states of button presses and joystick movements on the gamepad
    * @details Adjusts the corresponding variables depending on the inputs received
    * @param pad @details The Gamepad object
    */
    void read_input(Gamepad &pad);
    
    /**
    * @brief Updates the state of the game
    * @details Combines all of the private JeromeEngine methods which configure how the game operates, the game's parameters
    * @details It passes these parameters to the correct Jerome and Enemy class functions to control how they move
    * @param pad @details The Gamepad object
    * @param lcd @details The N5110 LCD screen object
    * @param reset_flag @details Boolean variable used to reset the game (take user back to home screen)
    */
    void update(Gamepad &pad, N5110 &lcd, bool &reset_flag, bool &play_flag);
    
    /**
    * @brief Draws the game on the LCD
    * @details Combines the Jerome and Enemy drawing functions and JeromeEngine's private drawing methods to draw the game on the LCD
    * @param lcd @details The N5110 LCD screen object
    */
    void draw(N5110 &lcd);
    
    /**
    * @brief Resets and initialises the game
    * @details Resets all game parameters and variables to their details to reset the game
    * @details Used within the class when Game over to reset game
    * @details Used in main.cpp to reset the game if back button pressed
    */
    void reset();
    
    /**
    * @brief Generates a random number
    * @details This function is used to return a random number
    * @details It is used when random behaviour is needed in the game (e.g. in choose_enemy_movement) to randomise the movement of the enemy
    * @param mod_x @details The modulus of the random to be created (0 <= random_number <= mod_x - 1)
    * @returns Random number between 0 and mod_x - 1
    */
    int random_number_generator(int mod_x);


private:
    // GAME FLOW FUNCTIONS //
    void check_hits(int level);
    void check_ko(Gamepad &pad, N5110 &lcd);
    void jerome_win(Gamepad &pad, N5110 &lcd);
    void enemy_win(Gamepad &pad, N5110 &lcd, int lives);
    void init();
    
    // MUTATOR AND ACCESSOR METHODS //
    Vector2D set_distance(Vector2D jerome_pos, Vector2D enemy_pos, Vector2D &_distance);
    EnemyAction choose_enemy_action(int level);
    EnemyMove choose_enemy_movement();
    
    
    void get_pos(Vector2D &_jerome_pos, Vector2D &_enemy_pos);
    void set_health();
    void set_orientation(Orientation &_o);
    void move_enemy_no_jump();
    void move_enemy_with_jump();
    
    // DISPLAY (DRAWING) FUNCTIONS //
    void display_health(N5110 &lcd);
    void display_icons(N5110 &lcd);
    void display_jerome_win(N5110 &lcd);
    void display_cpu_win(N5110 &lcd);
    void display_round(N5110 &lcd);
    void display_level(N5110 &lcd);
    void display_game_over(N5110 &lcd);
    void display_background(Vector2D coord, N5110 &lcd);
    void display_pause(N5110 &lcd);
    void display_lives(N5110 &lcd, int lives);
    
    // LED FUNCTIONS //
    void flash_left_leds(Gamepad &pad, int times);
    void flash_right_leds(Gamepad &pad, int times);
    
    // CLASS OBJECT DECLARATION //
    Jerome player; // Controlled by user
    Enemy cpu; // Controlled by AI
    Sprites sprites;
    
    // STRUCT DECLARATION //
    Direction _d;
    Orientation _o;
    Action _a;
    EnemyAction _e_a;
    EnemyMove _e_m;
    Health _health;
    
    // INPUT PARAMETERS //
    float _mag;
    bool _A;
    bool _B;
    bool _X;
    bool _Y;
    bool _BACK;
    bool _START;
    
    // GAME CHARACTERISTICS VARIABLES //
    int _punch_strength;
    int _kick_strength;
    int _level;
    int _lives;
    bool _pause_flag;
    
    // AI VARIABLES TO BE RANDOMISED //
    int _random_action;
    int _random_jump;

    
    // POSITIONING VARIABLES //
    Vector2D _distance;
    Vector2D _jerome_pos;
    Vector2D _enemy_pos;
};

#endif