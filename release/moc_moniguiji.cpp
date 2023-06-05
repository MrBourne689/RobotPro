/****************************************************************************
** Meta object code from reading C++ file 'moniguiji.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../moniguiji.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'moniguiji.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_moniguiji_t {
    QByteArrayData data[19];
    char stringdata0[287];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_moniguiji_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_moniguiji_t qt_meta_stringdata_moniguiji = {
    {
QT_MOC_LITERAL(0, 0, 9), // "moniguiji"
QT_MOC_LITERAL(1, 10, 10), // "flush_path"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 4), // "send"
QT_MOC_LITERAL(4, 27, 10), // "paintEvent"
QT_MOC_LITERAL(5, 38, 12), // "QPaintEvent*"
QT_MOC_LITERAL(6, 51, 15), // "mousePressEvent"
QT_MOC_LITERAL(7, 67, 12), // "QMouseEvent*"
QT_MOC_LITERAL(8, 80, 5), // "event"
QT_MOC_LITERAL(9, 86, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(10, 101, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(11, 123, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(12, 147, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(13, 171, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(14, 195, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(15, 219, 5), // "dotai"
QT_MOC_LITERAL(16, 225, 23), // "on_pushButton_6_clicked"
QT_MOC_LITERAL(17, 249, 13), // "handleTimeout"
QT_MOC_LITERAL(18, 263, 23) // "on_pushButton_7_clicked"

    },
    "moniguiji\0flush_path\0\0send\0paintEvent\0"
    "QPaintEvent*\0mousePressEvent\0QMouseEvent*\0"
    "event\0mouseMoveEvent\0on_pushButton_clicked\0"
    "on_pushButton_2_clicked\0on_pushButton_3_clicked\0"
    "on_pushButton_4_clicked\0on_pushButton_5_clicked\0"
    "dotai\0on_pushButton_6_clicked\0"
    "handleTimeout\0on_pushButton_7_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_moniguiji[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    1,   85,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   88,    2, 0x08 /* Private */,
       6,    1,   91,    2, 0x08 /* Private */,
       9,    1,   94,    2, 0x08 /* Private */,
      10,    0,   97,    2, 0x08 /* Private */,
      11,    0,   98,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    0,  100,    2, 0x08 /* Private */,
      14,    0,  101,    2, 0x08 /* Private */,
      15,    0,  102,    2, 0x08 /* Private */,
      16,    0,  103,    2, 0x08 /* Private */,
      17,    0,  104,    2, 0x08 /* Private */,
      18,    0,  105,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
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

void moniguiji::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<moniguiji *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->flush_path(); break;
        case 1: _t->send((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        case 3: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_clicked(); break;
        case 6: _t->on_pushButton_2_clicked(); break;
        case 7: _t->on_pushButton_3_clicked(); break;
        case 8: _t->on_pushButton_4_clicked(); break;
        case 9: _t->on_pushButton_5_clicked(); break;
        case 10: _t->dotai(); break;
        case 11: _t->on_pushButton_6_clicked(); break;
        case 12: _t->handleTimeout(); break;
        case 13: _t->on_pushButton_7_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (moniguiji::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&moniguiji::flush_path)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (moniguiji::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&moniguiji::send)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject moniguiji::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_moniguiji.data,
    qt_meta_data_moniguiji,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *moniguiji::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *moniguiji::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_moniguiji.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int moniguiji::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void moniguiji::flush_path()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void moniguiji::send(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
