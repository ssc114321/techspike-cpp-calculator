#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>

int main(int argc, char* argv[])
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
    QPushButton button1("1", &window);

    // TODO: Create buttons for 2, 3, and 0.
    QPushButton button2("2", &window);
    QPushButton button3("3", &window);
    QPushButton button0("0", &window);

    // Arrange the display and button vertically.
    QVBoxLayout layout(&window);
    layout.addWidget(&display);

    // Add a grid layout for the keypad.
    QGridLayout keypad;
    layout.addLayout(&keypad);

    // Place the digit buttons in the grid.
    keypad.addWidget(&button1, 0, 0);

    // TODO: Place the remaining buttons.
    keypad.addWidget(&button2, 0, 1);
    keypad.addWidget(&button3, 0, 2);
    keypad.addWidget(&button0, 1, 1);

    // Connect the button's clicked signal to update the display.
    QObject::connect(
        &button1,
        &QPushButton::clicked,
        &window,
        [&display]() {
            // Update the display when the button is clicked.
            QString current = display.text();
            if (current == "0") {
                current = "1";
            }
            else {
                current += "1";
            }
             display.setText(current);
        }
    );

    QObject::connect(
        &button2,
        &QPushButton::clicked,
        &window,
        [&display]() {
            // Update the display when the button is clicked.
            QString current = display.text();
            if (current == "0") {
                current = "2";
            }
            else {
                current += "2";
            }
             display.setText(current);
        }
    );
    
    QObject::connect(
        &button3,
        &QPushButton::clicked,
        &window,
        [&display]() {
            // Update the display when the button is clicked.
            QString current = display.text();
            if (current == "0") {
                current = "3";
            }
            else {
                current += "3";
            }
             display.setText(current);
        }
    );

    QObject::connect(
        &button0,
        &QPushButton::clicked,
        &window,
        [&display]() {
            // Update the display when the button is clicked.
            QString current = display.text();
            if (current == "0") {
                current = "0";
            }
            else {
                current += "0";
            }
             display.setText(current);
        }
    );

    // Show the window.
    window.show();

    // Run the event loop and return its exit code.
    return(app.exec());
}
