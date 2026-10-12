#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QKeySequence>
#include <QShortcut>

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

    // Define the clear action.
    auto clearInput = [&display]()
    {
        display.setText("0");
    };

    // Define the delete action.
    auto deleteLast = [&display]()
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
    };

    // Define the shared digit input action.
    auto appendDigit = [&display](const QString &digit)
    {
        QString current = display.text();
        if (current == "0")
        {
            current = digit;
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

    // Create the clear shortcut.
    QShortcut clearShortcut(QKeySequence(Qt::Key_Escape), &window);

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

    // Show the window.
    window.show();

    // Run the event loop and return its exit code.
    return (app.exec());
}
