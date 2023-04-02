HEADERS = src/geometry/*.h \
        src/gl/*.h \
        src/ui/*.h 
SOURCES = src/*.cpp \
        src/geometry/*.cpp \
        src/gl/*.cpp \
        src/ui/*.cpp

DESTDIR = ./bin
MOC_DIR = ./moc
OBJECTS_DIR = ./objects
RCC_DIR = ./resource

QT += widgets opengl openglwidgets

# install
target.path = build/openmapper
INSTALLS += target
