/****************************************************************************
** Meta object code from reading C++ file 'RuleEditWidget.h'
**
** Created: Thu Jan 24 15:10:20 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "RuleEditWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RuleEditWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RuleEditWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   16,   15,   15, 0x0a,
      48,   16,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RuleEditWidget[] = {
    "RuleEditWidget\0\0index\0ruleSelected(QModelIndex)\0"
    "ruleSave(QModelIndex)\0"
};

const QMetaObject RuleEditWidget::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_RuleEditWidget,
      qt_meta_data_RuleEditWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RuleEditWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RuleEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RuleEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RuleEditWidget))
        return static_cast<void*>(const_cast< RuleEditWidget*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int RuleEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ruleSelected((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: ruleSave((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
