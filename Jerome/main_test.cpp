/*
ELEC2645 Embedded Systems Project
School of Electronic & Electrical Engineering
University of Leeds
Name: Kamal Gamir - Shahin
Username: ll15kygs
Student ID Number: 201039795
Date: 18/03/2019
*/
///////// pre-processor directives ////////
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


struct settings {
    float brightness;
    float contrast;
};


enum ArrowLocation {
    PLAY,
    SETTINGS,
    BRIGHTNESS,
    CONTRAST,
    CONTROLS,
    NOWHERE
};


// FUNCTIONS //
void init();
void welcome_init(int x);
void render();
void display_jerome_icon(int fps);
void welcome_draw(Gamepad &pad, int fps);
//void home_screen();

bool play_game;
ArrowLocation arrow_location;

int main()
{
    //arrow_location = PLAY; //Initial position is play
    int fps = 15; // Set fps to 15
    //play_game = false;
    init();
    welcome_draw(pad,fps);
    // GAME LOOP
    //cout << "Game loop initiated" << std::endl;
    while (1) {
        game.read_input(pad); // Read pad input
        game.update(pad,lcd); // Update game
        wait_ms(1000/fps); // Wait for one frame duration
        render(); // Render to screen
    }
}

void init()
{
    lcd.init(); // Initialise the LCD
    lcd.setContrast(0.5); // Initial contrast set at 0.5
    lcd.setBrightness(0.5); // Initial brightness set at 0.5
    lcd.clear(); // Clear the screen
    pad.init();
    lcd.refresh();
}

void welcome_init(int x)
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
    lcd.drawSprite(x,26,7,7,(int *)arrow); // Draw sprite of arrow
}

void welcome_draw(Gamepad &pad, int fps, int play_game)
{
    arrow_location = PLAY; //Initial position is play
    enum Direction;
    int x = 8;

//    while (pad.check_event(Gamepad::A_PRESSED) == false) {
    while (play_game == false) {
        welcome_init(x);
        display_jerome_icon(fps);
        lcd.clear();
        lcd.refresh();

        int joystick = pad.get_direction();
        if (pad.get_direction() == W) {
            x = 8; // Above settings button
            arrow_location = PLAY;
        }

        if (pad.get_direction() == E) {
            x = 50; // Above settings button
            arrow_location = SETTINGS;
        }
        //home_screen();
    }
}

void render()
{
    lcd.clear(); // Clear LCD buffer
    game.draw(lcd); // Draw the game
    lcd.refresh(); // Refresh the LCD
}

void display_jerome_icon(int fps)   // Show animated jerome on welcome screen
{
    int *jerome_right_punch;
    jerome_right_punch = jerome.get_jerome_right_punch();
    lcd.drawSprite(4,4,13,11,(int *)jerome_right_punch);
    lcd.refresh();
    wait_ms(1000/fps);
}
//void home_screen()
//{
//    if (pad.check_event(Gamepad::A_PRESSED) == true && arrow_location == PLAY) {
//        lcd.clear();
//        lcd.refresh();
//        wait(0.2);
//        play_game = true;
//    }
//}