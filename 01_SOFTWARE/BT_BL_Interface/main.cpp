#include "bt_bl_interface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BT_BL_Interface w;
    w.show();

    return a.exec();
}
