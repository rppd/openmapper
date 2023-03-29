#ifndef SHADER_LIBRARY_H
#define SHADER_LIBRARY

#include <QList>
#include <QString>
#include <QOpenGLShader>

#include "shader.h"

class ShaderLibrary: public QList<Shader*> {

    public:
        ShaderLibrary();

        void addShader(Shader* shader);
        void addShader(const QString& source, QString name);
        int shaderIndex(QString& name) const;

    private:
        void saveShaderToFile(const Shader* shader) const;

};

#endif