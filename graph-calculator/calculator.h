#pragma once

#include <string>

// Describe the outcome of an evaluation.
enum class CalculationError
{
    None,
    InvalidExpression,
    DivisionByZero,
    NonFiniteResult
};

// Evaluate an expression and return its error status.
CalculationError evaluateExpression(
    const std::string &expression,
    double &result);