#pragma once

#include "calculator.h"

#include <string>
#include <vector>

// Identify the kind of token.
enum class TokenType
{
    Number,
    Plus,
    Minus,
    Multiply,
    Divide,
    LeftParen,
    RightParen,
    End
};

// Store a token and its numeric value.
struct Token
{
    TokenType type;
    double value = 0.0;
};

// Convert an expression into tokens.
CalculationError tokenize(
    const std::string &expression,
    std::vector<Token> &tokens);