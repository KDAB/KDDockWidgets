#include <cstdio>

#include <ViewGuard.h>
#include <qtwidgets/views/ViewWrapper_qtwidgets.h>

using namespace KDDockWidgets;

void test(bool cond, const char *stmt, int line)
{
    if (!cond) {
        printf("[FAILED] %s line; %d\n", stmt, line);
        exit(1);
    }
}
#define TEST(cond) test(cond, #cond, __LINE__)

int main()
{
    ViewGuard g(nullptr);
    TEST(g.isNull());

    {
        Views::ViewWrapper_qtwidgets wv(static_cast<QWidget*>(nullptr));
        g = &wv;
        TEST(!g.isNull());
    }

    TEST(g.isNull());

    // Test when ViewGuard is destroyed before view
    // May not crash without ASAN
    Views::ViewWrapper_qtwidgets wv(static_cast<QWidget*>(nullptr));
    {
        ViewGuard gg(&wv);
        TEST(!gg.isNull());
    }
}
