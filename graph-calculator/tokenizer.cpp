#include "tokenizer.h"

#include <cctype>
#include <cmath>
#include <stdexcept>

CalculationError tokenize(
    const std::string &expression,
    std::vector<Token> &tokens)
{
    std::vector<Token> parsed;
    std::size_t position = 0;

    while (position < expression.size())
    {
        const char character = expression[position];

        // TODO: Skip whitespace.
        if (std::isspace(static_cast<unsigned char>(character)))
        {
            ++position;
            continue;
        }
        // TODO: Recognize operators and parentheses.
        switch (character)
        {
        case '+':
            parsed.push_back({TokenType::Plus});
            ++position;
            continue;
        case '-':
            parsed.push_back({TokenType::Minus});
            ++position;
            continue;
        case '*':
            parsed.push_back({TokenType::Multiply});
            ++position;
            continue;
        case '/':
            parsed.push_back({TokenType::Divide});
            ++position;
            continue;
        case '(':
            parsed.push_back({TokenType::LeftParen});
            ++position;
            continue;
        case ')':
            parsed.push_back({TokenType::RightParen});
            ++position;
            continue;
        }
        // TODO: Read a number when the character is a digit or '.'.
        if (std::isdigit(static_cast<unsigned char>(character)) || character == '.')
        {
            try
            {
                // TODO: Read, validate, and store the number.
                std::size_t consumed = 0;
                double value = std::stod(expression.substr(position), &consumed);
                // Reject non-finite numeric values.
                if (!std::isfinite(value))
                {
                    return CalculationError::NonFiniteResult;
                }
                parsed.push_back({TokenType::Number, value});
                position += consumed;
                continue;
            }
            catch (const std::invalid_argument &)
            {
                return CalculationError::InvalidExpression;
            }
            catch (const std::out_of_range &)
            {
                return CalculationError::NonFiniteResult;
            }
        }
        // TODO: Reject any unrecognized character.
        return CalculationError::InvalidExpression;
    }

    // Mark the end of the expression.
    parsed.push_back({TokenType::End});

    // Replace the output only after tokenization succeeds.
    tokens = parsed;
    return CalculationError::None;
}