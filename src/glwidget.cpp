#include "glwidget.h"

#include <iostream>
#include <math.h>

#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <QOpenGLDebugLogger>
#include <QDateTime>

GLWidget::~GLWidget() {
    cleanup();
}

void GLWidget::initLogging() {
    logger = new QOpenGLDebugLogger(this);
    logger->initialize();
    connect(logger, &QOpenGLDebugLogger::messageLogged, this, &GLWidget::handleLoggedMessage);
    logger->startLogging();
}

QSize GLWidget::minimumSizeHint() const {
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const {
    return QSize(1000, 900);
}

void GLWidget::cleanup() {
    QObject::disconnect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);
}

void GLWidget::initializeGL() {
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);
    initLogging();
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GLWidget::onTimer);
    timer->setInterval(31);
    timer->start();
    ctx = QOpenGLContext::currentContext();
}

void GLWidget::paintGL() {
    ctx->makeCurrent(ctx->surface());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    for (const GLPointers& pointers : glPointers) {
        draw(pointers);
    }
    logErrors();
}

void GLWidget::errorCheck(std::string marker) {
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    GLenum error = GL_NO_ERROR;
    do {
        error = f->glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "OpenGL error at " << marker << std::endl;
        }
    } while (error != GL_NO_ERROR);
}

void GLWidget::errorCheck() {
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    GLenum error = GL_NO_ERROR;
    do {
        error = f->glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "OpenGL error" << std::endl;
        }
    } while (error != GL_NO_ERROR);
}

void GLWidget::logErrors() {
    const QList<QOpenGLDebugMessage> messages = logger->loggedMessages();
    for (const QOpenGLDebugMessage& message : messages)
        std::cout << message.message().toStdString() << std::endl;
}

void GLWidget::handleLoggedMessage(QOpenGLDebugMessage msg) {
    std::cout << msg.message().toStdString() << std::endl;
}

void GLWidget::logBuffer(QOpenGLBuffer* buf) {
    printf("Logging buffer contents (%d bytes at %d)): \n", buf->size(), buf->bufferId());
    int count = buf->size() / sizeof(GLfloat);
    GLfloat* data = new GLfloat[count];
    buf->read(0, data, count * sizeof(GLfloat));
    for (int i = 0; i < count / 4; i++) {
        printf("xy(%5.1f, %5.1f) uv(%5.1f,%5.1f) [%d] \n", *data, *(data + 1), *(data + 2), *(data + 3), i);
        data += 4;
    }
}

void GLWidget::bindAndLog(QOpenGLBuffer* buf, std::string marker) {
    bool bound = buf->bind();
    if (bound) {
        std::cout << "Bound on " << buf->bufferId() << " at " << marker << std::endl;
    }
    else {
        std::cout << "Binding failed at " << marker << std::endl;
    }
}

void GLWidget::onTimer() {
    update();
}

void GLWidget::draw(const GLPointers& p) const {
    QSize viewportSize = size();

    QMatrix4x4 transform;
    transform.setToIdentity();
    transform.viewport(0, 0, viewportSize.width(), viewportSize.height());
    transform.scale(1, -1, 1);
    transform = transform.inverted();

    int ms = QDateTime::currentMSecsSinceEpoch();
    float t = 0.001f * (float)ms;
    printf("%f\n", t);

    QOpenGLContext* ctx = context();
    ctx->makeCurrent(ctx->surface());
    QOpenGLFunctions* f = ctx->functions();

    p.vbo->bind();
    QOpenGLVertexArrayObject::Binder vaoBinder(p.vao);
    p.program->bind();

    p.program->setUniformValue("transform", transform);
    p.program->setUniformValue("t", t);

    f->glDrawArrays(GL_TRIANGLES, 0, p.vertexCount);
    p.program->release();
    p.vbo->release();
    vaoBinder.release();
}