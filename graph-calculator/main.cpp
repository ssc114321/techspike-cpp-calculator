#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

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

    // Create a button labeled "7".
    QPushButton button("7", &window);

    // Arrange the display and button vertically.
    QVBoxLayout layout(&window);
    layout.addWidget(&display);

    // Connect the button's clicked signal to update the display.
    QObject::connect(
        &button,
        &QPushButton::clicked,
        &window,
        [&display]() {
            // Update the display when the button is clicked.
            display.setText("7");
        }
    );

    // Show the window.
    window.show();

    // Run the event loop and return its exit code.
    return(app.exec());
}
