#pragma once

#include "tokenizer.h"

#include <cstddef>
#include <vector>

// Read and evaluate a sequence of tokens.
class Parser
{
public:
    explicit Parser(const std::vector<Token> &inputTokens);

    CalculationError parse(double &result);

private:
    const Token &current() const;
    void advance();

    const std::vector<Token> &tokens;
    std::size_t position = 0;

    CalculationError parseFactor(double &result);
    CalculationError parseTerm(double &result);
    CalculationError parseExpression(double &result);
};