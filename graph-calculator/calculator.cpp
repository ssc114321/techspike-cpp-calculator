#include "calculator.h"
#include "parser.h"
#include "tokenizer.h"
#include <vector>

CalculationError evaluateExpression(
    const std::string &expression,
    double &result)
{
    std::vector<Token> tokens;
    const auto error = tokenize(expression, tokens);

    if (error != CalculationError::None)
    {
        return error;
    }

    Parser parser(tokens);
    return parser.parse(result);
}