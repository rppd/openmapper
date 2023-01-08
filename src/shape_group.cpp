#include "shape_group.h"

#include "shape.h"
#include "triangle.h"
#include "qopengl.h"
#include "glwidget.h"

#include <stdio.h>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QVector2D>
#include <QPainter>
#include <QMatrix4x4>

void ShapeGroup::build() {
    QOpenGLContext* ctx = QOpenGLContext::currentContext();
    printf("Building group with %d shapes. (%p)\n", (int) shapes.size(), ctx);
    QOpenGLFunctions* f = ctx->functions();
    
    vbo = new QOpenGLBuffer();
    program = new QOpenGLShaderProgram();

    program->create();
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/default.vert");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/default.frag");
    program->link();
    program->bind();

    if (vao.isCreated()) {
        vao.destroy();
        printf("Destroyed \n");
    }
    vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&vao);

    vbo->create();
    vbo->bind();

    vertexCount = 0;
    for (const Shape &shape: shapes) {
        vertexCount += shape.nTriangles()*6;
    }
    GLfloat data[vertexCount*4];
    GLfloat* p = data;
    for (const Shape &shape: shapes) {
        for (const Triangle &triangle: shape.getTriangles()) {
            p = triangle.appendData(p);
        }
    }
    p = data;
    vbo->allocate(data, sizeof(data));

    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
    f->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *)(2 * sizeof(GLfloat)));

    vbo->release();
    program->release();
}

void ShapeGroup::draw() {
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    printf("In Shape::draw(), context is at %p\n", QOpenGLContext::currentContext());

    QOpenGLVertexArrayObject::Binder vaoBinder(&vao);
    program->bind();

    printf("Drawing %d vertices (%p).\n", vertexCount, QOpenGLContext::currentContext());
    f->glDrawArrays(GL_TRIANGLES, 0, vertexCount);
  
    program->release();
}

void ShapeGroup::paint(QPainter* painter) const {
    for (Shape shape: shapes) {
        QList<QVector2D> vectors = shape.getPoints();
        QList<QPointF> points; // = QList(vectors.begin(), vectors.end());
        for (QVector2D vec: vectors) {
            points.append(vec.toPointF());
        }
        painter->drawPolyline(points.data(), points.size());
        painter->drawLine(points.first(), points.last());
    }
}

void ShapeGroup::allocateVBO() const {

}
