/****************************************************************************
** Meta object code from reading C++ file 'UVectorField.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Include/InspectorField/UVectorField.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UVectorField.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ParadigmEditor__UVectorField_t {
    QByteArrayData data[3];
    char stringdata0[45];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ParadigmEditor__UVectorField_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ParadigmEditor__UVectorField_t qt_meta_stringdata_ParadigmEditor__UVectorField = {
    {
QT_MOC_LITERAL(0, 0, 28), // "ParadigmEditor::UVectorField"
QT_MOC_LITERAL(1, 29, 14), // "OnValueUpdated"
QT_MOC_LITERAL(2, 44, 0) // ""

    },
    "ParadigmEditor::UVectorField\0"
    "OnValueUpdated\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ParadigmEditor__UVectorField[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    2,

       0        // eod
};

void ParadigmEditor::UVectorField::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UVectorField *_t = static_cast<UVectorField *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnValueUpdated((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ParadigmEditor::UVectorField::staticMetaObject = {
    { &UVariableField::staticMetaObject, qt_meta_stringdata_ParadigmEditor__UVectorField.data,
      qt_meta_data_ParadigmEditor__UVectorField,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ParadigmEditor::UVectorField::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ParadigmEditor::UVectorField::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ParadigmEditor__UVectorField.stringdata0))
        return static_cast<void*>(this);
    return UVariableField::qt_metacast(_clname);
}

int ParadigmEditor::UVectorField::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UVariableField::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
