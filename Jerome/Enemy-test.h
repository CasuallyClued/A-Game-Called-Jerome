#ifndef ENEMY_TEST_H
#define ENEMY_TEST_H

/** Enemy Testing
* @brief Test to make sure Enemy movement functions operate correctly
* @returns True if test passed, false if failed
* @date May 2019
* @author Kamal Gamir - Shahin, University of Leeds
*/
bool test_enemy_movement()
{
    // CREATE ENEMY OBJECT
    Enemy enemy;
    enemy.init(71,0); // Set enemy position (MUTATOR)
    
    Vector2D enemy_pos_check = enemy.get_enemy_pos(); // Get enemy position (ACCESSOR)
    
    bool success_flag = true; // Initialise success flag bool to true
    if (enemy_pos_check.x != 71 || enemy_pos_check.y != 0) { //If any tests failed
        success_flag = false; // Set flag to false
    }
    return success_flag; // Return if test passed or not
}
#endif