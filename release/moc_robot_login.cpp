/****************************************************************************
** Meta object code from reading C++ file 'robot_login.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../robot_login.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'robot_login.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_robot_login_t {
    QByteArrayData data[13];
    char stringdata0[262];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_robot_login_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_robot_login_t qt_meta_stringdata_robot_login = {
    {
QT_MOC_LITERAL(0, 0, 11), // "robot_login"
QT_MOC_LITERAL(1, 12, 12), // "flush_modbus"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 26), // "on_lianjie_caijiqi_clicked"
QT_MOC_LITERAL(4, 53, 24), // "on_kaiqi_caijiqi_clicked"
QT_MOC_LITERAL(5, 78, 9), // "readReady"
QT_MOC_LITERAL(6, 88, 11), // "kaishicaiji"
QT_MOC_LITERAL(7, 100, 26), // "on_kaiqi_caijiqi_2_clicked"
QT_MOC_LITERAL(8, 127, 26), // "on_kaiqi_caijiqi_3_clicked"
QT_MOC_LITERAL(9, 154, 26), // "on_kaiqi_caijiqi_5_clicked"
QT_MOC_LITERAL(10, 181, 26), // "on_kaiqi_caijiqi_6_clicked"
QT_MOC_LITERAL(11, 208, 26), // "on_kaiqi_caijiqi_4_clicked"
QT_MOC_LITERAL(12, 235, 26) // "on_kaiqi_caijiqi_7_clicked"

    },
    "robot_login\0flush_modbus\0\0"
    "on_lianjie_caijiqi_clicked\0"
    "on_kaiqi_caijiqi_clicked\0readReady\0"
    "kaishicaiji\0on_kaiqi_caijiqi_2_clicked\0"
    "on_kaiqi_caijiqi_3_clicked\0"
    "on_kaiqi_caijiqi_5_clicked\0"
    "on_kaiqi_caijiqi_6_clicked\0"
    "on_kaiqi_caijiqi_4_clicked\0"
    "on_kaiqi_caijiqi_7_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_robot_login[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void robot_login::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<robot_login *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->flush_modbus(); break;
        case 1: _t->on_lianjie_caijiqi_clicked(); break;
        case 2: _t->on_kaiqi_caijiqi_clicked(); break;
        case 3: _t->readReady(); break;
        case 4: _t->kaishicaiji(); break;
        case 5: _t->on_kaiqi_caijiqi_2_clicked(); break;
        case 6: _t->on_kaiqi_caijiqi_3_clicked(); break;
        case 7: _t->on_kaiqi_caijiqi_5_clicked(); break;
        case 8: _t->on_kaiqi_caijiqi_6_clicked(); break;
        case 9: _t->on_kaiqi_caijiqi_4_clicked(); break;
        case 10: _t->on_kaiqi_caijiqi_7_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (robot_login::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&robot_login::flush_modbus)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject robot_login::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_robot_login.data,
    qt_meta_data_robot_login,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *robot_login::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *robot_login::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_robot_login.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int robot_login::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void robot_login::flush_modbus()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
