/**
 * Main program to input mathmatical expression.
 * Call EvaluateExpression to calculate the result of expression, then print it.
 */

#include "expression_evaluator.h"
#include <iostream>
#include <string>

int main()
{
    std::cout << "Please enter expression with only 4 fundamental rules.\n";
    std::cout << "Only accept valid symbols like [0-9] and '+', '-', '*', '/',";
    std::cout << " '(', ')'.\n";
    std::cout << "Note: The brackets must be paired.\n";
    std::string expression{};
    std::getline(std::cin >> std::ws, expression);

    try
    {
        std::cout << EvaluateExpression(expression) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Fatal: " << e.what() << std::endl;
    }

    return 0;
}