#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <qopengl.h>

#include <QVector2D>
#include <QPolygonF>

class Triangle {
    public:
        Triangle(QVector2D v1, QVector2D v2, QVector2D v3);
        GLfloat* appendData(GLfloat*) const;
        
        QList<QVector2D> getPoints() { return QList({ points[0], points[1], points[2], points[0] }); }
        QPolygonF getPolygonF() const;

        bool pointInside(const QVector2D& point) const;
        float grade() const;
         
    private:
        QVector2D points[3];
        constexpr static QVector2D uvs[] = {
            QVector2D(0,0),
            QVector2D(1,0),
            QVector2D(0,1)
        };
};

#endif