/****************************************************************************
** Meta object code from reading C++ file 'xiancheng.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../xiancheng.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xiancheng.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_cam1_t {
    QByteArrayData data[8];
    char stringdata0[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_cam1_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_cam1_t qt_meta_stringdata_cam1 = {
    {
QT_MOC_LITERAL(0, 0, 4), // "cam1"
QT_MOC_LITERAL(1, 5, 4), // "send"
QT_MOC_LITERAL(2, 10, 0), // ""
QT_MOC_LITERAL(3, 11, 7), // "__int64"
QT_MOC_LITERAL(4, 19, 4), // "rev1"
QT_MOC_LITERAL(5, 24, 3), // "rev"
QT_MOC_LITERAL(6, 28, 4), // "HWND"
QT_MOC_LITERAL(7, 33, 7) // "working"

    },
    "cam1\0send\0\0__int64\0rev1\0rev\0HWND\0"
    "working"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cam1[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   37,    2, 0x0a /* Public */,
       5,    1,   40,    2, 0x0a /* Public */,
       7,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,

       0        // eod
};

void cam1::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<cam1 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send((*reinterpret_cast< __int64(*)>(_a[1]))); break;
        case 1: _t->rev1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->rev((*reinterpret_cast< HWND(*)>(_a[1]))); break;
        case 3: _t->working(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (cam1::*)(__int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cam1::send)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject cam1::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_cam1.data,
    qt_meta_data_cam1,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *cam1::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cam1::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_cam1.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int cam1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void cam1::send(__int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_cam2_t {
    QByteArrayData data[8];
    char stringdata0[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_cam2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_cam2_t qt_meta_stringdata_cam2 = {
    {
QT_MOC_LITERAL(0, 0, 4), // "cam2"
QT_MOC_LITERAL(1, 5, 4), // "send"
QT_MOC_LITERAL(2, 10, 0), // ""
QT_MOC_LITERAL(3, 11, 7), // "__int64"
QT_MOC_LITERAL(4, 19, 4), // "rev1"
QT_MOC_LITERAL(5, 24, 3), // "rev"
QT_MOC_LITERAL(6, 28, 4), // "HWND"
QT_MOC_LITERAL(7, 33, 7) // "working"

    },
    "cam2\0send\0\0__int64\0rev1\0rev\0HWND\0"
    "working"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cam2[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   37,    2, 0x0a /* Public */,
       5,    1,   40,    2, 0x0a /* Public */,
       7,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,

       0        // eod
};

void cam2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<cam2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send((*reinterpret_cast< __int64(*)>(_a[1]))); break;
        case 1: _t->rev1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->rev((*reinterpret_cast< HWND(*)>(_a[1]))); break;
        case 3: _t->working(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (cam2::*)(__int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cam2::send)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject cam2::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_cam2.data,
    qt_meta_data_cam2,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *cam2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cam2::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_cam2.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int cam2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void cam2::send(__int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_rob1_t {
    QByteArrayData data[25];
    char stringdata0[203];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_rob1_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_rob1_t qt_meta_stringdata_rob1 = {
    {
QT_MOC_LITERAL(0, 0, 4), // "rob1"
QT_MOC_LITERAL(1, 5, 18), // "flush_modbus_value"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "send_104"
QT_MOC_LITERAL(4, 34, 5), // "send_"
QT_MOC_LITERAL(5, 40, 8), // "send_100"
QT_MOC_LITERAL(6, 49, 8), // "send_102"
QT_MOC_LITERAL(7, 58, 14), // "warning_signal"
QT_MOC_LITERAL(8, 73, 1), // "a"
QT_MOC_LITERAL(9, 75, 13), // "rob_connected"
QT_MOC_LITERAL(10, 89, 10), // "xintiaorob"
QT_MOC_LITERAL(11, 100, 23), // "send_robot_connect_bool"
QT_MOC_LITERAL(12, 124, 4), // "rev2"
QT_MOC_LITERAL(13, 129, 4), // "rev1"
QT_MOC_LITERAL(14, 134, 9), // "readReady"
QT_MOC_LITERAL(15, 144, 11), // "kaishicaiji"
QT_MOC_LITERAL(16, 156, 4), // "rev3"
QT_MOC_LITERAL(17, 161, 4), // "rev4"
QT_MOC_LITERAL(18, 166, 5), // "count"
QT_MOC_LITERAL(19, 172, 4), // "rev5"
QT_MOC_LITERAL(20, 177, 4), // "rev6"
QT_MOC_LITERAL(21, 182, 4), // "rev7"
QT_MOC_LITERAL(22, 187, 4), // "rev8"
QT_MOC_LITERAL(23, 192, 4), // "rev9"
QT_MOC_LITERAL(24, 197, 5) // "rev10"

    },
    "rob1\0flush_modbus_value\0\0send_104\0"
    "send_\0send_100\0send_102\0warning_signal\0"
    "a\0rob_connected\0xintiaorob\0"
    "send_robot_connect_bool\0rev2\0rev1\0"
    "readReady\0kaishicaiji\0rev3\0rev4\0count\0"
    "rev5\0rev6\0rev7\0rev8\0rev9\0rev10"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_rob1[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  119,    2, 0x06 /* Public */,
       3,    1,  120,    2, 0x06 /* Public */,
       4,    1,  123,    2, 0x06 /* Public */,
       5,    1,  126,    2, 0x06 /* Public */,
       6,    1,  129,    2, 0x06 /* Public */,
       7,    1,  132,    2, 0x06 /* Public */,
       9,    1,  135,    2, 0x06 /* Public */,
      10,    1,  138,    2, 0x06 /* Public */,
      11,    1,  141,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,  144,    2, 0x0a /* Public */,
      13,    1,  147,    2, 0x0a /* Public */,
      14,    0,  150,    2, 0x0a /* Public */,
      15,    0,  151,    2, 0x0a /* Public */,
      16,    1,  152,    2, 0x0a /* Public */,
      17,    2,  155,    2, 0x0a /* Public */,
      19,    1,  160,    2, 0x0a /* Public */,
      20,    1,  163,    2, 0x0a /* Public */,
      21,    1,  166,    2, 0x0a /* Public */,
      22,    1,  169,    2, 0x0a /* Public */,
      23,    1,  172,    2, 0x0a /* Public */,
      24,    1,  175,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,   18,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void rob1::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<rob1 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->flush_modbus_value(); break;
        case 1: _t->send_104((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->send_((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->send_100((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->send_102((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->warning_signal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->rob_connected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->xintiaorob((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->send_robot_connect_bool((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->rev2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->rev1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->readReady(); break;
        case 12: _t->kaishicaiji(); break;
        case 13: _t->rev3((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->rev4((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: _t->rev5((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->rev6((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->rev7((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->rev8((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->rev9((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->rev10((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (rob1::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&rob1::flush_modbus_value)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (rob1::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&rob1::send_104)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (rob1::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&rob1::send_)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (rob1::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&rob1::send_100)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (rob1::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&rob1::send_102)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (rob1::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&rob1::warning_signal)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (rob1::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&rob1::rob_connected)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (rob1::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&rob1::xintiaorob)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (rob1::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&rob1::send_robot_connect_bool)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject rob1::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_rob1.data,
    qt_meta_data_rob1,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *rob1::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *rob1::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_rob1.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int rob1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void rob1::flush_modbus_value()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void rob1::send_104(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void rob1::send_(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void rob1::send_100(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void rob1::send_102(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void rob1::warning_signal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void rob1::rob_connected(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void rob1::xintiaorob(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void rob1::send_robot_connect_bool(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
struct qt_meta_stringdata_plc_t {
    QByteArrayData data[9];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_plc_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_plc_t qt_meta_stringdata_plc = {
    {
QT_MOC_LITERAL(0, 0, 3), // "plc"
QT_MOC_LITERAL(1, 4, 19), // "flush_modbus_value1"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 19), // "flush_modbus_value2"
QT_MOC_LITERAL(4, 45, 10), // "xintiaoplc"
QT_MOC_LITERAL(5, 56, 4), // "rev1"
QT_MOC_LITERAL(6, 61, 10), // "readReady1"
QT_MOC_LITERAL(7, 72, 12), // "kaishicaiji1"
QT_MOC_LITERAL(8, 85, 8) // "caozuodu"

    },
    "plc\0flush_modbus_value1\0\0flush_modbus_value2\0"
    "xintiaoplc\0rev1\0readReady1\0kaishicaiji1\0"
    "caozuodu"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_plc[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    1,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   54,    2, 0x0a /* Public */,
       6,    0,   57,    2, 0x0a /* Public */,
       7,    0,   58,    2, 0x0a /* Public */,
       8,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void plc::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<plc *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->flush_modbus_value1(); break;
        case 1: _t->flush_modbus_value2(); break;
        case 2: _t->xintiaoplc((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->rev1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->readReady1(); break;
        case 5: _t->kaishicaiji1(); break;
        case 6: _t->caozuodu(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (plc::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&plc::flush_modbus_value1)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (plc::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&plc::flush_modbus_value2)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (plc::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&plc::xintiaoplc)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject plc::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_plc.data,
    qt_meta_data_plc,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *plc::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *plc::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_plc.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int plc::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void plc::flush_modbus_value1()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void plc::flush_modbus_value2()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void plc::xintiaoplc(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
