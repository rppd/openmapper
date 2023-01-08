#ifndef VERTEX_BUILDER_H
#define VERTEX_BUILDER_H

#include <qmath.h>
#include <qopengl.h>
#include <QList>
#include <QVector3D>

class VertexSampler {

public:
    VertexSampler() {};
    VertexSampler(int vertexCount);

    int size() const { return list_size; }
    int vertexCount() const { return list_size/4; };
    const GLfloat* constData() const { return list.constData(); };
    static VertexSampler triangleExampleSampler();

    void addTriangle(const QVector2D v1, const QVector2D v2, const QVector2D v3);
    void resize(int vertexCount);
private:
    int list_size = 0;
    QList<GLfloat> list;

    void add(QVector2D pos, QVector2D uv);
};

#endif