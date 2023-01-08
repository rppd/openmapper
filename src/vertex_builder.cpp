#include "vertex_builder.h"

#include <qopengl.h>
#include <qmath.h>
#include <QVector2D>

VertexSampler::VertexSampler(int vertexCount) {
    resize(vertexCount);
}

void VertexSampler::add(const QVector2D pos, const QVector2D uv)
{
    GLfloat *p = list.data() + list_size;
    *p++ = pos.x();
    *p++ = pos.y();
    *p++ = uv.x();
    *p++ = uv.y();
    list_size += 4;
}

void VertexSampler::addTriangle(const QVector2D v1, const QVector2D v2, const QVector2D v3) {
    add(v1, QVector2D(0,0));
    add(v2, QVector2D(1,0));
    add(v3, QVector2D(0,1));

    add(v1, QVector2D(0,0));
    add(v3, QVector2D(1,0));
    add(v2, QVector2D(0,1));
}

void VertexSampler::resize(int vertexCount) {
    list.resize(4*vertexCount); 
}

VertexSampler VertexSampler::triangleExampleSampler() {
    VertexSampler sampler = VertexSampler();
    sampler.resize(2 * 6);

    QVector2D v1(0,0);
    QVector2D v2(0,.5);
    QVector2D v3(1,0);
    QVector2D v4(1,1);

    sampler.addTriangle(v1, v3, v2);
    sampler.addTriangle(v2, v3, v4);
    return sampler;
}