#include "triangle.h"

#include <QDebug>

Triangle::Triangle(QVector2D v1, QVector2D v2, QVector2D v3) {
    points[0] = v1;
    points[1] = v2;
    points[2] = v3;
}

GLfloat* Triangle::appendData(GLfloat* p) const {
    for (int i = 0; i<3; i++) {
        *p++ = points[i].x();
        *p++ = points[i].y();
        *p++ = uvs[i].x();
        *p++ = uvs[i].y();
    }
    for (int i = 2; i>=0; i--) {
        *p++ = points[i].x();
        *p++ = points[i].y();
        *p++ = uvs[i].x();
        *p++ = uvs[i].y();
    }
    return p;
}

float Triangle::grade() const { //for meshing
    float a = (points[0] - points[1]).length();
    float b = (points[1] - points[2]).length();
    float c = (points[2] - points[0]).length();
    
    float half_p = (a+b+c)/2;
    float surface = sqrt(half_p*(half_p-a)*(half_p-b)*(half_p-c));
    float r_in = surface/half_p;
    float r_out = (a*b*c)/(3*surface);
    return r_in/r_out;
}

QPolygonF Triangle::getPolygonF() const {
    QList<QPointF> pointsF;
    for (QVector2D point: points) {
        pointsF.append(point.toPointF());
    }
    return QPolygonF(pointsF);
}

bool Triangle::pointInside(const QVector2D& point) const {
    for (int i=0; i<3; i++) {
        QVector2D p1 = points[i];
        QVector2D p2 = points[(i+1)%3];
        QVector2D side = p2-p1;
        QVector2D normal(-side.y(),side.x()); //to the outside, assuming counter-clockwise points
        QVector2D to_point = point-p1;
        if (QVector2D::dotProduct(normal, to_point) >= 0) return false;
    }
    return true;
}