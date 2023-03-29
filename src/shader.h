#ifndef SHADER_H
#define SHADER_H

#include <qopengl.h>

#include <QOpenGLShader>
#include <QOpenGLFunctions>
#include <QString>
#include <QList>
#include <QOpenGLShaderProgram>

class Shader: public QOpenGLShader {
    public:
        enum UniformType {
            FLOAT,
            VEC2,
            UNSUPPORTED
        };

        struct Uniform {
            QString name;
            UniformType type;
        };

        Shader(): QOpenGLShader(QOpenGLShader::Fragment) {};
        Shader(QString name): QOpenGLShader(QOpenGLShader::Fragment), _name(name) {};
        void compile(const QString& source);
        void loadUniforms();

        QString name() const { return _name; };
        void name(QString name) { _name = name; };

    private:
        QList<Uniform> uniforms;
        QString _name;
        QString _source;

};

#endif