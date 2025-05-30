#include <gtkmm.h>
#include <iostream>

class MyWindow : public Gtk::Window
{
public:
    MyWindow()
    {
        set_title("Hello gtkmm");
        set_default_size(300, 200);

        button.set_label("Click me!");
        button.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button_clicked));

        add(button);
        button.show();
    }

protected:
    void on_button_clicked()
    {
        set_title("Button clicked!");
    }

private:
    Gtk::Button button;
};

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    std::cout << typeid(app).name() << std::endl;
    std::cout << "Running Application now...." << std::endl;

    MyWindow window;
    return app->run(window);
}
