#ifndef SHADER_H
#define SHADER_H

#include <qopengl.h>
#include <iostream>

#include <QOpenGLShader>
#include <QOpenGLFunctions>
#include <QString>
#include <QList>
#include <QOpenGLShaderProgram>

class Shader {
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

        Shader() {};
        Shader(QString aname): _name(aname) {};
        Shader(QString aname, QString asource): _name(aname), _source(asource) {};

        void loadUniforms();
        void source(const QString& newSource);
        QString source() const { return _source; };

        QString name() const { return _name; };
        void name(QString name) { _name = name; };

    private:
        QOpenGLShader* qShader = new QOpenGLShader(QOpenGLShader::Fragment); //has to be a pointer because Qt disabled copy of QOpenGLShader (and wants it to be a poinbter)
        QList<Uniform> uniforms;
        QString _name;
        QString _source;

};

#endif