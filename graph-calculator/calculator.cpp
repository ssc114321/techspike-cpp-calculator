#include "calculator.h"

#include <cmath>
#include <sstream>

bool evaluateAddition(const std::string &expression, double &result)
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

    // Accept only addition.
    if (operation != '+')
    {
        return false;
    }

    // Skip trailing whitespace and reject any remaining input.
    input >> std::ws;
    if (!input.eof())
    {
        return false;
    }

    // Calculate the sum and reject non-finite results.
    const double sum = left + right;
    if (!std::isfinite(sum))
    {
        return false;
    }

    // Assign the output only after all checks succeed.
    result = sum;
    return true;
}