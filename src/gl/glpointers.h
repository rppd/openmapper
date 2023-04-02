#ifndef GL_POINTERS_H
#define GL_POINTERS_H

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

struct GLPointers
{
    QOpenGLBuffer *vbo;
    QOpenGLVertexArrayObject *vao;
    QOpenGLShaderProgram *program;
    int vertexCount;
};

#endif
