#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLDebugLogger>
#include <QMatrix4x4>
#include <QTimer>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{

public:
    struct GLPointers
    {
        QOpenGLBuffer *vbo;
        QOpenGLVertexArrayObject *vao;
        QOpenGLShaderProgram *program;
        int vertexCount;
    };

    GLWidget() : QOpenGLWidget(), QOpenGLFunctions(){};
    GLWidget(QWidget *parent) : QOpenGLWidget(parent), QOpenGLFunctions(){};
    ~GLWidget();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void logErrors();
    void initLogging();
    void onTimer();
    // void build();
    void draw(const GLPointers &p) const;
    void registerPointers(const QList<GLPointers> p) { glPointers = p; };

    static void logBuffer(QOpenGLBuffer *vbo);
    static void bindAndLog(QOpenGLBuffer *buf, std::string marker = "<no marker>");
    static void errorCheck(std::string marker);
    static void errorCheck();

public slots:
    void cleanup();
    void handleLoggedMessage(QOpenGLDebugMessage msg);

protected:
    void initializeGL() override;
    void paintGL() override;

private:
    // std::string loadShaderSource(std::string filename);

    QOpenGLDebugLogger *logger;
    QTimer *timer;
    QOpenGLContext *ctx; // TODO remove, replace using QOpenGLWidget::context()

    QList<GLPointers> glPointers;
    QList<int> vertexCounts;
};

#endif
