# Auto-generated by IDE. Any changes made by user will be lost!
BASEDIR =  $$quote($$_PRO_FILE_PWD_)

device {
    CONFIG(debug, debug|release) {
        INCLUDEPATH +=  $$quote(${QNX_TARGET}/usr/include/cpp) \
                 $$quote(${QNX_TARGET}/usr/include/qt4) \
                 $$quote(${QNX_TARGET}/usr/include/cpp/embedded) \
                 $$quote(${QNX_TARGET}/usr/include/cpp/c) \
                 $$quote(${QNX_TARGET}/../target-override/usr/include) \
                 $$quote(${QNX_TARGET}/usr/include/qt4/QtCore)

        DEPENDPATH +=  $$quote(${QNX_TARGET}/usr/include/cpp) \
                 $$quote(${QNX_TARGET}/usr/include/qt4) \
                 $$quote(${QNX_TARGET}/usr/include/cpp/embedded) \
                 $$quote(${QNX_TARGET}/usr/include/cpp/c) \
                 $$quote(${QNX_TARGET}/../target-override/usr/include) \
                 $$quote(${QNX_TARGET}/usr/include/qt4/QtCore)

        SOURCES +=  $$quote($$BASEDIR/src/AlbumPic.cpp) \
                 $$quote($$BASEDIR/src/abstractloader.cpp) \
                 $$quote($$BASEDIR/src/albumloader.cpp) \
                 $$quote($$BASEDIR/src/app.cpp) \
                 $$quote($$BASEDIR/src/imageloader.cpp) \
                 $$quote($$BASEDIR/src/imageprocessor.cpp) \
                 $$quote($$BASEDIR/src/main.cpp)

        HEADERS +=  $$quote($$BASEDIR/src/AlbumPic.h) \
                 $$quote($$BASEDIR/src/abstractloader.hpp) \
                 $$quote($$BASEDIR/src/albumloader.hpp) \
                 $$quote($$BASEDIR/src/app.hpp) \
                 $$quote($$BASEDIR/src/imageloader.hpp) \
                 $$quote($$BASEDIR/src/imageprocessor.hpp)
    }

    CONFIG(release, debug|release) {
        INCLUDEPATH +=  $$quote(${QNX_TARGET}/usr/include/cpp) \
                 $$quote(${QNX_TARGET}/usr/include/qt4) \
                 $$quote(${QNX_TARGET}/usr/include/cpp/embedded) \
                 $$quote(${QNX_TARGET}/usr/include/cpp/c) \
                 $$quote(${QNX_TARGET}/../target-override/usr/include) \
                 $$quote(${QNX_TARGET}/usr/include/qt4/QtCore)

        DEPENDPATH +=  $$quote(${QNX_TARGET}/usr/include/cpp) \
                 $$quote(${QNX_TARGET}/usr/include/qt4) \
                 $$quote(${QNX_TARGET}/usr/include/cpp/embedded) \
                 $$quote(${QNX_TARGET}/usr/include/cpp/c) \
                 $$quote(${QNX_TARGET}/../target-override/usr/include) \
                 $$quote(${QNX_TARGET}/usr/include/qt4/QtCore)

        SOURCES +=  $$quote($$BASEDIR/src/AlbumPic.cpp) \
                 $$quote($$BASEDIR/src/abstractloader.cpp) \
                 $$quote($$BASEDIR/src/albumloader.cpp) \
                 $$quote($$BASEDIR/src/app.cpp) \
                 $$quote($$BASEDIR/src/imageloader.cpp) \
                 $$quote($$BASEDIR/src/imageprocessor.cpp) \
                 $$quote($$BASEDIR/src/main.cpp)

        HEADERS +=  $$quote($$BASEDIR/src/AlbumPic.h) \
                 $$quote($$BASEDIR/src/abstractloader.hpp) \
                 $$quote($$BASEDIR/src/albumloader.hpp) \
                 $$quote($$BASEDIR/src/app.hpp) \
                 $$quote($$BASEDIR/src/imageloader.hpp) \
                 $$quote($$BASEDIR/src/imageprocessor.hpp)
    }
}

simulator {
    CONFIG(debug, debug|release) {
        INCLUDEPATH +=  $$quote(${QNX_TARGET}/usr/include/cpp) \
                 $$quote(${QNX_TARGET}/usr/include/qt4) \
                 $$quote(${QNX_TARGET}/usr/include/cpp/embedded) \
                 $$quote(${QNX_TARGET}/usr/include/cpp/c) \
                 $$quote(${QNX_TARGET}/../target-override/usr/include) \
                 $$quote(${QNX_TARGET}/usr/include/qt4/QtCore)

        DEPENDPATH +=  $$quote(${QNX_TARGET}/usr/include/cpp) \
                 $$quote(${QNX_TARGET}/usr/include/qt4) \
                 $$quote(${QNX_TARGET}/usr/include/cpp/embedded) \
                 $$quote(${QNX_TARGET}/usr/include/cpp/c) \
                 $$quote(${QNX_TARGET}/../target-override/usr/include) \
                 $$quote(${QNX_TARGET}/usr/include/qt4/QtCore)

        SOURCES +=  $$quote($$BASEDIR/src/AlbumPic.cpp) \
                 $$quote($$BASEDIR/src/abstractloader.cpp) \
                 $$quote($$BASEDIR/src/albumloader.cpp) \
                 $$quote($$BASEDIR/src/app.cpp) \
                 $$quote($$BASEDIR/src/imageloader.cpp) \
                 $$quote($$BASEDIR/src/imageprocessor.cpp) \
                 $$quote($$BASEDIR/src/main.cpp)

        HEADERS +=  $$quote($$BASEDIR/src/AlbumPic.h) \
                 $$quote($$BASEDIR/src/abstractloader.hpp) \
                 $$quote($$BASEDIR/src/albumloader.hpp) \
                 $$quote($$BASEDIR/src/app.hpp) \
                 $$quote($$BASEDIR/src/imageloader.hpp) \
                 $$quote($$BASEDIR/src/imageprocessor.hpp)
    }
}

INCLUDEPATH +=  $$quote($$BASEDIR/src)

lupdate_inclusion {
    SOURCES +=  $$quote($$BASEDIR/../src/*.c) \
             $$quote($$BASEDIR/../src/*.c++) \
             $$quote($$BASEDIR/../src/*.cc) \
             $$quote($$BASEDIR/../src/*.cpp) \
             $$quote($$BASEDIR/../src/*.cxx) \
             $$quote($$BASEDIR/../assets/*.qml) \
             $$quote($$BASEDIR/../assets/*.js) \
             $$quote($$BASEDIR/../assets/*.qs)

    HEADERS +=  $$quote($$BASEDIR/../src/*.h) \
             $$quote($$BASEDIR/../src/*.h++) \
             $$quote($$BASEDIR/../src/*.hh) \
             $$quote($$BASEDIR/../src/*.hpp) \
             $$quote($$BASEDIR/../src/*.hxx)
}

TRANSLATIONS =  $$quote($${TARGET}.ts)
