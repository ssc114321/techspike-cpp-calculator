#include "calculator.h"

#include <cmath>
#include <sstream>

bool evaluateExpression(const std::string &expression, double &result)
{
    std::istringstream input(expression);

    double left = 0.0;
    double right = 0.0;
    char operation = '\0';

    // Read both operands and the operator.
    if (!(input >> left >> operation >> right))
    {
        return false;
    }

    // Skip trailing whitespace and reject any remaining input.
    input >> std::ws;
    if (!input.eof())
    {
        return false;
    }

    // Calculate according to the operator.
    double value = 0.0;

    switch (operation)
    {
    case '+':
        value = left + right;
        break;

    case '-':
        value = left - right;
        break;

    case '*':
        value = left * right;
        break;

    case '/':
        if (right == 0.0)
        {
            return false;
        }
        value = left / right;
        break;

    default:
        return false;
    }
    // Reject non-finite results.
    if (!std::isfinite(value))
    {
        return false;
    }

    // Assign the output only after all checks succeed.
    result = value;
    return true;
}