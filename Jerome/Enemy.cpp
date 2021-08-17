#include "Enemy.h"

Enemy::Enemy()
{
    _enemy_pos.x = 70;
    _enemy_pos.y = 0;
    _height = 34 - _enemy_pos.y; // initial
}
Enemy::~Enemy()
{

}

int *Enemy::get_right() // Contains enemy right-facing sprite
{
    static int _right[13][11] =   {
        // 13x11 array for sprite
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,1,1,1,0,0,0 },
        { 0,0,0,0,0,1,1,1,0,0,0 },
        { 0,0,0,1,1,1,1,0,0,0,0 },
        { 0,0,1,0,1,1,1,0,1,0,0 },
        { 0,0,0,1,1,1,1,1,0,0,0 },
        { 0,0,0,0,1,1,1,0,0,0,0 },
        { 0,0,0,0,1,1,1,0,0,0,0 },
        { 0,0,0,0,1,0,0,1,0,0,0 },
        { 0,0,0,0,1,0,0,0,1,0,0 },
        { 0,0,0,0,1,0,0,0,1,0,0 },
        { 0,0,0,0,1,1,0,0,1,1,0 },
    };
    return *_right; // Return pointer to array
}

int *Enemy::get_left() // Contains enemy left-facing sprite
{
    static int _left[13][11] =   {
        // 13x11 array for sprite
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,1,1,1,0,0,0,0,0 },
        { 0,0,0,1,1,1,0,0,0,0,0 },
        { 0,0,0,0,1,1,1,1,0,0,0 },
        { 0,0,1,0,1,1,1,0,1,0,0 },
        { 0,0,0,1,1,1,1,1,0,0,0 },
        { 0,0,0,0,1,1,1,0,0,0,0 },
        { 0,0,0,0,1,1,1,0,0,0,0 },
        { 0,0,0,1,1,1,1,0,0,0,0 },
        { 0,0,1,0,0,0,1,0,0,0,0 },
        { 0,0,1,0,0,0,1,0,0,0,0 },
        { 0,1,1,0,0,1,1,0,0,0,0 },
    };
    return *_left; // Return pointer to array
}

int *Enemy::get_right_punch() // Contains enemy right-punching sprite
{
    static int _right_punch[13][11] =   {
        // 13x11 array for sprite
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,1,1,1,0,0,0,0 },
        { 0,0,0,0,1,1,1,0,0,0,0 },
        { 0,0,1,1,1,1,1,1,1,1,1 },
        { 0,1,0,1,1,1,0,0,0,0,0 },
        { 0,0,1,1,1,1,1,0,0,0,0 },
        { 0,0,0,1,1,1,0,0,0,0,0 },
        { 0,0,0,1,1,1,0,0,0,0,0 },
        { 0,0,0,1,0,0,1,0,0,0,0 },
        { 0,0,0,1,0,0,0,1,0,0,0 },
        { 0,1,1,0,0,0,1,0,0,0,0 },
        { 0,1,0,0,0,1,0,0,0,0,0 },
    };
    return *_right_punch; // Return pointer to array
}
int *Enemy::get_right_kick() // Contains enemy right-kicking sprite
{
    static int _right_kick[13][11] =   {
        // 13x11 array for sprite
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,1,1,1,0,0,0,0,0 },
        { 0,0,0,1,1,1,0,0,0,0,0 },
        { 0,1,1,1,1,0,0,0,0,0,0 },
        { 1,0,1,1,1,0,0,0,0,0,0 },
        { 0,1,1,1,1,0,0,0,0,0,1 },
        { 0,0,1,1,1,1,1,1,1,1,1 },
        { 0,0,1,1,0,0,0,0,0,0,0 },
        { 0,1,0,0,0,0,0,0,0,0,0 },
        { 0,0,1,0,0,0,0,0,0,0,0 },
        { 0,0,0,1,1,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0 },
    };
    return *_right_kick; // Return pointer to array
}

int *Enemy::get_left_punch() // Contains enemy left-punching sprite
{
    static int _left_punch[13][11] =   { //LEFT PUNCH
        // 13x11 array for sprite
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,1,1,1,0,0,0,0 },
        { 0,0,0,0,1,1,1,0,0,0,0 },
        { 1,1,1,1,1,1,1,1,1,0,0 },
        { 0,0,0,0,0,1,1,1,0,1,0 },
        { 0,0,0,0,1,1,1,1,1,0,0 },
        { 0,0,0,0,0,1,1,1,0,0,0 },
        { 0,0,0,0,0,1,1,1,0,0,0 },
        { 0,0,0,0,1,0,0,1,0,0,0 },
        { 0,0,0,1,0,0,0,1,0,0,0 },
        { 0,0,0,0,1,0,0,0,1,1,0 },
        { 0,0,0,0,0,1,0,0,0,1,0 },
    };
    return *_left_punch; // Return pointer to array
}

int *Enemy::get_left_kick() // Contains enemy left-kicking sprite
{
    static int _left_kick[13][11] =   { //LEFT KICK
        // 13x11 array for sprite
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,1,1,1,0,0,0 },
        { 0,0,0,0,0,1,1,1,0,0,0 },
        { 0,0,0,0,0,0,1,1,1,1,0 },
        { 0,0,0,0,0,0,1,1,1,0,1 },
        { 1,0,0,0,0,0,1,1,1,1,0 },
        { 1,1,1,1,1,1,1,1,1,0,0 },
        { 0,0,0,0,0,0,1,1,0,0,0 },
        { 0,0,0,0,0,0,0,0,1,0,0 },
        { 0,0,0,0,0,0,0,1,0,0,0 },
        { 0,0,0,0,0,1,1,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0 },
    };
    return *_left_kick; // Return pointer to array
}

void Enemy::enemy_draw(N5110 &lcd, Orientation _o, EnemyAction _e_a)
{
    // USING SPRITE ACCESSORS //
    int *enemy_left;
    enemy_left = get_left();
    int *enemy_right;
    enemy_right = get_right();
    int *enemy_right_punch;
    enemy_right_punch = get_right_punch();
    int *enemy_right_kick;
    enemy_right_kick = get_right_kick();
    int *enemy_left_punch;
    enemy_left_punch = get_left_punch();
    int *enemy_left_kick;
    enemy_left_kick = get_left_kick();
    _EnemyFrames.number = 2;
    hold_sprite_frame(_e_a, _EnemyFrames.number);

    _height = 34 - _enemy_pos.y; // Declare height
    
    // NOTE: //
    // This is almost the same function as the one in the Jerome clas
    // The difference is that when the orientation is RIGHT for example
    // the opposite sprites are drawn.
    // This is so that the enemy is always facing Jerome
    
    // If Jerome is facing the RIGHT
    if (_o == RIGHT) {
        lcd.drawSprite(_enemy_pos.x,_height,13,11,(int *)enemy_left); // Left-facing
        
        if (_EnemyFrames.punch > 0) { // If there are still more punch frames to display
            lcd.drawSprite(_enemy_pos.x,_height,13,11,(int *)enemy_left_punch); // Left-facing
            _EnemyFrames.punch--; // Decrease number of remaining punch frames to draw
        }
        if (_EnemyFrames.kick > 0) { // If there are still more kick frames to display
            lcd.drawSprite(_enemy_pos.x,_height,13,11,(int *)enemy_left_kick); // Right-facing
            _EnemyFrames.kick--; // Decrease number of remaining kick frames to draw
        }
    }
    
    // If Jerome is facing the LEFT
    if (_o == LEFT) {
        lcd.drawSprite(_enemy_pos.x,_height,13,11,(int *)enemy_right); // Right-facing

        if (_EnemyFrames.punch > 0) { // If there are still more punch frames to display
            lcd.drawSprite(_enemy_pos.x,_height,13,11,(int *)enemy_right_punch); // Right-facing
            _EnemyFrames.punch--; // Decrease number of remaining punch frames to draw
        }
        if (_EnemyFrames.kick > 0) { // If there are still more kick frames to display
            lcd.drawSprite(_enemy_pos.x,_height,13,11,(int *)enemy_right_kick); // Right-facing
            _EnemyFrames.kick--; // Decrease number of remaining kick frames to draw
        }
    }
}

Vector2D Enemy::get_enemy_pos()
{
    return _enemy_pos;
}

void Enemy::enemy_update(int level, EnemyMove _e_m, Vector2D _distance)
{
    _level = level; // Set level to input parameter
    
    _velocity.x = float(1+(_level*0.8f)); // Increase the enemy's speed with each level increase
    //cout << "Level = " << _level << std::endl;
    if (_e_m == E_LEFT && ((_distance.x <= 13 && _distance.x >= 0 && _distance.y >= -11)) == false) {
        // ONLY MOVE if not too close to Jerome
        _enemy_pos.x -= _velocity.x; // Move left
    }
    if (_e_m == E_RIGHT && ((_distance.x >= -13 && _distance.x <= 0 && _distance.y >= -11)) == false) {
        // ONLY MOVE if not too close to Jerome
        _enemy_pos.x += _velocity.x; // Move right
    }
    if (_e_m == E_STILL) {
        _velocity.x = 0; // Stop Jerome moving horizontally
    }
    if (_e_m == E_JUMP && _enemy_pos.y == 0) { // Only jump when enemy is on ground
        jump(); // Execute jump code
    }
    gravity_force(); // Make sure Enemy falls back to the ground if in air
    enemy_boundary(); // Make sure Enemy stays in the screen
}

void Enemy::init(int x, int y)
{
    _enemy_pos.x = x;
    _enemy_pos.y = y;
}

void Enemy::hold_sprite_frame(EnemyAction _e_a, int frames)
{
    // NOTES: //
    // This function determines how many frames to hold the current sprite for.
    // This helps the game animations run more smoothly at high frame rates.
    // When a striking button is pressed (B or X) the corresponding sprite is 
    // displayed on the screen (PUNCH or KICK) for one loop of game code or one frame.
    // At high frame rates these sprites are barely visible and the punch and kick 
    // sprites appear as a blur.
    
    // This function improves the animation of Jeromes character when striking
    // It does this by setting the variables _punch_frames and _kick_frames to a 
    // value which decreases every time the code is executed (once each frame) 
    // until the value is 0.
    
    // The values of _punch_frames and _kick_frames are used in Jerome::draw(...)
    // to determine what sprite is drawn
    // _B represents whether button B is pressed or not (punch)
    // _X represents whether button X is pressed or not (kick)
    // _frames represents how any frames to hold each sprite for
    ////
    
    if (_e_a == E_PUNCH) { // If a punch is to be displayed
        _EnemyFrames.punch = 2; // Set the number of punch frames to be diplayed to 2
        _EnemyFrames.kick = 0; //Reset kick counter to stop kick frame showing
    }
    if (_e_a == E_KICK) { // If a kick is to be displayed
        _EnemyFrames.kick = 2; // Set the number of kick frames to be diplayed to 2
        _EnemyFrames.punch = 0; //Reset punch counter to stop kick frame showing
    }
    
    // STOP FRAME COUNTERS DECREASING LOWER THAN 0
    if (_EnemyFrames.punch < 0) {
        _EnemyFrames.kick = 0;
    }
    if (_EnemyFrames.kick < 0) {
        _EnemyFrames.kick = 0;
    }
}

void Enemy::enemy_boundary()
{
    // 
    if (_enemy_pos.x > 71) {
        _enemy_pos.x = 71; // If at the right edge of the screen, stop moving
    }
    if (_enemy_pos.x < 0 ) {
        _enemy_pos.x = 0; // if at the left edge of the screen stop moving
    }
    if (_enemy_pos.y <= 0) {
        _enemy_pos.y = 0;
    }
}

void Enemy::jump()
{
    _velocity.y = 12; // Set Enemy's vertical velocity
    _enemy_pos.y += _velocity.y; // Change Enemy's vetical position based on vertical velocity
}

void Enemy::gravity_force()
{
    if (_enemy_pos.y >= 0) { // If Enemy is in the air
        _gravity = -3; // Set gravity variable
        _velocity.y += _gravity; // Change vertical velocity depending on gravity
        _enemy_pos.y += _velocity.y; // Change vertical position depending on vertical
                                     // Velocity
        if (_velocity.y < -40) {
            _velocity.y = -40; // Terminal velocity

        } else { // Else on ground
            _velocity.y = 0; // Set vertical velocity to 0
        }
    }
}