#include "shader_library.h"

#include "shader.h"

#include <QFile>

ShaderLibrary::addShader(Shader shader) {
    append(shader);
    saveShaderToFile(shader);
}

ShaderLibrary::addShader(const QString& source, QString name) {
    Shader shader(name);
    shader.compile(source);
    addShader(shader);
}

ShaderLibrary::saveShaderToFile(const Shader& shader) const {
    QString filename = QFile::encodeName(shader.name() + ".frag");
    QFile file = QFile("shaders/"+filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);
    out << shader.sourceCode();

}