#include "shape_group.h"

#include <iostream>
#include <cmath>

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QVector2D>
#include <QPainter>
#include <QMatrix4x4>
#include <QDateTime>

GLWidget::GLPointers ShapeGroup::build(QOpenGLContext* ctx) const {
    ctx->makeCurrent(ctx->surface());
    QOpenGLFunctions* f = ctx->functions();

    QOpenGLVertexArrayObject* vao = new QOpenGLVertexArrayObject();
    QOpenGLBuffer* vbo = new QOpenGLBuffer();
    QOpenGLShaderProgram* program = new QOpenGLShaderProgram();

    program->create();
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/default.vert");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/stripes.frag");
    program->link();
    program->bind();

    vao->create();
    QOpenGLVertexArrayObject::Binder vaoBinder(vao);

    vbo->create();
    vbo->bind();

    int vCount = vertexCount();
    GLfloat data[vCount*4];
    GLfloat* p = data;
    for (const Shape &shape: *this) {
        for (const Triangle &triangle: shape.getTriangles()) {
            p = triangle.appendData(p);
        }
    }
    vbo->allocate(data, sizeof(data));

    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
    f->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *)(2 * sizeof(GLfloat)));

    vbo->release();
    program->release();

    GLWidget::GLPointers pointers = { vbo, vao, program, vCount };
    return pointers;
}

void ShapeGroup::paint(QPainter* painter) const {
    for (Shape shape: *this) {
        QList<QVector2D> vectors = shape.getPoints();
        QList<QPointF> points; // = QList(vectors.begin(), vectors.end());
        for (QVector2D vec: vectors) points.append(vec.toPointF());
        painter->drawPolyline(points.data(), points.size());
        painter->drawLine(points.first(), points.last());
    }
}

int ShapeGroup::vertexCount() const {
    int count = 0;
    for (const Shape &shape: *this) {
        count += shape.nTriangles()*6;
    }
    return count;
}

void ShapeGroup::allocateVBO() const {

}
