/****************************************************************************
** Meta object code from reading C++ file 'juliantimetests.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../TestSuites/core/util/juliantimetests.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'juliantimetests.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_JulianTimeTests_t {
    QByteArrayData data[7];
    char stringdata[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_JulianTimeTests_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_JulianTimeTests_t qt_meta_stringdata_JulianTimeTests = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 16),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 7),
QT_MOC_LITERAL(4, 42, 11),
QT_MOC_LITERAL(5, 54, 10),
QT_MOC_LITERAL(6, 65, 12)
    },
    "JulianTimeTests\0constructionTime\0\0"
    "getters\0conversions\0operations\0"
    "timeInterval\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JulianTimeTests[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08,
       3,    0,   40,    2, 0x08,
       4,    0,   41,    2, 0x08,
       5,    0,   42,    2, 0x08,
       6,    0,   43,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void JulianTimeTests::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        JulianTimeTests *_t = static_cast<JulianTimeTests *>(_o);
        switch (_id) {
        case 0: _t->constructionTime(); break;
        case 1: _t->getters(); break;
        case 2: _t->conversions(); break;
        case 3: _t->operations(); break;
        case 4: _t->timeInterval(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject JulianTimeTests::staticMetaObject = {
    { &IlwisTestCase::staticMetaObject, qt_meta_stringdata_JulianTimeTests.data,
      qt_meta_data_JulianTimeTests,  qt_static_metacall, 0, 0}
};


const QMetaObject *JulianTimeTests::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JulianTimeTests::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_JulianTimeTests.stringdata))
        return static_cast<void*>(const_cast< JulianTimeTests*>(this));
    return IlwisTestCase::qt_metacast(_clname);
}

int JulianTimeTests::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IlwisTestCase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
