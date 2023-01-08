QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    credit_c_a.cpp \
    credit_calculator.cpp \
    graphics.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    ../s21_credit_calculator.c \
    ../s21_parcer.c \
    ../s21_stack.c

HEADERS += \
    credit_c_a.h \
    credit_calculator.h \
    graphics.h \
    mainwindow.h \
    qcustomplot.h \
    ../s21_calculate.h

FORMS += \
    credit_c_a.ui \
    credit_calculator.ui \
    graphics.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
