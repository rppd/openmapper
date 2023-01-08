#include "glwidget.h"

#include <iostream>

#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <QOpenGLDebugLogger>
#include <math.h>

GLWidget::~GLWidget()
{
    cleanup();
}

void GLWidget::initLogging() {
    logger = new QOpenGLDebugLogger(this);
    logger->initialize();
    connect(logger, &QOpenGLDebugLogger::messageLogged, this, &GLWidget::handleLoggedMessage);
    logger->startLogging();
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(1000, 900);
}

void GLWidget::cleanup()
{
    QObject::disconnect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);
}

void GLWidget::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

    initLogging();

    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);

    printf("GLWidget::initializeGL() : context is %p\n", QOpenGLContext::currentContext());
    
    // QOpenGLShaderProgram* program = new QOpenGLShaderProgram();
    // program->addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/default.vert");
    // program->addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/default.frag");
    // program->link();
    // program->bind();

    // QOpenGLBuffer* vbo = new QOpenGLBuffer();
    // QOpenGLVertexArrayObject* vao = new QOpenGLVertexArrayObject();

    // vbo->create();
    // vao->create();

    // vbo->bind();
    // GLfloat testData[] = { 0,0,0,0, 200,200,0,1, 0,210,1,0 };
    // vbo->allocate(testData, sizeof(testData));

    // GLfloat* data = (GLfloat*) vbo->map(QOpenGLBuffer::Access::ReadOnly);
    // for (int i = 0; i < 3; i++) {
    //     printf("xy(%5.1f, %5.1f) uv(%5.1f,%5.1f) [%d] \n", *data, *(data+1), *(data+2), *(data+3), i);
    //     data += 4;
    // }
    // vbo->unmap();

    // QOpenGLVertexArrayObject::Binder vaoBinder(vao);
    // glEnableVertexAttribArray(0);
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *)(2 * sizeof(GLfloat)));

    // glDrawArrays(GL_TRIANGLES, 0, 12);

    // vbo->release();
    // program->release();
}

void GLWidget::paintGL()
{
    printf("\nOpenGL drawing.\n");

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    printf("GLWidget::paintGL() : context is %p\n", QOpenGLContext::currentContext());
    if (scene != nullptr) scene->draw();

    errorCheck();
}

void GLWidget::errorCheck(std::string marker) {
    GLenum error = GL_NO_ERROR;
    do {
        error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "OpenGL error at " <<  marker << std::endl;
        }
    } while (error != GL_NO_ERROR);
}

void GLWidget::errorCheck() {
    GLenum error = GL_NO_ERROR;
    do {
        error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "OpenGL error" << std::endl;
        }
    } while (error != GL_NO_ERROR);
}

void GLWidget::logErrors() {
    const QList<QOpenGLDebugMessage> messages = logger->loggedMessages();
    for (const QOpenGLDebugMessage &message : messages)
        std::cout << message.message().toStdString() << std::endl;
}

void GLWidget::handleLoggedMessage(QOpenGLDebugMessage msg) {
    std::cout << msg.message().toStdString() << std::endl;
}

void GLWidget::logBuffer(QOpenGLBuffer* buf) {
    // GLfloat* data = (GLfloat*) buf->map(QOpenGLBuffer::ReadOnly);
    // printf("Logging buffer contents (%d): \n", buf->size());
    // for (int i = 0; i < buf->size()/sizeof(GLfloat)/4; i++) {
    //     printf("xy(%5.1f, %5.1f) uv(%5.1f,%5.1f) [%d] \n", *data, *(data+1), *(data+2), *(data+3), i);
    //     data += 4;
    // }
    // buf->unmap();

    printf("Logging buffer contents (%d bytes at %d)): \n", buf->size(), buf->bufferId());
    int count = buf->size()/sizeof(GLfloat);
    GLfloat* data = new GLfloat[count];
    buf->read(0, data, count*sizeof(GLfloat));
    for (int i = 0; i < count/4; i++) {
        printf("xy(%5.1f, %5.1f) uv(%5.1f,%5.1f) [%d] \n", *data, *(data+1), *(data+2), *(data+3), i);
        data += 4;
    }
}

void GLWidget::bindAndLog(QOpenGLBuffer* buf, std::string marker) {
    bool bound = buf->bind();
    if (bound) {
        std::cout << "Bound on " << buf->bufferId() << " at " << marker << std::endl;
    } else {
        std::cout << "Binding failed at "<< marker << std::endl;
    }
}