#ifndef EXPRESSION_EVALUATOR_H_
#define EXPRESSION_EVALUATOR_H_

#include <cassert>
#include <cctype>
#include <stdexcept>
#include <string>

#include "infix_to_postfix.h"

/**
 * Calculate the expression of reverse Polish notation (RPN).
 * expression is original infix notaion, EvaluateExpression include convertion
 * from infix notation to RPN.
 */
double EvaluateExpression(const std::string &expression) {
  // Convert infix expression to RPN queue
  auto rpn_queue = InfixToPostfix(expression);

  // Values stack to store calculation result
  std::stack<double> values;

  // Pop tokens out of RPN queue, then push into values stack to calcutate
  while (!rpn_queue.empty()) {
    const std::string token = rpn_queue.front();
    rpn_queue.pop();

    if (std::isdigit(token[0])) {
      // token is a digit
      values.push(std::stod(token));
      continue;
    }

    // token is an operator
    // Check if values is valid
    if (values.size() < 2) {
      throw std::invalid_argument("Too many operations");
    }

    // If values is valid, pop and calculate the result of the top 2
    // value, then push result back to stack
    double b = values.top();
    values.pop();
    double a = values.top();
    values.pop();

    switch (token[0]) {
      case '+':
        values.push(a + b);
        break;
      case '-':
        values.push(a - b);
        break;
      case '*':
        values.push(a * b);
        break;
      case '/':
        if (b == 0) throw std::invalid_argument("Division by zero");
        values.push(a / b);
        break;
      default:
        assert(false &&
               "Charactor not operators and parentheses be passed into "
               "expressing_evaluator.h");
    }
  }

  if (values.size() != 1) {
    throw std::invalid_argument(
        "Operation missing, the multiplication sign cannot be omitted");
  }
  return values.top();
}

#endif  // EXPRESSION_EVALUATOR_H_