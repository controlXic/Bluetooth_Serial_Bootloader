/****************************************************************************
** Meta object code from reading C++ file 'bt_bl_interface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../bt_bl_interface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bt_bl_interface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BT_BL_Interface_t {
    QByteArrayData data[17];
    char stringdata0[279];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BT_BL_Interface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BT_BL_Interface_t qt_meta_stringdata_BT_BL_Interface = {
    {
QT_MOC_LITERAL(0, 0, 15), // "BT_BL_Interface"
QT_MOC_LITERAL(1, 16, 12), // "showPortInfo"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 3), // "idx"
QT_MOC_LITERAL(4, 34, 23), // "on_refreshPorts_clicked"
QT_MOC_LITERAL(5, 58, 22), // "on_connectPort_clicked"
QT_MOC_LITERAL(6, 81, 7), // "checked"
QT_MOC_LITERAL(7, 89, 12), // "on_read_data"
QT_MOC_LITERAL(8, 102, 20), // "on_clearData_clicked"
QT_MOC_LITERAL(9, 123, 20), // "on_scanBlDev_clicked"
QT_MOC_LITERAL(10, 144, 16), // "discover_devices"
QT_MOC_LITERAL(11, 161, 17), // "on_clrDev_clicked"
QT_MOC_LITERAL(12, 179, 21), // "on_connectDev_clicked"
QT_MOC_LITERAL(13, 201, 18), // "on_stSpBtl_clicked"
QT_MOC_LITERAL(14, 220, 16), // "check_bootloader"
QT_MOC_LITERAL(15, 237, 19), // "reset_window_status"
QT_MOC_LITERAL(16, 257, 21) // "on_passButton_clicked"

    },
    "BT_BL_Interface\0showPortInfo\0\0idx\0"
    "on_refreshPorts_clicked\0on_connectPort_clicked\0"
    "checked\0on_read_data\0on_clearData_clicked\0"
    "on_scanBlDev_clicked\0discover_devices\0"
    "on_clrDev_clicked\0on_connectDev_clicked\0"
    "on_stSpBtl_clicked\0check_bootloader\0"
    "reset_window_status\0on_passButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BT_BL_Interface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x08 /* Private */,
       4,    0,   82,    2, 0x08 /* Private */,
       5,    1,   83,    2, 0x08 /* Private */,
       7,    0,   86,    2, 0x08 /* Private */,
       8,    0,   87,    2, 0x08 /* Private */,
       9,    0,   88,    2, 0x08 /* Private */,
      10,    0,   89,    2, 0x08 /* Private */,
      11,    0,   90,    2, 0x08 /* Private */,
      12,    1,   91,    2, 0x08 /* Private */,
      13,    0,   94,    2, 0x08 /* Private */,
      14,    0,   95,    2, 0x08 /* Private */,
      15,    0,   96,    2, 0x08 /* Private */,
      16,    0,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BT_BL_Interface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BT_BL_Interface *_t = static_cast<BT_BL_Interface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showPortInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_refreshPorts_clicked(); break;
        case 2: _t->on_connectPort_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_read_data(); break;
        case 4: _t->on_clearData_clicked(); break;
        case 5: _t->on_scanBlDev_clicked(); break;
        case 6: _t->discover_devices(); break;
        case 7: _t->on_clrDev_clicked(); break;
        case 8: _t->on_connectDev_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_stSpBtl_clicked(); break;
        case 10: _t->check_bootloader(); break;
        case 11: _t->reset_window_status(); break;
        case 12: _t->on_passButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject BT_BL_Interface::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_BT_BL_Interface.data,
      qt_meta_data_BT_BL_Interface,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *BT_BL_Interface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BT_BL_Interface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BT_BL_Interface.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int BT_BL_Interface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
