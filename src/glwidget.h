#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "scene.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLDebugLogger>
#include <QMatrix4x4>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{

public:
    GLWidget(): QOpenGLWidget(), QOpenGLFunctions() {};
    GLWidget(Scene* p_scene): QOpenGLWidget(), QOpenGLFunctions(), scene(p_scene) {};
    GLWidget(QWidget* parent): QOpenGLWidget(parent), QOpenGLFunctions() {};
    GLWidget(QWidget* parent, Scene* p_scene): QOpenGLWidget(parent), QOpenGLFunctions(), scene(p_scene) {};
    ~GLWidget();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void errorCheck(std::string marker);
    void errorCheck();
    void logErrors();
    void initLogging();
    
    static void logBuffer(QOpenGLBuffer* vbo);
    static void bindAndLog(QOpenGLBuffer* buf, std::string marker="<no marker>");

public slots:
    void cleanup();
    void handleLoggedMessage(QOpenGLDebugMessage msg);

protected:
    void initializeGL() override;
    void paintGL() override;

private:
    // std::string loadShaderSource(std::string filename);

    int vertexCount;
    QOpenGLDebugLogger* logger;
    QMatrix4x4 transform;
    Scene* scene;
};

#endif
