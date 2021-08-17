/*
ELEC2645 Embedded Systems Project
School of Electronic & Electrical Engineering
University of Leeds
Name: Kamal Gamir - Shahin
Username: ll15kygs
Student ID Number: 201039795
Date: 18/03/2019
*/

// INCLUDE RELEVANT HEADERS //
#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"
#include "Sprites.h"
#include "Jerome.h"
#include "JeromeEngine.h"
#include <iostream>

// DEFINE TESTING COMPILATION MACRO //
#ifdef WITH_TESTING
# include "Testing.h"
#endif

// OBJECT DECLARATION //
N5110 lcd(PTC9,PTC0,PTC7,PTD2,PTD1,PTC11); // LCD Constructor
Gamepad pad;
Sprites sprites;
Jerome jerome;
JeromeEngine game;

// MAIN GAME FUNCTIONS //
void init();
void render();
// WELCOME SCREEN FUNCTIONS //
void welcome_init(int arrow_pos);
void display_jerome_icon();
void settings_menu(Gamepad &pad, N5110 &lcd, int fps, bool &settings_flag, double &brightness, double &contrast);
void welcome_draw(Gamepad &pad, N5110 &lcd, int fps, int &arrow_pos);
void welcome_screen_control(Gamepad &pad, int &arrow_pos);
void display_settings_icons(N5110 &lcd);
void display_controls(N5110 &lcd);
void display_credits(N5110 &lcd);
void modify_settings(Gamepad &pad, N5110 &lcd, int &select);

// CONTINUITY FLAGS //
// Allow navigation between menus and game states without the use of labels and goto's
bool play_flag;
bool settings_flag;
bool continue_flag;
bool reset_flag;

// VARIABLES
int fps;
int arrow_pos; // Used to position arrow
int select; // Used to position select rectangle in settings
// SETTINGS PARAMETERS
double brightness = 0.5;
double contrast = 0.5;

int main()
{
    init(); // Initialise Gamepad and LCD
#ifdef WITH_TESTING
    // RUN TESTING //
    int number_of_failures = run_tests();
    if(number_of_failures > 0) { // If any test have failed
        cout << "Number of failed tests = " << number_of_failures;
        lcd.clear(); // Clear LCD
        lcd.refresh(); // Refresh LCD
        wait(2);
        return number_of_failures;  // Returning a number ends the program
        // Because main is an int function
    }
#endif
    // CREDITS INTRO //
    display_credits(lcd); // Display credits
    wait(1.5); // Short wait

    // NOTE: //
    // The flow between the game, the menus and the home screen are all
    // controlled with boolean flags
    // These are set accordingly by functions in main.cpp and in JeromeEngine::update
    // The use of these flags means that the entire main function can be put in an
    // infinite loop

    // INFINITE LOOP
    while(1) {
        if (reset_flag == true) {
            reset_flag = false; // set reset flag to false
            play_flag = false; // set play flag to false
            game.reset(); // reset game
        }
        // Initialise reset flag to false
        welcome_draw(pad,lcd,fps,arrow_pos); // Display welcome screen
        // NOTE: //
        // This function contains loops that continue as long as certain flags are set to true
        // Flags are also set to control the menu and welcome screen flow
        // Moving past this line means that the appropriate flags have been set to start the game

        display_controls(lcd); // Display the controls
        wait(2.5); // Small wait

        // GAME LOOP
        //cout << "Game loop initiated" << std::endl;
        while (reset_flag == false) { // Execute code while reset_flag is false
            game.read_input(pad); // Read pad input
            game.update(pad,lcd,reset_flag,play_flag); // Update game
            wait_ms(1000/fps); // Wait for one frame duration
            render(); // Render to screen
            
            if (pad.check_event(Gamepad::BACK_PRESSED) == true) { // If back button pressed
                reset_flag = true; // Set reset flag to true
            } else {
                reset_flag = false; // Otherwise set it to false
            }

        }
    }
}

void init()
{
    // INITIALISE SCREEN AND LCD
    lcd.init(); // Initialise the LCD
    lcd.setContrast(contrast); // Initial contrast set at 0.5
    lcd.setBrightness(brightness); // Initial brightness set at 0.5
    lcd.clear(); // Clear the screen
    lcd.refresh(); // Refresh the screen
    pad.init(); // Initialise the pad

    // SET FLAGS AND VARIABLES
    fps = 15; // Set fps to 15
    play_flag = false; // Set initial play flag to false
    reset_flag = false;
    arrow_pos = 8; // Set arrow position to 8 (above PLAY button)
    select = 2; // Set position of rectangle in settings to around the brightness setting
}

void welcome_init(int arrow_pos)
{
    // SPRITES ACCESSORS //
    // PLAY BUTTON
    int *play;
    play = sprites.get_play();
    lcd.drawSprite(0,36,8,24,(int *)play); // Draw play button
    //
    // TITLE
    int *title;
    title = sprites.get_title();
    lcd.drawSprite(34,3,15,48,(int *)title); // Draw sprite of Title (JEROME)
    //
    // SETTINGS BUTTON
    int *settings;
    settings  = sprites.get_settings();
    lcd.drawSprite(36,36,8,41,(int *)settings); // Draw sprite of Settings button
    //
    // ARROW
    int *arrow;
    arrow  = sprites.get_arrow();
    lcd.drawSprite(arrow_pos,26,7,7,(int *)arrow); // Draw sprite of arrow
}

void welcome_draw(Gamepad &pad, N5110 &lcd, int fps, int &arrow_pos)
{
    enum Direction; // Create direction enum to store direction of the Joystick

    while (play_flag == false) {
        lcd.clear(); // Clear the LCD
        play_flag = false; // Prevent game from starting
        settings_flag = false; // Prevent settings from showing

        welcome_init(arrow_pos); //Initialise welcome screen
        display_jerome_icon(); //
        int joystick = pad.get_direction(); // Get joystick movement direction
        welcome_screen_control(pad,arrow_pos); // Control arrow on welcome screen

        while(settings_flag == true) { // If user has selected settings
            lcd.clear(); // Clear the LCD
            settings_menu(pad,lcd,fps,settings_flag,brightness,contrast); // Execute settings menu code
            lcd.refresh(); // Refresh the LCD
        }
        wait_ms(1000/fps); // Wait one frame
        lcd.refresh(); //Refresh LCD
    }
}

void render()
{
    lcd.clear(); // Clear LCD buffer
    game.draw(lcd); // Draw the game
    lcd.refresh(); // Refresh the LCD
}

void display_jerome_icon()   // Show animated jerome on welcome screen
{
    // SPRITES ACCESSOR //
    int *jerome_right_punch; // Create pointer
    jerome_right_punch = jerome.get_jerome_right_punch(); // Set variable
    lcd.drawSprite(4,4,13,11,(int *)jerome_right_punch); // Draw sprite onto LCD
}

void welcome_screen_control(Gamepad &pad, int &arrow_pos)
{
    if (pad.get_direction() == W) {
        arrow_pos = 8; // Move arrow to above play button
    }
    if (pad.get_direction() == E) {
        arrow_pos = 50; // Move arrow to above settings button
    }

    // GET INPUTS FROM GAMEPAD
    bool _A = pad.check_event(Gamepad::A_PRESSED);
    bool _START = pad.check_event(Gamepad::START_PRESSED);

    if(_A || _START) { // If the button A is pressed (an action is wanted)
        if (arrow_pos == 8) {
            play_flag = true; // Set play flag to true if arrow is over play button
            settings_flag = false; // Ensure settings do not sbow
            //cout << "PLAY" << std::endl;
        } else {
            settings_flag = true; // Set settings flag to true if arrow is over settings button
            play_flag = false; //Ensure game does not start
            //cout << "SETTINGS" << std::endl;
        }
    }
}

void settings_menu(Gamepad &pad, N5110 &lcd, int fps, bool &settings_flag, double &brightness, double &contrast)
{
    lcd.clear(); // Clear the LCD
    // DISPLAY BRIGHTNESS & CONTRAST BARS AND ICONS //
    // NOTE: //
    // The rectangles' widths are set according to their respective parameter value
    // When the lcd.drawRect function is called with a width parameter of 0
    // a line is displayed.
    // To prevent this occurring the rectangles are only drawn in the cases where
    // their widths will be above 0.

    if (brightness > 0.2) {
        lcd.drawRect(30,4,((brightness-0.2)*62.5f),10,FILL_BLACK); // Draw brightness rectangle
    }
    if (contrast > 0.42) {
        lcd.drawRect(30,20,((contrast-0.42)*200),10,FILL_BLACK); // Draw contrast rectangle
    }
    display_settings_icons(lcd);
    ////
    modify_settings(pad,lcd,select); // Modify settings according to user input
    // DISPLAY AND MOVE SELECT BAR //
    // NOTE: //
    // Y-coordinate value determined by what setting is currently being modified
    lcd.drawRect(28,select,54,14,FILL_TRANSPARENT); // Draw select rectangle
    lcd.refresh(); // Refresh LCD
    wait_ms(1000/fps); // Wait one frame
}

void display_settings_icons(N5110 &lcd)
{
    // SPRITE ACCESSORS //
    int *brightness_icon;
    brightness_icon = sprites.get_brightness_icon();
    lcd.drawSprite(4,3,11,11,(int *)brightness_icon); // Draw brightness icon
    int *contrast_icon;
    contrast_icon = sprites.get_contrast_icon();
    lcd.drawSprite(6,22,7,7,(int *)contrast_icon); // Draw contrast icon

    lcd.printString("Y - DEFAULTS",8,5); // Print text to screen
}

void display_controls(N5110 &lcd)
{
    lcd.clear(); // Clear LCD
    lcd.printString("JOYSTICK <->",8,0); // Print text to screen
    lcd.printString("A - JUMP",8,1); // Print text to screen
    lcd.printString("B - PUNCH",8,2); // Print text to screen
    lcd.printString("X - KICK",8,3); // Print text to screen
    lcd.printString("START - PAUSE",8,4); // Print text to screen
    lcd.printString("BACK - HOME",8,5); // Print text to screen
    lcd.refresh(); //Refresh LCD
}

void display_credits(N5110 &lcd)
{
    lcd.clear(); // Clear the LCD
    // SPRITES ACCESSOR //
    int *title;
    title = sprites.get_title();
    lcd.drawSprite(18,2,15,48,(int *)title); // Draw sprite of Title (JEROME)
    lcd.printString("Kamal",8,2.5); // Print text to screen
    lcd.printString("Gamir-Shahin",8,3.5); // Print text to screen
    lcd.printString("May 2019",8,4.5); // Print text to screen
    lcd.refresh(); // Refresh the LCD
}

void modify_settings(Gamepad &pad, N5110 &lcd, int &select)
{
    // READ INPUTS //
    bool _A = pad.check_event(Gamepad::A_PRESSED);
    bool _Y = pad.check_event(Gamepad::Y_PRESSED);
    bool _START = pad.check_event(Gamepad::START_PRESSED);

    // NOTE: //
    // When the LCD lcd.setContrast and lcd.setBrightness mutator methods are used, the
    // LCD screen flashes
    // In order to stop the LCD screen flashing on every frame (which is irritating
    // for the user), this flag is used to ensure the mutator methods are only called
    // if a change has occured to their corresponding setting
    bool change_flag = false;

    if (_A || _START) {
        settings_flag = false; // If A is pressed leave the settings menu
    }
    if (_Y) { // If Y is pressed reset the settings to their defaults
        brightness = 0.5; // Default value
        contrast = 0.5; // Default value
        change_flag = true; // Make change occur
    }
    if (pad.get_direction() == N) { // If joystick pushed upwards
        select = 2; // Move select box up
    }
    if (pad.get_direction() == S) { // If joystick moved downwards
        select = 18; // Move select box down
    }

    // IF MODIFYING THE BRIGHTNESS (SELECT BOX HOVERS OVER BRIGHTNESS)
    if (select == 2 && pad.get_direction() == E) { // If joystick pushed to the right
        change_flag = true;
        brightness += 0.05; // Increase brightness by small amount
        if (brightness > 1) { // Prevent brightness exceeding max value
            brightness = 1;
        }
    }
    if (select == 2 && pad.get_direction() == W) { // If joystick pushed to the left
        change_flag = true;
        brightness -= 0.05; // Decrease brightness by small amount
        if (brightness < 0.2) { // Prevent brightness exceeding min allowed value
            brightness = 0.2;
        }
    }

    // IF MODIFYING THE CONTRAST (SELECT BOX HOVERS OVER CONTRAST)
    if (select == 18 && pad.get_direction() == E) { // If joystick pushed to the right
        change_flag = true; // Make sure change will be implemented
        contrast += 0.01; // Increase contrast by small amount
        if (contrast > 0.67) { // Prevent contrast exceeding max allowed value
            contrast = 0.67;
        }
    }
    if (select == 18 && pad.get_direction() == W) { // If joystick pushed to the left
        change_flag = true; // Make sure change will be implemented
        contrast -= 0.01; // Decrease contrast by small amount
        if (contrast < 0.42) { // Prevent contrast exceeding min allowed value
            contrast = 0.42;
        }
    }
    if (change_flag == true) { // Only set parameters if a change flag has occured
        lcd.setBrightness(brightness); // Set brightness
        lcd.setContrast(contrast); // Set contrast
        change_flag = false; // Reset change flag
    }
}