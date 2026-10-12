#include <QApplication>
#include <QWidget>

int main(int argc, char* argv[])
{
    // 1. Create the QApplication instance.
    QApplication app(argc, argv);

    // 2. Create the main window.
    QWidget window;

    // 3. Set the window title.
    window.setWindowTitle("Graph Calculator");

    // 4. Set the window size to 800 by 600 pixels.
    window.resize(800, 600);

    // 5. Show the window.
    window.show();

    // 6. Run the event loop and return its exit code.
    return(app.exec());
}
