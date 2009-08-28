/****************************************************************************
** Meta object code from reading C++ file 'GUI_Main.h'
**
** Created: Fri 28. Aug 17:24:11 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GUI_Main.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUI_Main.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GUI_Main[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      35,    9,    9,    9, 0x08,
      64,    9,    9,    9, 0x08,
      86,    9,    9,    9, 0x08,
     108,    9,    9,    9, 0x08,
     126,    9,    9,    9, 0x08,
     150,    9,    9,    9, 0x08,
     172,    9,    9,    9, 0x08,
     194,    9,    9,    9, 0x08,
     216,    9,    9,    9, 0x08,
     256,    9,    9,    9, 0x08,
     296,    9,    9,    9, 0x08,
     318,    9,    9,    9, 0x08,
     340,    9,    9,    9, 0x08,
     360,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GUI_Main[] = {
    "GUI_Main\0\0OnMenu_File_Open_Files()\0"
    "OnMenu_File_Open_Directory()\0"
    "OnMenu_View_Summary()\0OnMenu_View_ByFrame()\0"
    "OnMenu_View_XML()\0OnMenu_View_MediaInfo()\0"
    "OnMenu_Verbosity_03()\0OnMenu_Verbosity_05()\0"
    "OnMenu_Verbosity_10()\0"
    "OnMenu_Debug_MediaInfo_InternalFields()\0"
    "OnMenu_Debug_MediaInfo_RawFieldsNames()\0"
    "OnMenu_Help_Summary()\0OnMenu_Help_ByFrame()\0"
    "OnMenu_Help_About()\0OnMenu_Help_AVPS_Website()\0"
};

const QMetaObject GUI_Main::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GUI_Main,
      qt_meta_data_GUI_Main, 0 }
};

const QMetaObject *GUI_Main::metaObject() const
{
    return &staticMetaObject;
}

void *GUI_Main::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GUI_Main))
        return static_cast<void*>(const_cast< GUI_Main*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GUI_Main::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnMenu_File_Open_Files(); break;
        case 1: OnMenu_File_Open_Directory(); break;
        case 2: OnMenu_View_Summary(); break;
        case 3: OnMenu_View_ByFrame(); break;
        case 4: OnMenu_View_XML(); break;
        case 5: OnMenu_View_MediaInfo(); break;
        case 6: OnMenu_Verbosity_03(); break;
        case 7: OnMenu_Verbosity_05(); break;
        case 8: OnMenu_Verbosity_10(); break;
        case 9: OnMenu_Debug_MediaInfo_InternalFields(); break;
        case 10: OnMenu_Debug_MediaInfo_RawFieldsNames(); break;
        case 11: OnMenu_Help_Summary(); break;
        case 12: OnMenu_Help_ByFrame(); break;
        case 13: OnMenu_Help_About(); break;
        case 14: OnMenu_Help_AVPS_Website(); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
