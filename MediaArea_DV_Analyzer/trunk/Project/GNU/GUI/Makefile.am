AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = dvanalyzer-gui
dvanalyzer_gui_SOURCES = \
    ../../../Source/Common/Help.cpp \
    ../../../Source/Common/Core.cpp \
    ../../../Source/GUI/Common/GUI_Main_Common_Core.cpp \
    ../../../Source/GUI/WxWidgets/App.cpp \
    ../../../Source/GUI/WxWidgets/GUI_About.cpp \
    ../../../Source/GUI/WxWidgets/GUI_Help_ByFrame.cpp \
    ../../../Source/GUI/WxWidgets/GUI_Help_Summary.cpp \
    ../../../Source/GUI/WxWidgets/GUI_Main.cpp \
    ../../../Source/GUI/WxWidgets/GUI_Main.rc \
    ../../../Source/GUI/WxWidgets/GUI_Main_FileDrop.cpp \
    ../../../Source/GUI/WxWidgets/GUI_Main_Menu.cpp \
    ../../../Source/GUI/WxWidgets/GUI_Main_Text.cpp \
    ../../../Source/GUI/WxWidgets/GUI_Main_Text_ByFrame.cpp \
    ../../../Source/GUI/WxWidgets/GUI_Main_Text_MediaInfo.cpp \
    ../../../Source/GUI/WxWidgets/GUI_Main_Text_Summary.cpp

#dvanalyzer-gui_LDFLAGS     = -no-undefined -version-info 0:0:0

INCLUDES = -I../../../Source -I../../../../MediaInfoLib/Source -I../../../../ZenLib/Source