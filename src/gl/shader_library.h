#ifndef SHADER_LIBRARY_H
#define SHADER_LIBRARY_H

#include "shader.h"

#include <QList>
#include <QString>
#include <QOpenGLShader>
#include <QFile>
#include <QDir>

#include <iostream>

class ShaderLibrary: public QObject {
    Q_OBJECT

    public:
        ShaderLibrary() {};

        void addShader(const Shader& shader);
        Shader& at(const int i) { return shaders.at(i); };
        Shader* data() { return shaders.data(); };
        int size() const { return shaders.size(); };
        int shaderIndex(const QString& name) const;
        
        void saveShaderCode(const long unsigned int index, const QString& newSource);
        void rename(const int index, const QString& name);
        void destroy(const int index);
        
    signals:
        void updated();

    public slots:
        void loadShaderDir();

    private:
        std::vector<Shader> shaders = std::vector<Shader>(0);

        void saveShaderToFile(const int index) const;
        void loadShader(const QString& filename);
        QFile shaderFile(const int index) const;

        QString encodeShaderFilename(const QString& shaderName) const;
        QString decodeShaderFilename(const QString& filename) const;

};

#endif