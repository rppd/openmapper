#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QVector2D>
#include <qopengl.h>

class Triangle {
    public:
        Triangle(QVector2D v1, QVector2D v2, QVector2D v3);

        GLfloat* appendData(GLfloat*) const;
    private:
        QVector2D positions[3];
        constexpr static QVector2D uvs[] = {
            QVector2D(0,0),
            QVector2D(1,0),
            QVector2D(0,1)
        };
};

#endif