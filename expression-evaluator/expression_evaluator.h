/**
 * Only include a class `ExpressionEvaluator` used to evaluate expression.
 * Allow `+ - * / ( )` and space.
 */

#ifndef EXPRESSION_EVALUATOR_H_
#define EXPRESSION_EVALUATOR_H_

#include <cassert>
#include <cctype>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>

/**
 * All menber function is static,and only `Evaluate` is public. 
 * Use `Evaluate` to calculate expression.
 * Only `[0-9]` and `+ - * / ( ) SPC` is valid charactor.
 */
class ExpressionEvaluator {
 public:
  /**
   * Convert expression string into postfix output tokens queue.
   * Then pop it out into result stack. Once a operator is pushed into stack,
   * perform the corresponding operation for the top 2 tokens.
   */
  static double Evaluate(const std::string &expression) {
    auto rpn_queue = InfixToPostfix(expression);
    std::stack<double> values;

    while (!rpn_queue.empty()) {
      const std::string token = rpn_queue.front();
      rpn_queue.pop();

      if (std::isdigit(token[0])) {
        values.push(std::stod(token));
        continue;
      }

      if (values.size() < 2) {
        throw std::invalid_argument("Too many operations");
      }
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

 private:
  /**
   * Get the precedence of operators.
   * `*`, `/` has greater precedence than `+`, `-` than `(`, `)`.
   */
  static int GetPrecedence(char opr) {
    if (opr == '+' || opr == '-') {
      return 1;
    }
    if (opr == '*' || opr == '/') {
      return 2;
    }
    return 0;
  }

  /**
   * Check if a charactor is an operator amoung 4 rules.
   */
  static bool IsOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
  }

  /**
   * Check if a charactor is a valid decimal point.
   */
  static bool IsValidDecimalPoint(char c, bool point_is_added,
                                  const std::string &buffer) {
    if (c != '.') {
      return false;
    }
    if (!buffer.length()) {
      throw std::invalid_argument("No digits before the decimal point");
    }

    if (!point_is_added) {
      return true;
    }
    throw std::invalid_argument("Mutiple decimal points exist");
  }

  /**
   * Use shungting-yard algorithm to translate infix expression to RPN.
   * Check the character in input string one by one. Push the digit together as
   * a token into output queue. Push the operators into stack, once the
   * precedence of the new operator that will be push into stack not greater
   * than the precedence of the top one in stack, pop the top operator and push
   * it into output queue until the above condition not satisfied.
   */
  static std::queue<std::string> InfixToPostfix(const std::string &infix) {
    std::stack<char> operators{};
    std::queue<std::string> output{};

    // buffer here is used to storage multiple digits and valid decimal point
    // as a token. Then push it into output queue.
    std::string buffer{};
    bool expect_negative_sign{true};
    bool point_is_added{false};

    for (char c : infix) {
      if (std::isspace(c)) {
        continue;
      }
      if (IsValidDecimalPoint(c, point_is_added, buffer)) {
        buffer += c;
        point_is_added = true;
        continue;
      }
      if (std::isdigit(c)) {
        buffer += c;
        expect_negative_sign = false;
        continue;
      }
      if (!buffer.empty()) {
        output.push(buffer);
        buffer.clear();
        point_is_added = false;
      }
      if (IsOperator(c)) {
        if (c == '-' && expect_negative_sign) {
          // Address negative sign by converting `-a` into `(0-a)`. So '-' must
          // be push into operator stack whatever the precedence of operator.
          output.push("0");
          operators.push('-');
        } else {
          while (!operators.empty() &&
                 GetPrecedence(operators.top()) >= GetPrecedence(c)) {
            output.push(std::string(1, operators.top()));
            operators.pop();
          }
          operators.push(c);
        }

        expect_negative_sign = true;
        continue;
      }
      if (c == '(') {
        operators.push(c);
        expect_negative_sign = true;
        continue;
      }
      if (c == ')') {
        while (!operators.empty() && operators.top() != '(') {
          output.push(std::string(1, operators.top()));
          operators.pop();
        }
        if (operators.empty()) {
          throw std::invalid_argument("Mismatched parentheses");
        }
        operators.pop();

        expect_negative_sign = false;
        continue;
      }

      throw std::invalid_argument(std::string("Invalid character: ") + c);
    }

    if (!buffer.empty()) {
      output.push(buffer);
    }
    while (!operators.empty()) {
      if (operators.top() == '(')
        throw std::invalid_argument("Mismatched parentheses");
      output.push(std::string(1, operators.top()));
      operators.pop();
    }

    return output;
  }
};

#endif  // EXPRESSION_EVALUATOR_H_