/**
 * Test program to expression evaluator.
 */

#include <cassert>
#include <iostream>

#include "expression_evaluator.h"

/**
 * Test valid input
 */
void TestValidExpression(const std::string &expression, double expected) {
  try {
    double result = ExpressionEvaluator::Evaluate(expression);
    // Allow for small floating point errors
    assert(std::abs(result - expected) < 1e-9 && "Wrong calculation result");
    std::cout << "PASS: " << expression << " = " << result << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "FAIL: " << expression << " threw exception: " << e.what()
              << std::endl;
    assert(false);
  }
}

/**
 * Helper function for invalid input
 */
void TestInvalidExpression(const std::string &expression) {
  try {
    ExpressionEvaluator::Evaluate(expression);
    std::cerr << "FAIL: " << expression
              << " did not throw exception as expected." << std::endl;
    assert(false);
  } catch (const std::invalid_argument &e) {
    std::cout << "PASS: " << expression
              << " threw expected exception: " << e.what() << std::endl;
  } catch (...) {
    std::cerr << "FAIL: " << expression << " threw unexpected exception."
              << std::endl;
    assert(false);
  }
}

int main() {
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
  TestValidExpression("0", 0);
  TestValidExpression("-1 + 1", 0);
  TestValidExpression("-(-2 + 1)", 1);
  TestValidExpression("0.1 + 0.2", 0.3);
  TestValidExpression("(3.5 + 4.5) * 2", 16.0);
  TestValidExpression("((1+2)*3)-(4/2)", 7.0);
  TestValidExpression("1.0e2", 100);
  TestValidExpression("1.0e2 + 2.0e1", 120);
  TestValidExpression("1e3 - 5e2", 500);
  TestValidExpression("2e3 * 3e-2", 60);
  TestValidExpression("1e2 / 2e-2", 5000);
  TestValidExpression("1.23e3 + 4.56e2", 1686);
  TestValidExpression("(1e2 + 2e1) * 3e0", 360);
  TestValidExpression("1e-3 + 1e-4", 0.0011);
  TestValidExpression("-1e3 + 2e3", 1000);
  TestValidExpression("1.0e2 / (2.5e1 + 7.5e1)", 1);

  // Test invalid inputs
  TestInvalidExpression("1++1");          // Continuation operators
  TestInvalidExpression("1-");            // Incomplete expression
  TestInvalidExpression("(1+2");          // Missing closing bracket
  TestInvalidExpression("1+2)");          // Missing left bracket
  TestInvalidExpression("1 + (2 + )");    // Emppty bracket
  TestInvalidExpression("1 / 0");         // Divide by zero
  TestInvalidExpression("abc + 1");       // Invalid charctors
  TestInvalidExpression("1.2.3 + 1");     // Invalid decimal points
  TestInvalidExpression("1 + * 2");       // Invalid operator combination
  TestInvalidExpression("1 + (2 * 3))");  // Extra closing bracket
  TestInvalidExpression("1.");            // No digit after '.'
  TestInvalidExpression("()");            // Empty expression
  TestInvalidExpression("1 / (2 - 2)");   // Divide by 0 in parentheses
  TestInvalidExpression("2 ** 3");        // Unsupported operator
  TestInvalidExpression("1 + .2.3");      // Wrong decimal point
  TestInvalidExpression("1.0ee2");        // Double `e`
  TestInvalidExpression("e2 + 1");        // Lack base number
  TestInvalidExpression("1e");            // Lack exponent number
  TestInvalidExpression("1.0e2.3");       // Invalid exponent defimal number
  TestInvalidExpression("1e+2e2");        // Nested exponent number
  TestInvalidExpression("1.0e-+2");       // Invalid operators
  TestInvalidExpression("1.0e--2");       // Continuous minus

  std::cout << "All tests passed!" << std::endl;
  return 0;
}