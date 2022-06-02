/****************************************************************************
** Meta object code from reading C++ file 'LBD_VideoMeeting_Meeting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LBD_VideoMeeting_Meeting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LBD_VideoMeeting_Meeting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LBD_VideoMeeting_Meeting_t {
    QByteArrayData data[21];
    char stringdata0[283];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LBD_VideoMeeting_Meeting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LBD_VideoMeeting_Meeting_t qt_meta_stringdata_LBD_VideoMeeting_Meeting = {
    {
QT_MOC_LITERAL(0, 0, 24), // "LBD_VideoMeeting_Meeting"
QT_MOC_LITERAL(1, 25, 9), // "UserReady"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 16), // "QList<UserInfo>*"
QT_MOC_LITERAL(4, 53, 5), // "users"
QT_MOC_LITERAL(5, 59, 5), // "char*"
QT_MOC_LITERAL(6, 65, 9), // "ClassName"
QT_MOC_LITERAL(7, 75, 15), // "QList<Camares>*"
QT_MOC_LITERAL(8, 91, 4), // "list"
QT_MOC_LITERAL(9, 96, 13), // "CancelChecked"
QT_MOC_LITERAL(10, 110, 21), // "on_btn_invite_clicked"
QT_MOC_LITERAL(11, 132, 7), // "checked"
QT_MOC_LITERAL(12, 140, 13), // "ReceiveInvite"
QT_MOC_LITERAL(13, 154, 7), // "Invited"
QT_MOC_LITERAL(14, 162, 10), // "getChecked"
QT_MOC_LITERAL(15, 173, 9), // "getCancel"
QT_MOC_LITERAL(16, 183, 15), // "TimeLabelUpdate"
QT_MOC_LITERAL(17, 199, 28), // "on_btn_InviteConfirm_clicked"
QT_MOC_LITERAL(18, 228, 20), // "on_btn_close_clicked"
QT_MOC_LITERAL(19, 249, 22), // "on_btn_close_2_clicked"
QT_MOC_LITERAL(20, 272, 10) // "QUITSIGNAL"

    },
    "LBD_VideoMeeting_Meeting\0UserReady\0\0"
    "QList<UserInfo>*\0users\0char*\0ClassName\0"
    "QList<Camares>*\0list\0CancelChecked\0"
    "on_btn_invite_clicked\0checked\0"
    "ReceiveInvite\0Invited\0getChecked\0"
    "getCancel\0TimeLabelUpdate\0"
    "on_btn_InviteConfirm_clicked\0"
    "on_btn_close_clicked\0on_btn_close_2_clicked\0"
    "QUITSIGNAL"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LBD_VideoMeeting_Meeting[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   69,    2, 0x06 /* Public */,
       9,    0,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   77,    2, 0x08 /* Private */,
      12,    1,   80,    2, 0x08 /* Private */,
      14,    0,   83,    2, 0x08 /* Private */,
      15,    0,   84,    2, 0x08 /* Private */,
      16,    0,   85,    2, 0x08 /* Private */,
      17,    0,   86,    2, 0x08 /* Private */,
      18,    0,   87,    2, 0x08 /* Private */,
      19,    0,   88,    2, 0x08 /* Private */,
      20,    0,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7,    4,    6,    8,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, 0x80000000 | 3,   13,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LBD_VideoMeeting_Meeting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LBD_VideoMeeting_Meeting *_t = static_cast<LBD_VideoMeeting_Meeting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UserReady((*reinterpret_cast< QList<UserInfo>*(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< QList<Camares>*(*)>(_a[3]))); break;
        case 1: _t->CancelChecked(); break;
        case 2: _t->on_btn_invite_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->ReceiveInvite((*reinterpret_cast< QList<UserInfo>*(*)>(_a[1]))); break;
        case 4: { bool _r = _t->getChecked();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->getCancel();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->TimeLabelUpdate(); break;
        case 7: _t->on_btn_InviteConfirm_clicked(); break;
        case 8: _t->on_btn_close_clicked(); break;
        case 9: _t->on_btn_close_2_clicked(); break;
        case 10: _t->QUITSIGNAL(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (LBD_VideoMeeting_Meeting::*_t)(QList<UserInfo> * , char * , QList<Camares> * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LBD_VideoMeeting_Meeting::UserReady)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (LBD_VideoMeeting_Meeting::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LBD_VideoMeeting_Meeting::CancelChecked)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LBD_VideoMeeting_Meeting::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_LBD_VideoMeeting_Meeting.data,
      qt_meta_data_LBD_VideoMeeting_Meeting,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *LBD_VideoMeeting_Meeting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LBD_VideoMeeting_Meeting::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LBD_VideoMeeting_Meeting.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int LBD_VideoMeeting_Meeting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
void LBD_VideoMeeting_Meeting::UserReady(QList<UserInfo> * _t1, char * _t2, QList<Camares> * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LBD_VideoMeeting_Meeting::CancelChecked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
