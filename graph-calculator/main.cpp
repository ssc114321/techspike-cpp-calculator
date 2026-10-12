#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QKeySequence>
#include <QShortcut>
#include "calculator.h"

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
    QPushButton equlsButton("=", &window);

    // Arrange the display and button vertically.
    QVBoxLayout layout(&window);
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
    keypad.addWidget(&plusButton, 4, 0);
    keypad.addWidget(&equlsButton, 4, 2);

    // Track whether the display contains a calculation result.
    bool resultShown = false;

    // Define the calculation action.
    auto calculate = [&display, &resultShown]()
    {
        double result = 0.0;

        if (!evaluateAddition(display.text().toStdString(), result))
        {
            return;
        }

        display.setText(QString::number(result, 'g', 15));
        resultShown = true;
    };

    // Define the addition input action.
    auto appendPlus = [&display, &resultShown]()
    {
        QString current = display.text();

        // TODO: Return immediately if current already contains '+'.
        if (current.contains("+"))
        {
            return;
        }
        else
        {
            current += "+";
            resultShown = false;
        }
        // TODO: Append '+' and update the display.
        display.setText(current);
    };

    // Define the clear action.
    auto clearInput = [&display, &resultShown]()
    {
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
        [&appendPlus]()
        {
            appendPlus();
        });

    QObject::connect(
        &equlsButton,
        &QPushButton::clicked,
        &window,
        [&calculate]()
        {
            calculate();
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
