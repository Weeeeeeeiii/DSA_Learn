/**
 * Convert an infix expression to a postfix expression.
 */

#ifndef INFIX_TO_POSTFIX_
#define INFIX_TO_POSTFIX_

#include <string>
#include <stack>
#include <queue>
#include <cctype>
#include <stdexcept>

/**
 * Define the precedence of operators.
 */
unsigned char Precedence(char opr)
{
    if (opr == '+' || opr == '-')
        return 1;
    else if (opr == '*' || opr == '/')
        return 2;
    else
        return 0;
}
/**
 * Check if a charactor is an operator amoung 4 rules.
 */
bool IsOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

/**
 * Check if a charactor is an numeric, digit and '.' included.
 */
bool IsNumeric(char c)
{
    return std::isdigit(c) || c == '.';
}

/**
 * Use shungting-yard algorithm to translate infix expression to RPN.
 */
std::queue<std::string> InfixToPostfix(const std::string &infix)
{
    // Initailize operator stack, output queue
    std::stack<char> operators{};
    std::queue<std::string> output{};

    // buffer here is used to save multi-digit numbers
    std::string buffer{};

    // Check if it is a negative sign or substraction, expect negative symbol at
    // the beginning
    bool ExpectNegative{true};

    for (char c : infix)
    {
        // Ignore spaces
        if (std::isspace(c))
            continue;

        // Store multi-digit numbers
        if (IsNumeric(c))
        {
            buffer += c;

            // After a numeric, do not expect negative
            ExpectNegative = false;
        }
        else
        {
            // Push number in buffer into output queue
            if (!buffer.empty())
            {
                output.push(buffer);
                buffer.clear();
            }

            if (IsOperator(c))
            {
                if (c == '-' && ExpectNegative)
                {
                    // If it is negative sign, push 0 into output queue
                    output.push("0");

                    // Add '-' to stack whatever the precedence is, it's 
                    // necessary because we must ensure "-a" must be transformed
                    // into "0 a -" in RPN
                    operators.push(c);
                }
                else
                {
                    // Pop operator from stack out until precedence of c is
                    // greater, when '-' is substraction
                    while (!operators.empty() &&
                           Precedence(operators.top()) >= Precedence(c))
                    {
                        output.push(std::string(1, operators.top()));
                        operators.pop();
                    }
                    operators.push(c);
                }

                // Expect negative after operator
                ExpectNegative = true;
            }
            else if (c == '(')
            {
                operators.push(c);

                // Expect negative after '('
                ExpectNegative = true;
            }
            else if (c == ')')
            {
                // Pop all operators in parentheses
                while (!operators.empty() && operators.top() != '(')
                {
                    output.push(std::string(1, operators.top()));
                    operators.pop();
                }
                if (operators.empty())
                    throw std::invalid_argument("Mismatched parentheses");
                operators.pop();

                // Expect substraction after ')'
                ExpectNegative = false;
            }
            else
                throw std::invalid_argument(
                    std::string("Invalid character: ") + c
                );
        }
    }

    // Push remaining digits in buffer into output queue
    if (!buffer.empty())
        output.push(buffer);

    // Push remaining operators in stack into output queue
    while (!operators.empty())
    {
        if (operators.top() == '(')
            throw std::invalid_argument("Mismatched parentheses");
        output.push(std::string(1, operators.top()));
        operators.pop();
    }

    return output;
}

#endif // INFIX_TO_POSTFIX_H_