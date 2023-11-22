#include "appwindow.h"
#include "../../../Item_p.h"
#include "../../../LayoutingHost_p.h"
#include "../../../LayoutingGuest_p.h"
#include "../../../LayoutingSeparator_p.h"

#include <iostream>

using namespace KDDockWidgets;

class Host : public KDDockWidgets::Core::LayoutingHost
{
public:
    explicit Host(slint::ComponentHandle<AppWindow> ui)
        : ui(ui)
        , root(Core::ItemBoxContainer(this))
    {
        ui->on_window_size_changed_callback([this](float w, float h) -> bool {
            root.setSize_recursive({ int(w), int(h) });
            return true;
        });
    }

    bool supportsHonouringLayoutMinSize() const override
    {
        return true;
    }

    slint::ComponentHandle<AppWindow> ui;
    Core::ItemBoxContainer root;
};

namespace {

void update_model_row(DockWidgetDescriptor desc, slint::ComponentHandle<AppWindow> ui)
{
    auto model = ui->get_dockWidgets();
    assert(model);
    for (int i = 0, end = model->row_count(); i < end; ++i) {
        auto dw = model->row_data(0);
        if (dw->uniqueName == desc.uniqueName) {
            model->set_row_data(i, desc);
            return;
        }
    }
    std::cerr << "Failed to find descriptor for" << desc.uniqueName << "\n";
}

int index_of_row(std::string name, slint::ComponentHandle<AppWindow> ui)
{
    auto model = ui->get_dockWidgets();
    if (!model)
        return -1;

    for (int i = 0, end = model->row_count(); i < end; ++i) {
        auto dw = model->row_data(0);
        if (dw->uniqueName.data() == name) {
            return i;
        }
    }

    return -1;
}

void add_model_row(DockWidgetDescriptor desc, slint::ComponentHandle<AppWindow> ui)
{
    const int index = index_of_row(desc.uniqueName.data(), ui);
    if (index != -1) {
        std::cerr << "add_model_row: Row already exists!\n";
        return;
    }

    if (auto model = ui->get_dockWidgets()) {
        auto vecModel = std::static_pointer_cast<slint::VectorModel<DockWidgetDescriptor>>(model);
        vecModel->push_back(desc);
    } else {
        std::vector<DockWidgetDescriptor> dockDescriptors = {
            desc
        };

        ui->set_dockWidgets(std::make_shared<slint::VectorModel<DockWidgetDescriptor>>(dockDescriptors));
    }
}

}

class Guest : public KDDockWidgets::Core::LayoutingGuest
{
public:
    explicit Guest(Host *host, const QString &uniqueName, slint::ComponentHandle<AppWindow> ui)
        : _uniqueName(uniqueName)
        , ui(ui)
    {
        auto item = new Core::Item(host);
        item->setGuest(this);
    }

    Size minSize() const override
    {
        return { 100, 100 };
    }

    Size maxSizeHint() const override
    {
        return { -1, -1 };
    }

    void setGeometry(Rect r) override
    {
        if (r == _geometry)
            return;

        _geometry = r;
        update_model_row(DockWidgetDescriptor { slint::SharedString(_uniqueName), 0, 0, 200, 300 }, ui);
    }

    DockWidgetDescriptor descriptor() const
    {
        return DockWidgetDescriptor { slint::SharedString(_uniqueName), float(_geometry.x()), float(geometry().y()), 200, 300 };
    }

    void setVisible(bool is) override
    {
        _isVisible = is;
    }

    Rect geometry() const override
    {
        return _geometry;
    }

    void setHost(Core::LayoutingHost *parent) override
    {
        if (_layoutingHost == parent)
            return;

        std::cout << "Adding row\n";
        add_model_row(descriptor(), ui);
        _layoutingHost = parent;
    }

    Core::LayoutingHost *host() const override
    {
        return _layoutingHost;
    }

    QString id() const override
    {
        return _uniqueName;
    }

    Core::LayoutingHost *_layoutingHost = nullptr;
    QString _uniqueName;
    slint::ComponentHandle<AppWindow> ui;
    Rect _geometry;
    bool _isVisible = true;
};

class Separator : public Core::LayoutingSeparator
{
public:
    using Core::LayoutingSeparator::LayoutingSeparator;

    Rect geometry() const override
    {
        return geo;
    }

    void setGeometry(Rect g) override
    {
        geo = g;
    }

    Rect geo;
};

int main(int argc, char **argv)
{
    auto ui = AppWindow::create();
    ui->on_clickme([&] {
        auto docks = ui->get_dockWidgets();
        auto dock = docks->row_data(0);
        dock->height = 200;
        std::cout << "clicked!\n";
        docks->set_row_data(0, { "name", 0, 0, 200, 200 });
    });

    /// Tell KDDW about our separators
    Core::Item::setCreateSeparatorFunc([](Core::LayoutingHost *host, Qt::Orientation orientation, Core::ItemBoxContainer *container) -> Core::LayoutingSeparator * {
        return new Separator(host, orientation, container);
    });

    Host host(ui);
    auto guest1 = new Guest(&host, "1", ui);
    auto guest2 = new Guest(&host, "2", ui);
    auto guest3 = new Guest(&host, "3", ui);
    auto guest4 = new Guest(&host, "4", ui);

    host.root.insertItem(guest1->layoutItem(), KDDockWidgets::Location_OnLeft);
    host.root.insertItem(guest2->layoutItem(), KDDockWidgets::Location_OnRight);
    host.root.insertItemRelativeTo(guest3->layoutItem(), /*relativeTo=*/guest2->layoutItem(), KDDockWidgets::Location_OnBottom);
    host.root.insertItem(guest4->layoutItem(), KDDockWidgets::Location_OnTop, Size(0, 200));

    std::vector<DockWidgetDescriptor> dockDescriptors = {
        { "name", 0, 0, 100, 100 }
    };

    auto model = std::make_shared<slint::VectorModel<DockWidgetDescriptor>>(dockDescriptors);
    ui->set_dockWidgets(model);

    ui->run();
    return 0;
}
