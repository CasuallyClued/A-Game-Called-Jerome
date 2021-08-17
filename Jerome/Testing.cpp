#ifndef TESTING_H
#define TESTING_H

// INCLUDE RELEVANT HEADERS //
#include "Jerome-test.h"
#include "Enemy-test.h"
#include <iostream>

/**
 * @brief Runs all testing files for this program
 * @returns Integer number of how many tests failed
 */
int run_tests()
{
    int tests_failed = 0; // Initialise number of failed tests to 0
    // PERFORM ENEMY TEST
    cout << "Testing enemy movement" << std::endl;
    bool test_passed = test_enemy_movement(); // set bool variable to result of test

    // PRINT TEST RESULTS //
    if (test_passed) {
        cout << "PASSED" << std::endl << std::endl; // Print PASSED to terminal
    } else {
        cout << "FAILED" << std::endl << std::endl; // Print FAILED to terminal
        ++tests_failed; // Increment number of failures
    }

    // PERFORM JEROME TEST //
    cout << "Testing Jerome movement" << std::endl;
    test_passed = test_jerome_movement();
    // Print out the result of this test
    if (test_passed) {
        cout << "PASSED" << std::endl << std::endl;
    } else {
        cout << "FAILED" << std::endl << std::endl;
        ++tests_failed; // Increment number of failures
    }

    // PRINT TEST SUMMARY
    if (tests_failed == 1) {
        cout << tests_failed << " test FAILED" << std::endl;
    }
    if (tests_failed > 1) {
        cout << tests_failed << " tests FAILED" << std::endl;
    }
    if (tests_failed == 0) {
        printf("All tests passed!\n");
    }
    return tests_failed; // Return the number of tests that failed
}
#endif