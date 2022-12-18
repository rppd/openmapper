HEADERS = src/glwidget.h src/logo.h src/mainwindow.h src/window.h
SOURCES = src/glwidget.cpp src/logo.cpp src/mainwindow.cpp src/window.cpp src/main.cpp

DESTDIR = ./bin
MOC_DIR = ./moc
OBJECTS_DIR = ./objects
RCC_DIR = ./resource

QT += widgets opengl openglwidgets

# install
target.path = build/openmapper
INSTALLS += target
