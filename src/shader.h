#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLShader>
#include <QString>
#include <QList>

class Shader: public QOpenGLShader {
    public:
        enum UniformType {
            FLOAT,
            VEC2,
            UNSUPPORTED
        };

        struct Uniform {
            QString name;
            Uniform type;
        };

        Shader() {};
        Shader(QString name): _name(name) {};
        void compile(const QString& source);
        void loadUniforms();

        QString name() { return _name; };
        void name(QString name) { _name = name; };

    private:
        QList<Uniform> uniforms;
        QString _name;
        QString _source;

}

#endif