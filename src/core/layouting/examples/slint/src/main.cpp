#include "appwindow.h"

int main(int argc, char **argv)
{
    auto ui = AppWindow::create();

    ui->on_request_increase_value([&] {
        ui->set_counter(ui->get_counter() + 1);
    });

    ui->run();
    return 0;
}
