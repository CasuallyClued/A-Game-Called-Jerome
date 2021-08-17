#ifndef JEROME_TEST_H
#define JEROME_TEST_H

/** Jerome Testing
* @brief Test to make sure Jerome movement functions operate correctly
* @returns True if test passed, false if failed
* @date May 2019
* @author Kamal Gamir - Shahin, University of Leeds
*/

bool test_jerome_movement()
{
    // CREATE JEROME OBJECT //
    Jerome jerome;
    jerome.init(30,40); // Set Jerome position (MUTATOR)
    
    Vector2D jerome_pos_check = jerome.get_jerome_pos(); // Get Jerome position (ACCESSOR)
    
    bool success_flag = true; // Initialise success flag bool to true
    if (jerome_pos_check.x != 30 || jerome_pos_check.y != 40) { //If any tests failed
        success_flag = false; // Set flag to false
    }
    return success_flag; // Return if test passed or not
}
#endif