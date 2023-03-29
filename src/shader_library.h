#ifndef SHADER_LIBRARY_H
#define SHADER_LIBRARY

#include <QList>
#include <QString>
#include <QOpenGLShader>

class ShaderLibrary: public QList<QOpenGLShader> {

    public:
        ShaderLibrary();

        void addShader(QOpenGLShader shader);
        int shaderIndex(QString name) const;

    private:
        void saveShaderToFile(const QOpenGLShader& shader) const;

}

#endif