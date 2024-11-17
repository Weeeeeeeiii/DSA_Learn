/**
 * Main program to input mathmatical expression.
 * Call EvaluateExpression to calculate the result of expression, then print it.
 */

#include "expression_evaluator.h"
#include <iostream>
#include <string>

int main()
{
    std::cout << "Please enter expression with only 4 fundamental rules:\n";
    std::string expression{};
    std::getline(std::cin >> std::ws, expression);
    std::cout << EvaluateExpression(expression);
    
    return 0;
}