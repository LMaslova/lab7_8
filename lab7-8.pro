QT += gui sql widgets core
CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
        database.cpp \
        extern/googletest/googletest/src/gtest-all.cc \
        extern/googletest/googletest/src/gtest-death-test.cc \
        extern/googletest/googletest/src/gtest-filepath.cc \
        extern/googletest/googletest/src/gtest-matchers.cc \
        extern/googletest/googletest/src/gtest-port.cc \
        extern/googletest/googletest/src/gtest-printers.cc \
        extern/googletest/googletest/src/gtest-test-part.cc \
        extern/googletest/googletest/src/gtest-typed-test.cc \
        extern/googletest/googletest/src/gtest.cc \
        main.cpp \
        mainwindow.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    lab7.pro

FORMS += \
    mainwindow.ui

DISTFILES += \
    lab7-8.pro.user

HEADERS += \
    database.h \
    mainwindow.h

INCLUDEPATH += \
    $$PWD/extern/googletest/googletest \
    $$PWD/extern/googletest/googletest/include \
    $$PWD/extern/googletest/googlemock \
    $$PWD/extern/googletest/googlemock/include
