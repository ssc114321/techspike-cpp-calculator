#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QKeySequence>
#include <QShortcut>
#include "calculator.h"
#include <QLabel>

int main(int argc, char *argv[])
{
    // Create the QApplication instance.
    QApplication app(argc, argv);

    // Create the main window.
    QWidget window;

    // Set the window title.
    window.setWindowTitle("Graph Calculator");

    // Set the window size to 800 by 600 pixels.
    window.resize(800, 600);

    // Create a read-only display initialized to "0".
    QLineEdit display(&window);
    display.setText("0");
    display.setReadOnly(true);

    // Create an error message label.
    QLabel errorLabel(&window);

    // Create the digit buttons.
    QPushButton button0("0", &window);
    QPushButton button1("1", &window);
    QPushButton button2("2", &window);
    QPushButton button3("3", &window);
    QPushButton button4("4", &window);
    QPushButton button5("5", &window);
    QPushButton button6("6", &window);
    QPushButton button7("7", &window);
    QPushButton button8("8", &window);
    QPushButton button9("9", &window);

    // Create action buttons
    QPushButton clearButton("C", &window);
    QPushButton deleteButton("DEL", &window);
    QPushButton plusButton("+", &window);
    QPushButton minusButton("-", &window);
    QPushButton multiplyButton("*", &window);
    QPushButton divideButton("/", &window);
    QPushButton equlsButton("=", &window);
    QPushButton decimalButton(".", &window);
    QPushButton leftParenButton("(", &window);
    QPushButton rightParenButton(")", &window);

    // Arrange the display and button vertically.
    QVBoxLayout layout(&window);
    layout.addWidget(&errorLabel);
    layout.addWidget(&display);

    // Add a grid layout for the keypad.
    QGridLayout keypad;
    layout.addLayout(&keypad);

    // Place the buttons in the grid.
    keypad.addWidget(&button0, 3, 1);
    keypad.addWidget(&button1, 2, 0);
    keypad.addWidget(&button2, 2, 1);
    keypad.addWidget(&button3, 2, 2);
    keypad.addWidget(&button4, 1, 0);
    keypad.addWidget(&button5, 1, 1);
    keypad.addWidget(&button6, 1, 2);
    keypad.addWidget(&button7, 0, 0);
    keypad.addWidget(&button8, 0, 1);
    keypad.addWidget(&button9, 0, 2);

    keypad.addWidget(&clearButton, 3, 0);
    keypad.addWidget(&deleteButton, 3, 2);
    keypad.addWidget(&plusButton, 0, 3);
    keypad.addWidget(&minusButton, 1, 3);
    keypad.addWidget(&multiplyButton, 2, 3);
    keypad.addWidget(&divideButton, 3, 3);
    keypad.addWidget(&equlsButton, 4, 3);
    keypad.addWidget(&decimalButton, 4, 1);
    keypad.addWidget(&leftParenButton, 4, 0);
    keypad.addWidget(&rightParenButton, 4, 2);

    // Track whether the display contains a calculation result.
    bool resultShown = false;

    // Define the shared parenthesis input action.
    auto appendParenthesis = [&display, &resultShown](const QString &parenthesis)
    {
        QString current = display.text();

        // TODO: For '(' at the initial "0" or after a result, start with "(".
        if (parenthesis == "(" && (current == "0" || resultShown))
        {
            display.setText("(");
            resultShown = false;
            return;
        }
        // TODO: Ignore ')' when a result is shown.
        if (parenthesis == ")" && resultShown)
        {
            return;
        }
        // TODO: Otherwise, append parenthesis.
        current += parenthesis;
        // TODO: Update the display and set resultShown to false.
        display.setText(current);
        resultShown = false;
    };

    // Define the decimal input action.
    auto appendDecimal = [&display, &resultShown]()
    {
        QString current = display.text();

        // TODO: If a result is shown, start a new input with "0." and return.
        if (resultShown)
        {
            display.setText("0.");
            resultShown = false;
            return;
        }

        // A decimal point cannot follow a closing parenthesis.
        if (current.endsWith(')'))
        {
            return;
        }

        // Find the start of the current operand.
        qsizetype numberStart = 0;

        for (qsizetype i = 0; i < current.size(); ++i)
        {
            const QChar character = current.at(i);

            // Start a new operand after an opening parenthesis.
            if (character == '(')
            {
                numberStart = i + 1;
                continue;
            }

            // Avoid accessing a previous character at the start.
            if (i == 0)
            {
                continue;
            }

            const QChar previous = current.at(i - 1);

            const bool isOperator =
                character == '+' || character == '-' ||
                character == '*' || character == '/';

            const bool isExponentSign =
                (character == '+' || character == '-') &&
                (previous == 'e' || previous == 'E');

            if (isOperator && !isExponentSign)
            {
                numberStart = i + 1;
            }
        }

        QString number = current.mid(numberStart);
        // TODO: Ignore the click if the operand already contains a decimal point.
        if (number.contains('.') || number.contains('e', Qt::CaseInsensitive))
        {
            return;
        }
        // TODO: Append "0." for an empty operand, otherwise append ".".
        if (number.isEmpty() || number == "-" || number == "+")
        {
            current += "0.";
        }
        else
        {
            current += ".";
        }
        // TODO: Update the display.
        display.setText(current);
    };

    // Define the calculation action.
    auto calculate = [&display, &resultShown, &errorLabel]()
    {
        // Keep the current result when calculation is requested again.
        if (resultShown)
        {
            return;
        }

        double result = 0.0;
        const auto error = evaluateExpression(
            display.text().toStdString(), result);

        if (error != CalculationError::None)
        {
            switch (error)
            {
            case CalculationError::InvalidExpression:
                errorLabel.setText("Check the expression.");
                break;

            case CalculationError::DivisionByZero:
                errorLabel.setText("Cannot divide by zero.");
                break;

            case CalculationError::NonFiniteResult:
                errorLabel.setText("Result is out of range.");
                break;

            case CalculationError::None:
                break;
            }

            return;
        }

        // TODO: Clear the error, display the result, and update resultShown.
        errorLabel.clear();
        display.setText(QString::number(result, 'g', 15));
        resultShown = true;
    };

    // Append an operator and continue editing the expression.
    auto appendOperator = [&display, &resultShown](const QString &operation)
    {
        display.setText(display.text() + operation);
        resultShown = false;
    };

    // Define the clear action.
    auto clearInput = [&display, &resultShown, &errorLabel]()
    {
        errorLabel.clear();
        display.setText("0");
        resultShown = false;
    };

    // Define the delete action.
    auto deleteLast = [&display, &resultShown]()
    {
        QString current = display.text();
        if (current.isEmpty() || current.size() == 1)
        {
            current = "0";
        }
        else
        {
            current.chop(1);
        }
        display.setText(current);
        resultShown = false;
    };

    // Define the shared digit input action.
    auto appendDigit = [&display, &resultShown](const QString &digit)
    {
        QString current = display.text();
        if (current == "0" || resultShown)
        {
            current = digit;
            resultShown = false;
        }
        else
        {
            current += digit;
        }
        display.setText(current);
    };

    // Connect the button's clicked signal to update the display.
    QObject::connect(
        &button0,
        &QPushButton::clicked,
        &window,
        [&appendDigit]()
        {
            appendDigit("0");
        });

    QObject::connect(
        &button1,
        &QPushButton::clicked,
        &window,
        [&appendDigit]()
        {
            appendDigit("1");
        });

    QObject::connect(
        &button2,
        &QPushButton::clicked,
        &window,
        [&appendDigit]()
        {
            appendDigit("2");
        });

    QObject::connect(
        &button3,
        &QPushButton::clicked,
        &window,
        [&appendDigit]()
        {
            appendDigit("3");
        });

    QObject::connect(
        &button4,
        &QPushButton::clicked,
        &window,
        [&appendDigit]()
        {
            appendDigit("4");
        });

    QObject::connect(
        &button5,
        &QPushButton::clicked,
        &window,
        [&appendDigit]()
        {
            appendDigit("5");
        });

    QObject::connect(
        &button6,
        &QPushButton::clicked,
        &window,
        [&appendDigit]()
        {
            appendDigit("6");
        });

    QObject::connect(
        &button7,
        &QPushButton::clicked,
        &window,
        [&appendDigit]()
        {
            appendDigit("7");
        });

    QObject::connect(
        &button8,
        &QPushButton::clicked,
        &window,
        [&appendDigit]()
        {
            appendDigit("8");
        });

    QObject::connect(
        &button9,
        &QPushButton::clicked,
        &window,
        [&appendDigit]()
        {
            appendDigit("9");
        });

    QObject::connect(
        &clearButton,
        &QPushButton::clicked,
        &window,
        clearInput);

    QObject::connect(
        &deleteButton,
        &QPushButton::clicked,
        &window,
        deleteLast);

    QObject::connect(
        &plusButton,
        &QPushButton::clicked,
        &window,
        [&appendOperator]()
        {
            appendOperator("+");
        });

    QObject::connect(
        &minusButton,
        &QPushButton::clicked,
        &window,
        [&appendOperator]()
        {
            appendOperator("-");
        });

    QObject::connect(
        &multiplyButton,
        &QPushButton::clicked,
        &window,
        [&appendOperator]()
        {
            appendOperator("*");
        });

    QObject::connect(
        &divideButton,
        &QPushButton::clicked,
        &window,
        [&appendOperator]()
        {
            appendOperator("/");
        });

    QObject::connect(
        &equlsButton,
        &QPushButton::clicked,
        &window,
        [&calculate]()
        {
            calculate();
        });

    QObject::connect(
        &decimalButton,
        &QPushButton::clicked,
        &window,
        [&appendDecimal]()
        {
            appendDecimal();
        });

    // Clear the error when the displayed text changes.
    QObject::connect(
        &display,
        &QLineEdit::textChanged,
        &errorLabel,
        &QLabel::clear);

    QObject::connect(
        &leftParenButton,
        &QPushButton::clicked,
        &window,
        [&appendParenthesis]()
        {
            appendParenthesis("(");
        });

    QObject::connect(
        &rightParenButton,
        &QPushButton::clicked,
        &window,
        [&appendParenthesis]()
        {
            appendParenthesis(")");
        });

    // Create the clear shortcut.
    QShortcut clearShortcut(QKeySequence(Qt::Key_Escape), &window);

    // Create shortcuts for both Enter keys.
    QShortcut calculateShortcut(&window);
    calculateShortcut.setKeys({QKeySequence(Qt::Key_Return),
                               QKeySequence(Qt::Key_Enter)});

    // Connect Escape to the existing clear action.
    QObject::connect(
        &clearShortcut,
        &QShortcut::activated,
        &window,
        clearInput);

    // Create the delete shortcut.
    QShortcut deleteShortcut(QKeySequence(Qt::Key_Backspace), &window);

    // Connect the shortcut to the existing delete action.
    QObject::connect(
        &deleteShortcut,
        &QShortcut::activated,
        &window,
        deleteLast);

    // Connect Enter to the calculation action.
    QObject::connect(
        &calculateShortcut,
        &QShortcut::activated,
        &window,
        calculate);

    // Show the window.
    window.show();

    // Run the event loop and return its exit code.
    return (app.exec());
}
