#include "Jerome.h"

Jerome::Jerome()
{
    _pos.x = 0; // Set initial horizontal position to 0
    _pos.y = 0; // Set initial vertical position to 0
    _height = 34 - _pos.y; //Set height to correct position
}
Jerome::~Jerome()
{
    // Nothing to do in destructor
}

int *Jerome::get_jerome_right() // Contains jerome right-facing sprite
{
    // 13x11 array for sprite
    static int _jerome_right[13][11] =   {
        { 0,0,0,0,0,1,1,1,0,0,0 },
        { 0,0,0,0,0,1,1,1,1,1,0 },
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
    return *_jerome_right; // Return pointer to array
}

int *Jerome::get_jerome_left() // Contains jerome left-facing sprite
{
    // 13x11 array for sprite
    static int _jerome_left[13][11] =   {
        { 0,0,0,1,1,1,0,0,0,0,0 },
        { 0,1,1,1,1,1,0,0,0,0,0 },
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
    return *_jerome_left; // Return pointer to array

}

int *Jerome::get_jerome_right_punch() // Contains jerome right-punching sprite
{
    // 13x11 array for sprite
    static int _jerome_right_punch[13][11] =   {
        { 0,0,0,0,1,1,1,0,0,0,0 },
        { 0,0,0,0,1,1,1,1,1,0,0 },
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
    return *_jerome_right_punch; // Return pointer to array

}
int *Jerome::get_jerome_right_kick() // Contains jerome right-kicking sprite
{
    // 13x11 array for sprite
    static int _jerome_right_kick[13][11] =   {
        { 0,0,0,1,1,1,0,0,0,0,0 },
        { 0,0,0,1,1,1,1,1,0,0,0 },
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
    return *_jerome_right_kick; // Return pointer to array
}

int *Jerome::get_jerome_left_punch() // Contains jerome left-punching sprite
{

    static int _jerome_left_punch[13][11] =   {
        // 13x11 array for sprite
        { 0,0,0,0,1,1,1,0,0,0,0 },
        { 0,0,1,1,1,1,1,0,0,0,0 },
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
    return *_jerome_left_punch; // Return pointer to array
}

int *Jerome::get_jerome_left_kick() // Contains jerome left-kicking sprite
{

    static int _jerome_left_kick[13][11] =   {
        // 13x11 array for sprite
        { 0,0,0,0,0,1,1,1,0,0,0 },
        { 0,0,0,1,1,1,1,1,0,0,0 },
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
    return *_jerome_left_kick; // Return pointer to array
}

void Jerome::draw(Direction d, N5110 &lcd, bool _B, bool _X, Orientation _o)
{
    // USING SPRITE ACCESSORS //
    int *jerome_left;
    jerome_left = get_jerome_left();
    int *jerome_right;
    jerome_right = get_jerome_right();
    int *jerome_right_punch;
    jerome_right_punch = get_jerome_right_punch();
    int *jerome_right_kick;
    jerome_right_kick = get_jerome_right_kick();
    int *jerome_left_punch;
    jerome_left_punch = get_jerome_left_punch();
    int *jerome_left_kick;
    jerome_left_kick = get_jerome_left_kick();

    // Determining how long to hold punch and kick sprites on the screen
    _frames.number = 2;
    hold_sprite_frame(_B,_X,_frames.number);
    //cout << "Punch counter = " << _frames.punch << std::endl;
    //cout << "Kick counter = " << _frames.kick << std::endl;

    // CHOOSE WHICH SPRITES TO DRAW
    if (_o == RIGHT) { // If facing right
        lcd.drawSprite(_pos.x,_height,13,11,(int *)jerome_right); // Right-facing
        
        if (_frames.punch > 0) { // If there are still more punch frames to display
            lcd.drawSprite(_pos.x,_height,13,11,(int *)jerome_right_punch); // Right-facing PUNCH
            _frames.punch--; // Decrease number of remaining punch frames to draw
        }
        if (_frames.kick > 0) { // If there are still more kick frames to display
            lcd.drawSprite(_pos.x,_height,13,11,(int *)jerome_right_kick); // Right-facing KICK
            _frames.kick--; // Decrease number of remaining kick frames to draw
        }

    }
    if (_o == LEFT) { // If facing left
        lcd.drawSprite(_pos.x,_height,13,11,(int *)jerome_left); // Left-facing
        
        if (_frames.punch > 0) { // If there are still more punch frames to display
            lcd.drawSprite(_pos.x,_height,13,11,(int *)jerome_left_punch); // Left-facing PUNCH
            _frames.punch--; // Decrease number of remaining punch frames to draw
        }
        if (_frames.kick > 0) { // If there are still more kick frames to display
            lcd.drawSprite(_pos.x,_height,13,11,(int *)jerome_left_kick); // Left-facing KICK
            _frames.kick--; // Decrease number of remaining kick frames to draw
        }
    }
}

void Jerome::hold_sprite_frame(bool _B, bool _X, int frames)
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
    
    if (_B == true) { // If a punch is to be displayed
        _frames.punch = 2; // Set the number of punch frames to be diplayed to 2
        _frames.kick = 0; //Reset kick frame counter to stop kick frame showing
    }
    if (_X == true) { // If a kick is to be displayed
        _frames.kick = 2; // Set the number of kick frames to be diplayed to 2
        _frames.punch = 0; //Reset punch frame counter to stop kick frame showing
    }
    // STOP FRAME COUNTERS DECREASING LOWER THAN 0
    if (_frames.punch < 0) {
        _frames.kick = 0;
    }
    if (_frames.kick < 0) {
        _frames.kick = 0;
    }
}

void Jerome::update(Direction d, float mag, bool _A, bool _B, bool _X, Orientation _o, Vector2D _distance)
{
    _height = 34 - _pos.y;  //Set height so that sprite is drawn in the correct place
                            //Screen is 48 pixels high
                            //Sprite is 13 pixels tall
                            //Floor is 1 pixel thick
                            // 48 - 13 - 1 = 34
                            
    _velocity.x = float(mag*6.0f);  // Set Jerome's horizontal velocity depending 
                                    // on how far the joystick is pushed
    collision_detect(_distance);    // Detect if any collisions have occured
                                            // Between Jerome and the enemy

    if ((d == E || d == NE || d == SE)  && _collision.left == false ) {
        // Only move if there is no obstacle in the way (&_collision.left)
        _pos.x += _velocity.x; // Move right
    }

    if ((d == W || d == NW || d == SW)  && _collision.right == false ) {
        // Only move if there is no obstacle in the way (&_collision.right)
        _pos.x -= _velocity.x; // Move left
    }

    if (_A == true) { // If button A is pressed
        //cout << "A button has been pressed" << std::endl; // Print statement
        jump(); // Execute jump code
    }
    if (_B == true) { // If button B is pressed
        //cout << "B button has been pressed" << std::endl; // Print statement
        _punch = true; // Set punch to true
    } else {
        _punch = false; // Otherwise punch is false
    }
    if (_X == true) { // If button X is pressed
        //cout << "X button has been pressed" << std::endl; // Print statement
        _kick = true; // Set kick to true
    } else {
        _kick = false; // Otherwise kick is false
    }
    gravity_force(); // Apply gravity force
    jerome_boundary(_distance); //Stop jerome from exiting screen
}

Action Jerome::get_jerome_hit(bool _B, bool _X)
{
    
    if (_B == true && (_collision.left || _collision.right)) {
        // Only register hit if Jerome is close enough to the enemy
        //cout << "PUNCH" << std::endl; // Print statement
        _a = PUNCH; // Set Action _a
    } else if (_X == true && (_collision.left || _collision.right)) {
        // Only register hit if Jerome is close enough to the enemy
        //cout << "KICK" << std::endl; // Print statement
        _a = KICK; // Set Action _a
    } else {
        _a = NOTHING; // Set Action _a
    }
    return _a; // Return the action
}

void Jerome::jump()
{
    if (on_surface() == true) { // Only jump if jerome is on surface (ground or top of enemy)
        _velocity.y = 12; // Give Jerome vertical velocity
        _pos.y += _velocity.y; // Set vertical position based on velocity
    }
}

void Jerome::jerome_boundary(Vector2D _distance)
{
    if (_pos.x > 71) {
        _pos.x = 71; // If at the right edge of the screen, stop moving
    }
    if (_pos.x < 0 ) {
        _pos.x = 0; // if at the left edge of the screen stop moving
    }
    if (_pos.y > 35) { // Stop jerome from leaving screen (bottom)
        _pos.y = 35;
    }
    if (_pos.y < 0) { // Stop jerome from leaving screen (top)
        _pos.y = 0;
    }
    if (_distance.x < 13 && _distance.x >= 0 && _distance.y >= -12) {
        //if (__collision.left == true) {
        //_pos.x = _distance.x - _pos.x - 13;
        _velocity.x = 0;
    }
    if (_distance.x > -13 && _distance.x <= 0 && _distance.y >= -12) {
        //_pos.x = _distance.x - _pos.x + 13;
        _velocity.x = 0;
    }

}

void Jerome::gravity_force()
{
    // NOTES: //
    // Makes Jerome fall back to ground if in air
    // When not on a surface - (bool on_surface() == false) - this function 
    // decreases Jeromes vertical velocity making him fall back to ground.
    // Vertical velocity is set to zero when on a surface.
    ////
    
    if (on_surface() == false) {
        _gravity = -3; // Set gravity variable
        _velocity.y += _gravity; // Change vertical velocity depending on gravity
        _pos.y += _velocity.y;  // Change vertical position depending on vertical
                                // Velocity
        if (_velocity.y < -40) { // If vertical velocity is too large
            _velocity.y = -40; // Stop vertical velocity decreasing (Terminal velocity)

        } else { // Else on surface
            _velocity.y = 0; // Set vertical velocity to 0
        }
    }
}

bool Jerome::on_surface()
{
    // NOTES: //
    // This function checks if Jerome is on surface (floor or top of enemy)
    // It the Jerome's y position to see if on the ground
    // Checks the x and y distance coordinates to see if Jerome is on top of the enemy. 
    ////
    
    //cout << "Height above ground = " << _pos.y << std::endl;
    if (_pos.y == 0) { // If on the ground
        //cout << "ON SURFACE (GROUND)" << std::endl;
        return true; // return boolean value TRUE
    }
    if (_collision.above == true) {
        //cout << "ON SURFACE (ENEMY)" << std::endl;
        return true; // return boolean value TRUE
    } else {
        //cout << "IN AIR" << std::endl;
        return false; // return boolean value FALSE
    }
}

bool Jerome::collision_detect(Vector2D _distance)
{
    // NOTES: //
    // Detects if Jerome sprite has collided with the enemy on the left, right 
    // or top sides.
    // If a horizontal collision is detected between Jerome and the Enemy, the
    // function sets the boolean boolean values accordingly
    ////

    if (_distance.x >= -13 && _distance.x <= 0 && _distance.y >= -11) {
        // Enemy touching right side of Jerome
        _collision.right = true;
        //cout <<  "Enemy touching RIGHT SIDE" << std::endl;
        //cout << "Distancepos.x = " << _distance.x << std::endl;
    } else {
        _collision.right = false;
    }
    
    if (_distance.x <= 13 && _distance.x >= 0 && _distance.y >= -11) {
        // Enemy touching left side of Jerome
        _collision.left = true;
        //cout <<  "Enemy touching LEFT SIDE" << std::endl;
        //cout << "Distancepos.x = " << _distance.x << std::endl;
    } else {
        _collision.left = false;
    }
    
    if (_distance.x <= 10 && _distance.x >= -10 && _distance.y >= -12) {
        _collision.above = true;
        // Jerome on top of enemy
        //cout <<  "COLLISION FROM ABOVE" << std::endl;
        //cout << "Distancepos.x = " << _distance.x << std::endl;
    } else {
        _collision.above = false;
    }
    
    if ((_distance.x >= -13 && _distance.x <= 13) && _distance.y >= -13) { // if closer than width of sprite AND closer than height of sprite
        // If touching on any side
        //cout << "Collision Detected" << std::endl;
        return true;
    } else {
        return false;
    }
}

Vector2D Jerome::get_jerome_pos()
{
    return _pos;
}

void Jerome::init(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
}