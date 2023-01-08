#include "triangle.h"

Triangle::Triangle(QVector2D v1, QVector2D v2, QVector2D v3) {
    positions[0] = v1;
    positions[1] = v2;
    positions[2] = v3;
}

GLfloat* Triangle::appendData(GLfloat* p) const {
    for (int i = 0; i<3; i++) {
        *p++ = positions[i].x();
        *p++ = positions[i].y();
        *p++ = uvs[i].x();
        *p++ = uvs[i].y();
    }
    for (int i = 2; i>=0; i--) {
        *p++ = positions[i].x();
        *p++ = positions[i].y();
        *p++ = uvs[i].x();
        *p++ = uvs[i].y();
    }
    return p;
}