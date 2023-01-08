HEADERS = src/*.h
SOURCES = src/*.cpp
        

DESTDIR = ./bin
MOC_DIR = ./moc
OBJECTS_DIR = ./objects
RCC_DIR = ./resource

QT += widgets opengl openglwidgets

# install
target.path = build/openmapper
INSTALLS += target
