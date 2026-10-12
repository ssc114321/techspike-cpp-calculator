#include "calculator.h"

#include <cmath>
#include <sstream>

CalculationError evaluateExpression(const std::string &expression, double &result)
{
    std::istringstream input(expression);

    double left = 0.0;
    double right = 0.0;
    char operation = '\0';

    // Read both operands and the operator.
    if (!(input >> left >> operation >> right))
    {
        return CalculationError::InvalidExpression;
    }

    // Skip trailing whitespace and reject any remaining input.
    input >> std::ws;
    if (!input.eof())
    {
        return CalculationError::InvalidExpression;
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
            return CalculationError::DivisionByZero;
        }
        value = left / right;
        break;

    default:
        return CalculationError::InvalidExpression;
    }
    // Reject non-finite results.
    if (!std::isfinite(value))
    {
        return CalculationError::NonFiniteResult;
    }

    // Assign the output only after all checks succeed.
    result = value;
    return CalculationError::None;
}