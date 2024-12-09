/**
 * Main program to input mathmatical expression.
 * Call EvaluateExpression to calculate the result of expression, then print it.
 */

#include <iostream>
#include <stdexcept>
#include <string>

#include "expression_evaluator.h"

int main() {
  std::cout << "Please enter the four arithmetic expression.\n";
  std::cout << "Scientific notation is supported.\n";
  std::cout << "Valid charactors: [0-9] + - * / ( ) e E\n";
  std::cout << "For example:\nInput: 1e2 + -2.1e0\nOutput: 97.9\nInput: ";
  std::string expression{};
  std::getline(std::cin >> std::ws, expression);
  try {
    std::cout << "Result: " << ExpressionEvaluator::Evaluate(expression)
              << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Fatal: " << e.what() << std::endl;
  }

  return 0;
}