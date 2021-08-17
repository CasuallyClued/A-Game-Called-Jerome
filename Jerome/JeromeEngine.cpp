#include "JeromeEngine.h"

JeromeEngine::JeromeEngine()
{
    _health.player = 100; // Set initial player health to 100
    _health.cpu = 100; //Set initial cpu health to 100
    _level = 1; // Set initial level to 1
    _lives = 3; // Set number of lives to 3
    _pause_flag = false; //Set initial pause_flag condition to false
}

JeromeEngine::~JeromeEngine()
{
    // Nothing to do in destructor
}

void JeromeEngine::read_input(Gamepad &pad)
{
    // FLOAT VARIABLES
    _d = pad.get_direction(); // Direction of Joystick movement (Direction enum)
    _mag = pad.get_mag(); // How far the joystick is pushed in any direction (float between 0 and 1)
    // BOOLEAN VARIABLES (If the buttons are pressed their corresponding boolean variable will be set to true)
    _A = pad.check_event(Gamepad::A_PRESSED);
    _B = pad.check_event(Gamepad::B_PRESSED);
    _X = pad.check_event(Gamepad::X_PRESSED);
    _Y = pad.check_event(Gamepad::Y_PRESSED);
    _BACK = pad.check_event(Gamepad::BACK_PRESSED);
    _START = pad.check_event(Gamepad::START_PRESSED);
}

void JeromeEngine::update(Gamepad &pad, N5110 &lcd, bool &reset_flag, bool &play_flag)
{
    reset_flag = false; // Set reset flag to false
    play_flag = true; // Set play flag to true
    
    // PAUSE & RESET FUNCTIONALITY //
    if (_BACK == true) { // If back button is pressed
        play_flag = false; // Set play flag to false (so game doesn't restart by itself when reset)
        reset(); // Reset game
    }
    if (_START == true) { // If start button is pressed
        _pause_flag = !_pause_flag; // Toggle pause flag
    }
    if (_pause_flag) {
        display_pause(lcd); // Display pause_flag screen and stop game updating
    } else { // If not paused, run game

        // CHECKING IF KO HAS OCURRED //
        check_ko(pad, lcd);

        // POSITIONING ACCESORS //
        set_orientation(_o);
        get_pos(_jerome_pos, _enemy_pos);
        _jerome_pos = player.get_jerome_pos();
        _enemy_pos = cpu.get_enemy_pos();

        // UPDATE GAME (MUTATORS) //
        _distance = set_distance(_jerome_pos,_enemy_pos, _distance); //Set distance variable
        player.update(_d,_mag,_A, _B, _X, _o, _distance); // Update player (Jerome)
        _e_m = choose_enemy_movement(); // Set enemy movement enum
        cpu.enemy_update(_level, _e_m, _distance); // Update cpu (Enemy)
        check_hits(_level); // Check if any hits have occured
        set_health(); // Set the player's and the cpu's healths accoringly
    }
}

void JeromeEngine::draw(N5110 &lcd)
{
    // NOTE:
    // Display functins must be called in the order they are to be printed to the LCD
    // Each draw function overlaps the preceding function

    // COMBINING DISPLAY FUNCTIONS
    display_background(_jerome_pos,lcd); //Display background first
    cpu.enemy_draw(lcd, _o, _e_a);
    player.draw(_d, lcd, _B, _X, _o);
    // DISPLAY ICONS //
    display_health(lcd);
    display_icons(lcd);
    display_level(lcd);
    display_lives(lcd,_lives);
}

void JeromeEngine::check_hits(int level)
{
    _a = player.get_jerome_hit(_B, _X); // Check if player has striked

    if ((((_distance.x < 14 && _distance.x >= 0) ||  (_distance.x > -14 && _distance.x <= 0)) && _distance.y <= 3)) {
        // If Enemy is close enough to Jerome
        _e_a = choose_enemy_action(_level); // Choose strike
    } else {
        _e_a = E_NOTHING; // Do nothing
    }
}
void JeromeEngine::set_health()
{
    // SET HOW MUCH DAMAGE EACH STRIKE DOWS
    _punch_strength = 5;
    _kick_strength = 7;

    // PLAYER STRIKES //
    if (_a == PUNCH) {
        _health.cpu -= _punch_strength; // Decrease CPU's health
    }
    if (_a == KICK) {
        _health.cpu -= _kick_strength; // Decrease CPU's health
    }
    if (_health.cpu < 0) { // Stop health decreasing lower than 0
        _health.cpu = 0;
    }
    // CPU STRIKES //
    if (_e_a == E_PUNCH) {
        _health.player -= _punch_strength; // Decrease player's health
    }
    if (_e_a == E_KICK) {
        _health.player -= _kick_strength; // Decrease player's health
    }
    if (_health.player < 0) { // Stop health decreasing lower than 0
        _health.player = 0;
    }
    //cout << "CPU HEALTH = " << _health.cpu << std::endl;
}

void JeromeEngine::display_health(N5110 &lcd)
{
    if (_health.cpu >= 3) { // If health lower than 3 don't draw rectangle
        lcd.drawRect(83-(_health.cpu/3),3,_health.cpu/3, 3, FILL_BLACK); // 83-(_health.cpu/3) x axis value keeps rectangle                                                // in place and makes it decrease from left to right.
    }

    if (_health.player >= 3) { // If health lower than 3 don't draw rectangle
        lcd.drawRect(0,3,_health.player/3, 3, FILL_BLACK); //Draw rectangle
    }
}

void JeromeEngine::display_icons(N5110 &lcd)
{
    // USING SPRITE ACCESSORS //
    int *j;
    j = sprites.get_j();
    lcd.drawSprite(1,7,6,6,(int *)j);

    int *cpu;
    cpu = sprites.get_cpu();
    lcd.drawSprite(69,7,6,14,(int *)cpu);
}

EnemyAction JeromeEngine::choose_enemy_action(int level)
{
    // CONTROL DIFFICULTY //
    if (level < 7) { // Progressing difficulty
        _random_action = random_number_generator(4*(7-level));
    } else { // Max difficulty;7
        _random_action = random_number_generator(4); // 4 different outcomes
    }

    // CHOOSE ENEMY ACTION //
    // NOTE: //
    // The if statement below assigns an enemy action to a number output from the
    // random number generator

    if (_random_action == 0) { // Assign outcome 0 to PUNCH
        _e_a = E_PUNCH;
        //cout << "CPU PUNCH" << std::endl;

    } else if (_random_action == 1) { // Assign outcome 1 to KICK
        _e_a = E_KICK;
        //cout << "CPU KICK" << std::endl;
    } else { // Assign all other outcomes to do NOTHING (this means the enemy will not be attacking most of the time
        _e_a = E_NOTHING;
        //cout << "CPU NOTHING" << std::endl;
    }
    return _e_a;
}

EnemyMove JeromeEngine::choose_enemy_movement()
{
    // CONTROL DIFFICULTY //
    _random_action = random_number_generator(4); // 4 different possibilities (0,1,2,3)
    if(_level >= 4) {
        _random_jump = random_number_generator(75); // jump 1 every 75 frames on average (5 seconds at 15 fps)
        move_enemy_with_jump();
    } else {
        move_enemy_no_jump();
    }
    return _e_m; // Return EnemyMove enum
}

int JeromeEngine::random_number_generator(int modulus)
{
    // NOTE: //
    // This function is used throughout the class to generate random numbers which
    // can be used to randomise the behaviour of the Enemy.
    // Random numbers can be generated using the srand which returns random values
    // each second.
    // In order to create random variables that change value more quickly I inlcuded
    // the clock_t function and combined the output of srand with the clock
    // clock_t Returns the processor time consumed by the program. "http://www.cplusplus.com/reference/ctime/clock/"
    ////

    srand(time(NULL)); // Create random variable
    clock_t t; // Declare clock
    t = clock();
    //cout << "CLOCK = " << t << std::endl;
    int random_number = (rand()*t) % (modulus); // create new random variable every clock cycle.
    // random number is multiplied by clock and its modulus is taken producing a
    // random number between 0 and modulus - 1 (or there are modulus different
    // possible random number outcomes).

    return random_number; // Return random number
}

void JeromeEngine::get_pos(Vector2D &_jerome_pos, Vector2D &_enemy_pos)
{
    _jerome_pos = player.get_jerome_pos(); // Get Jerome's position
    _enemy_pos = cpu.get_enemy_pos(); // Get Enemy's position
    //cout << _jerome_pos.x << std::endl;
    //cout << "ENEMY = " <<_enemy_pos.x << std::endl;
}

Vector2D JeromeEngine::set_distance(Vector2D jerome_pos, Vector2D enemy_pos, Vector2D &distance)
{
    // SET POSITION VARIABLES TO INPUT PARAMETERS
    _jerome_pos = jerome_pos;
    _enemy_pos = enemy_pos;
    _distance = distance;

    Vector2D _distance = {_distance.x,_distance.y}; // Concatenate distance x and y coordinates into Vector2D struct
    _distance.x = (_enemy_pos.x) - (_jerome_pos.x); // Set horizontal
    _distance.y = (_enemy_pos.y) - (_jerome_pos.y); // Set vertical distance
    return _distance; // Return Vector2D _distance struct
}

void JeromeEngine::set_orientation(Orientation &o)
{
    // NOTE: //
    // _distance.x is defined as enemy position.x - jerome position.x
    // If value is positive that means Jerome is on the left of the enemy
    // And vice versa
    // Orientation is defined as the direction Jerome would face to always be
    // facing the enemy

    if (_distance.x  >= 0) {
        _o = RIGHT; // Set orientation enum to RIGHT
        //cout << "Orientation = RIGHT" << std::endl; // Jerome's orientation with respect to the enemy
    } else if (_distance.x < 0) {
        _o = LEFT; // Set orientation enum to LEFT
        //cout << "Orientation = LEFT" << std::endl;
    }
}

void JeromeEngine::check_ko(Gamepad &pad, N5110 &lcd)
{
    //cout << "Player health = " << _health.player << std::endl;
    //cout << "CPU health = " << _health.cpu << std::endl << std::endl;
    if (_health.cpu <= 0) { // JEROME KO
        jerome_win(pad,lcd); // Execute Jerome win code
    }

    if (_health.player <= 0) { // CPU KO
        enemy_win(pad,lcd,_lives); // Execute Enemy win code
    }
}

void JeromeEngine::flash_left_leds(Gamepad &pad, int times)
{
    int _times = times;
    for (int i = 1; i < _times; i++) { // Flash LED's as many times as input parameter int times
        // TURN LEDS ON
        pad.led(1,1);
        pad.led(2,1);
        pad.led(3,1);
        wait(0.1);
        // TURN LEDS OFF
        pad.led(1,0);
        pad.led(2,0);
        pad.led(3,0);
        wait(0.1);
    }
    wait(0.5); // Apply small wait
}

void JeromeEngine::flash_right_leds(Gamepad &pad, int times)
{
    int _times = times;
    for (int i = 1; i < _times; i++) { // Flash LED's as many times as input parameter int times
        // TURN LEDS ON
        pad.led(4,1);
        pad.led(5,1);
        pad.led(6,1);
        wait(0.1);
        // TURN LEDS OFF
        pad.led(4,0);
        pad.led(5,0);
        pad.led(6,0);
        wait(0.1);
    }
    wait(0.5); // Apply small wait
}

void JeromeEngine::display_jerome_win(N5110 &lcd)
{
    // SPRITE ACCESSORS //
    int *jerome_ko;
    jerome_ko = sprites.get_jerome_ko();
    int *ko;
    ko = sprites.get_ko_icon();

    Vector2D pos = player.get_jerome_pos(); // Set Vector2D struct Jerome's location to draw background in the right location
    lcd.clear(); // Clear LCD
    display_background(pos,lcd); // Display background
    lcd.drawRect(0,0,WIDTH,HEIGHT,FILL_TRANSPARENT); // Draw box around screen
    lcd.drawSprite(30,28,9,20,(int *)ko); //Draw KO sprite
    lcd.drawSprite(19,19,10,46,(int *)jerome_ko); // Draw Jerome KO sprite
    lcd.refresh(); // Refresh LCD
}

void JeromeEngine::display_cpu_win(N5110 &lcd)
{
    // SPRITE ACCESSORS //
    int *cpu_ko;
    cpu_ko = sprites.get_cpu_ko();
    int *ko;
    ko = sprites.get_ko_icon();

    Vector2D pos = player.get_jerome_pos(); // Set Vector2D struct Jerome's location to draw background in the right location
    lcd.clear(); // Clear LCD
    display_background(pos,lcd); // Display background
    lcd.drawRect(0,0,WIDTH,HEIGHT,FILL_TRANSPARENT); // Draw box around screen
    lcd.drawSprite(30,27,9,20,(int *)ko); //Draw KO sprite
    lcd.drawSprite(30,19,9,21,(int *)cpu_ko);// Draw CPU KO sprite
    lcd.refresh(); // Refresh LCD
}

void JeromeEngine::init()
{
    // RESET PLAYER POSITIONS //
    player.init(0,0); // Set Jerome's coordinates to (0,0)
    cpu.init(71,0); // Set Enemy's coordinates to (71,0)
    // RESET HEALTHS //
    _health.cpu = 100;
    _health.player = 100;
}

void JeromeEngine::reset()
{
    // RESET PLAYER POSITIONS //
    player.init(0,0); // Set Jerome's coordinates to (0,0)
    cpu.init(71,0); // Set Enemy's coordinates to (71,0)
    // RESET HEALTHS //
    _health.cpu = 100;
    _health.player = 100;
    _level = 1; // Go back to level 1
    _lives = 3; // Restore lives
}

void JeromeEngine::display_round(N5110 &lcd)
{
    lcd.clear(); // Clear LCD
    lcd.printString("ROUND",30,2); // Print ROUND string
    char buffer1[2]; // Declare buffer width 2
    sprintf(buffer1,"%2d",_level); // Set buffer to Level number (int _level)
    lcd.printString(buffer1,32,3); // Print buffer
    lcd.refresh(); // Refresh LCD
}

void JeromeEngine::display_level(N5110 &lcd)
{
    char buffer1[2]; //Declare buffer width 2
    sprintf(buffer1,"%2d",_level); //Set buffer to Level number (int _level)
    lcd.printString(buffer1,34,0); // Print buffer
}

void JeromeEngine::display_game_over(N5110 &lcd)
{
    Vector2D pos = player.get_jerome_pos(); // Set Vector2D struct Jerome's location to draw background in the right location
    lcd.clear(); // Clear LCD
    display_background(pos,lcd); // Draw background
    lcd.drawRect(0,0,WIDTH,HEIGHT,FILL_TRANSPARENT); // Draw box around screen
    lcd.printString("GAME",30,2); // Print GAME string
    lcd.printString("OVER",30,3); // Print OVER string
    lcd.refresh(); // Refresh LCD
}

void JeromeEngine::display_background(Vector2D coord, N5110 &lcd)
{
    // SPRITES ACCESSOR //
    int *background;
    background = sprites.get_background();
    ////
    // NOTE: //
    // The x-coordinate of where the background is drawn is determined by the coord parameter
    // When the function is called in JeromeEngine::draw(...) with the _jerome_pos
    // parameter, the background is moved depending on where Jerome is.
    // This creates the Parallax (3D) effect
    lcd.drawSprite(0-(coord.x/4),0,50,100,(int *)background); // Draw parallax background
    lcd.drawLine(0,47,84,47,FILL_BLACK); // The 'floor' line drawn at bottom of screen
}

void JeromeEngine::move_enemy_no_jump()
{
    if (_distance.x <= 13 && _distance.x >=0) {
        _e_m = E_STILL;
    }
    if (_distance.x >= -13 && _distance.x <0) {
        _e_m = E_STILL;
    }
    if (_distance.x < -13) {
        if (_random_action == 0 || _random_action == 2) {
            _e_m = E_RIGHT;
            //cout << "CPU MOVE RIGHT" << std::endl;
        }  else {
            _e_m = E_STILL;
            //cout << "CPU STILL" << std::endl;
        }
    }

    if (_distance.x > 13) {
        if (_random_action == 0 || _random_action == 2) {
            _e_m = E_LEFT;
            //cout << "CPU MOVE LEFT" << std::endl;
        }  else {
            _e_m = E_STILL;
            //cout << "CPU STILL" << std::endl;
        }
    }
}

void JeromeEngine::move_enemy_with_jump()
{
    if (_distance.x <= 13 && _distance.x >=0) { // Enemy is close to Jerome
        _e_m = E_STILL;                         // So stop moving
    }

    if (_distance.x >= -13 && _distance.x >=0) { // Enemy is close to Jerome
        _e_m = E_STILL;                          // So stop moving
    }
    // NOTE: //
    // The functions below use the _random_action variable to determine
    // what to set the EnemyMove enum _e_m to, controlling how the enemy moves.
    ////
    if (_distance.x < -13) {
        if (_random_action == 0 || _random_action == 2) {
            _e_m = E_RIGHT;
            //cout << "CPU MOVE RIGHT" << std::endl;
        }  else {
            _e_m = E_STILL;
            //cout << "CPU STILL" << std::endl;
        }
    }

    if (_distance.x > 13) {
        if (_random_action == 0 || _random_action == 2) {
            _e_m = E_LEFT;
            //cout << "CPU MOVE LEFT" << std::endl;
        }  else {
            _e_m = E_STILL;
            //cout << "CPU STILL" << std::endl;
        }
    }
    // ENABLED JUMP
    if (_random_jump == 0) { // If random jump == 1
        _e_m = E_JUMP;      // Set enemy movement to E_JUMP
    }
}

void JeromeEngine::display_pause(N5110 &lcd)
{
    lcd.drawRect(0,0,WIDTH,HEIGHT,FILL_TRANSPARENT); // Draw rectangle around screen
    lcd.drawRect(22,21,41,13,FILL_WHITE);
    lcd.drawRect(22,21,41,13,FILL_TRANSPARENT);
    lcd.printString("PAUSED",25,3); // Write PAUSED onto screen
    lcd.refresh(); // Refresh LCD
}

void JeromeEngine::display_lives(N5110 &lcd, int lives)
{
    // SPRITES ACCESSOR //
    int *life;
    life = sprites.get_life_icon();

    // Determine how many lives to display
    switch(lives) { // Only show the number of lives Jerome has left
        case 1: // If Jerome has 1 life left
            lcd.drawSprite(26,7,4,5,(int *)life); // Draw last life
            break;
        case 2: // If Jerome has 2 lives left
            lcd.drawSprite(26,7,4,5,(int *)life); // Draw last life
            lcd.drawSprite(20,7,4,5,(int *)life); // Draw second to last life
            break;
        case 3: // If Jerome has 3 lives left
            lcd.drawSprite(26,7,4,5,(int *)life); // Draw last life
            lcd.drawSprite(20,7,4,5,(int *)life); // Draw second to last life
            lcd.drawSprite(14,7,4,5,(int *)life); // Draw first life
            break;
    }
}

void JeromeEngine::jerome_win(Gamepad &pad, N5110 &lcd)
{
    lcd.inverseMode(); // Invert screen colours
    flash_left_leds(pad,10); // Flash left LEDs 10 times
    lcd.normalMode(); // Revert screen colours
    lcd.clear(); // Clear LCD screen

    display_jerome_win(lcd); // Display Jerome win screen
    lcd.refresh(); // Refresh LCD screen
    wait(1.0);
    _level++; // Increment level
    display_round(lcd); // Display current round
    wait(1.0);
    JeromeEngine::init(); // Reset player parameters
}

void JeromeEngine::enemy_win(Gamepad &pad, N5110 &lcd, int lives)
{
    _lives = lives;
    _lives--; // Decrement number of lives
    lcd.inverseMode(); // Invert screen colours
    flash_right_leds(pad,10); // Flash LEDs 10 times
    display_cpu_win(lcd); // Display CPU win screen
    wait(1.5); // Small wait

    // REVERT SCREEN
    lcd.normalMode(); // Revert screen
    lcd.clear(); // Clear screen
    lcd.refresh(); // Refresh screen

    // CHOOSE WHAT TO DO NEXT //
    if (_lives == 0) { // If no move lives left (GAME OVER)
        reset();
        display_game_over(lcd); // Display GAME OVER screen
        wait(1.3);
        display_round(lcd); // Display current round
        wait(1.0);

    } else { // If Jerome still has lives left (SAME ROUND)
        display_round(lcd); // Display current round
        wait(1.0);
        init(); // Reset player parameters
    }
}