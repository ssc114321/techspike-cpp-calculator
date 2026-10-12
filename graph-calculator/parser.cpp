#include "parser.h"
#include <cmath>

// Keep a reference to the input tokens.
Parser::Parser(const std::vector<Token> &inputTokens)
    : tokens(inputTokens)
{
}

// Return the current token without advancing.
const Token &Parser::current() const
{
    // TODO: Return the token at position.
    return tokens[position];
}

// Advance unless the current token marks the end.
void Parser::advance()
{
    // TODO: Increment position if the current token is not End.
    if (current().type != TokenType::End)
    {
        ++position;
    }
}

// Parse a complete expression.
CalculationError Parser::parse(double &result)
{
    // TODO: Reject an empty token list or a missing End token.
    if (tokens.empty() || tokens.back().type != TokenType::End)
    {
        return CalculationError::InvalidExpression;
    }
    double value = 0.0;
    const auto error = parseExpression(value);

    if (error != CalculationError::None)
    {
        return error;
    }

    // TODO: Reject any remaining token other than End.
    if (current().type != TokenType::End)
    {
        return CalculationError::InvalidExpression;
    }
    // TODO: Assign result and return None.
    result = value;
    return CalculationError::None;
}

// Read one numeric factor.
CalculationError Parser::parseFactor(double &result)
{
    // Handle a unary sign.
    if (current().type == TokenType::Plus ||
        current().type == TokenType::Minus)
    {
        const auto sign = current().type;
        advance();

        double value = 0.0;
        const auto error = parseFactor(value);

        if (error != CalculationError::None)
        {
            return error;
        }

        // TODO: Negate value for Minus, otherwise keep value.
        if (sign == TokenType::Minus)
        {
            value = -value;
        }
        // TODO: Assign result and return None.
        result = value;
        return CalculationError::None;
    }
    // Handle a parenthesized expression.
    if (current().type == TokenType::LeftParen)
    {
        advance();

        double value = 0.0;
        const auto error = parseExpression(value);

        if (error != CalculationError::None)
        {
            return error;
        }

        // TODO: Require a RightParen token.
        if (current().type != TokenType::RightParen)
        {
            return CalculationError::InvalidExpression;
        }
        // TODO: Advance past the closing parenthesis.
        advance();
        // TODO: Assign result and return None.
        result = value;
        return CalculationError::None;
    }
    // Handle Number
    if (current().type != TokenType::Number)
    {
        return CalculationError::InvalidExpression;
    }

    result = current().value;
    advance();
    return CalculationError::None;
}

// Evaluate a sequence of multiplications and divisions.
CalculationError Parser::parseTerm(double &result)
{
    double value = 0.0;
    auto error = parseFactor(value);

    if (error != CalculationError::None)
    {
        return error;
    }

    while (current().type == TokenType::Multiply ||
           current().type == TokenType::Divide)
    {
        const auto operation = current().type;
        advance();

        double right = 0.0;

        // TODO: Read the right factor and propagate any error.
        error = parseFactor(right);
        if (error != CalculationError::None)
        {
            return error;
        }
        // TODO: Multiply or divide according to operation.
        if (operation == TokenType::Multiply)
        {
            value *= right;
        }
        // TODO: Reject division by zero.
        else
        {
            if (right == 0.0)
            {
                return CalculationError::DivisionByZero;
            }
            value /= right;
        }
        // TODO: Reject a non-finite value.
        if (!std::isfinite(value))
        {
            return CalculationError::NonFiniteResult;
        }
    }

    result = value;
    return CalculationError::None;
}

// Evaluate a sequence of additions and subtractions.
CalculationError Parser::parseExpression(double &result)
{
    double value = 0.0;
    auto error = parseTerm(value);

    if (error != CalculationError::None)
    {
        return error;
    }

    while (current().type == TokenType::Plus ||
           current().type == TokenType::Minus)
    {
        const auto operation = current().type;
        advance();

        double right = 0.0;

        // TODO: Read the right term and propagate any error.
        error = parseTerm(right);
        if (error != CalculationError::None)
        {
            return error;
        }
        // TODO: Add or subtract according to operation.
        if (operation == TokenType::Plus)
        {
            value += right;
        }
        else
        {
            value -= right;
        }
        // TODO: Reject a non-finite value.
        if (!std::isfinite(value))
        {
            return CalculationError::NonFiniteResult;
        }
    }

    result = value;
    return CalculationError::None;
}