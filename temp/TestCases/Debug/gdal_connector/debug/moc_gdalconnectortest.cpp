/****************************************************************************
** Meta object code from reading C++ file 'gdalconnectortest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../TestCases/gdal_connector/gdalconnectortest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gdalconnectortest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GDALConnectorTest_t {
    QByteArrayData data[11];
    char stringdata[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_GDALConnectorTest_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_GDALConnectorTest_t qt_meta_stringdata_GDALConnectorTest = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 12),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 14),
QT_MOC_LITERAL(4, 47, 15),
QT_MOC_LITERAL(5, 63, 15),
QT_MOC_LITERAL(6, 79, 16),
QT_MOC_LITERAL(7, 96, 16),
QT_MOC_LITERAL(8, 113, 17),
QT_MOC_LITERAL(9, 131, 18),
QT_MOC_LITERAL(10, 150, 19)
    },
    "GDALConnectorTest\0initTestCase\0\0"
    "tableLoadTests\0tableStoreTests\0"
    "rasterLoadTests\0rasterStoreTests\0"
    "featureLoadTests\0featureStoreTests\0"
    "attributeLoadTests\0attributeStoreTests\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GDALConnectorTest[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08,
       3,    0,   60,    2, 0x08,
       4,    0,   61,    2, 0x08,
       5,    0,   62,    2, 0x08,
       6,    0,   63,    2, 0x08,
       7,    0,   64,    2, 0x08,
       8,    0,   65,    2, 0x08,
       9,    0,   66,    2, 0x08,
      10,    0,   67,    2, 0x08,

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

       0        // eod
};

void GDALConnectorTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GDALConnectorTest *_t = static_cast<GDALConnectorTest *>(_o);
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->tableLoadTests(); break;
        case 2: _t->tableStoreTests(); break;
        case 3: _t->rasterLoadTests(); break;
        case 4: _t->rasterStoreTests(); break;
        case 5: _t->featureLoadTests(); break;
        case 6: _t->featureStoreTests(); break;
        case 7: _t->attributeLoadTests(); break;
        case 8: _t->attributeStoreTests(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject GDALConnectorTest::staticMetaObject = {
    { &IlwisTestCase::staticMetaObject, qt_meta_stringdata_GDALConnectorTest.data,
      qt_meta_data_GDALConnectorTest,  qt_static_metacall, 0, 0}
};


const QMetaObject *GDALConnectorTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GDALConnectorTest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GDALConnectorTest.stringdata))
        return static_cast<void*>(const_cast< GDALConnectorTest*>(this));
    return IlwisTestCase::qt_metacast(_clname);
}

int GDALConnectorTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IlwisTestCase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
