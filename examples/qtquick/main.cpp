#include <QQuickView>
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setSource(QUrl("qrc:/main.qml"));
    view.resize(1000, 800);
    view.show();
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    return app.exec();
}
