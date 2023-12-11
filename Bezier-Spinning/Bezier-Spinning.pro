QT += quick core gui widgets

SOURCES += \
        Algorithms.cpp \
        BezierCurve.cpp \
        Circle.cpp \
        ImageProvider.cpp \
        PascalTriangle.cpp \
        SceneManager.cpp \
        main.cpp

resources.files = main.qml 
resources.prefix = /$${TARGET}
RESOURCES += resources

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Algorithms.h \
    BezierCurve.h \
    Circle.h \
    Enums.h \
    ImageProvider.h \
    PascalTriangle.h \
    SceneManager.h
