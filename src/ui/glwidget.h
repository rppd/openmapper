#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "../geometry/scene.h"
#include "../gl/glpointers.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QTimer>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:

    GLWidget(Scene& scene): QOpenGLWidget(), QOpenGLFunctions(), _scene(scene) { };
    GLWidget(QWidget *parent, Scene& scene) : QOpenGLWidget(parent), QOpenGLFunctions(), _scene(scene) { };
    ~GLWidget();
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void logErrors();
    void initLogging();
    void onTimer();
    void draw() const;
    void draw(const GLPointers& pointers) const;

    Scene& scene() const { return _scene; };
    void scene(Scene& scene) { _scene = scene; };

    static void logBuffer(QOpenGLBuffer *vbo);
    static void bindAndLog(QOpenGLBuffer *buf, std::string marker = "<no marker>");
    static void errorCheck(std::string marker);
    static void errorCheck();

public slots:
    void cleanup();
    void handleLoggedMessage(QOpenGLDebugMessage msg);

signals:
    void glReady();

protected:
    void initializeGL() override;
    void paintGL() override;

private:
    // std::string loadShaderSource(std::string filename);

    QOpenGLDebugLogger *logger;
    QTimer *timer;
    QOpenGLContext *ctx; // TODO remove, replace using QOpenGLWidget::context()
    Scene& _scene;

};

#endif
