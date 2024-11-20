/**
 * Test program to expression evaluator.
 */

#include "expression_evaluator.h"
#include <iostream>
#include <cassert>

/**
 * Test valid input
 */
void TestValidExpression(const std::string &expression, double expected)
{
    try
    {
        double result = EvaluateExpression(expression);
        // Allow for small floating point errors
        assert(std::abs(result - expected) < 1e-9);
        std::cout << "PASS: " << expression << " = " << result << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "FAIL: " << expression << " threw exception: " << e.what()
        << std::endl;
        // Make sure program stops at test failure
        assert(false);
    }
}

/**
 * Helper function for invalid input
 */
void TestInvalidExpression(const std::string &expression)
{
    try
    {
        // This call should not succeed
        EvaluateExpression(expression);
        std::cerr << "FAIL: " << expression << 
        " did not throw exception as expected." << std::endl;
        // Make sure program stops at test failure
        assert(false);
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "PASS: " << expression << " threw expected exception: "
        << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "FAIL: " << expression << " threw unexpected exception."
        << std::endl;
        assert(false);
    }
}

int main()
{
    // Test valid inputs
    TestValidExpression("1+2", 3);
    TestValidExpression("1 + 2 * 3", 7);
    TestValidExpression("1.5 + 2.5", 4.0);
    TestValidExpression("10 / 2", 5.0);
    TestValidExpression("1 + -2", -1.0);
    TestValidExpression("-3 * -2.5", 7.5);
    TestValidExpression("1 + -(2 + 3)", -4.0);
    TestValidExpression("-(1 + 2) * -3", 9.0);
    TestValidExpression("(1 + 2) * (3 + 4)", 21.0);
    TestValidExpression("10 / (2 + 3)", 2.0);

    // Test invalid inputs
    TestInvalidExpression("1++1");       // Continuation operators
    TestInvalidExpression("1+");         // Incomplete expression
    TestInvalidExpression("(1+2");       // Missing closing bracket
    TestInvalidExpression("1+2)");       // Missing left bracket
    TestInvalidExpression("1 + (2 + )"); // Emppty bracket
    TestInvalidExpression("1 / 0");      // Divide by zero
    TestInvalidExpression("abc + 1");    // Invalid charctors
    TestInvalidExpression("1.2.3 + 1");  // Invalid decimal points

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
