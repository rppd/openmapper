#include "shader_library.h"

#include "shader.h"

#include <QFile>

void ShaderLibrary::addShader(Shader* shader) {
    append(shader);
    saveShaderToFile(shader);
}

void ShaderLibrary::addShader(const QString& source, QString name) {
    Shader* shader = new Shader(name);
    shader->compile(source);
    addShader(shader);
}

void ShaderLibrary::saveShaderToFile(const Shader* shader) const {
    QString filename = QFile::encodeName(shader->name() + ".frag");
    QFile file = QFile("shaders/"+filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);
    out << shader->sourceCode();

}

int ShaderLibrary::shaderIndex(QString& name) const {
    for (int i=0; i<size(); i++) {
        if ((*this)[i]->name() == name) return i;
    }
    return -1;
}