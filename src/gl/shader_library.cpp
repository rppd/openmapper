#include "shader_library.h"

void ShaderLibrary::loadShaderDir() {
    std::cout << "Loading shader dir" << std::endl;
    QDir shaderDir("shaders/");
    for (const QString& filename: shaderDir.entryList(QDir::Files)) {
        loadShader("shaders/" + filename);
    }
}

void ShaderLibrary::addShader(const Shader& shader) {
    shaders.push_back(shader);
    updated();
}

void ShaderLibrary::saveShaderToFile(const int index) const {
    const Shader& shader = shaders[index];
    QString filename = encodeShaderFilename(shader.name());
    QFile file = QFile(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);
    out << shader.source();
}

int ShaderLibrary::shaderIndex(const QString& name) const {
    for (int i=0; i<size(); i++) {
        if (shaders[i].name() == name) return i;
    }
    return -1;
}

void ShaderLibrary::loadShader(const QString& filename) {
    QFile file = QFile(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QString shaderCode = QTextStream(&file).readAll();
    QString name = decodeShaderFilename(filename);
    addShader(Shader(name,shaderCode));
}

QFile ShaderLibrary::shaderFile(const int index) const {
    return QFile(encodeShaderFilename(shaders[index].name()));
}

QString ShaderLibrary::encodeShaderFilename(const QString& shaderName) const {
    return "shaders/" + QFile::encodeName(shaderName) + ".frag";
}

QString ShaderLibrary::decodeShaderFilename(const QString& filename) const {
    QString name = QFile::decodeName(QByteArray::fromStdString(filename.toStdString()));
    name = name.split('/')[1];
    name = name.split('.')[0];
    return name;
}

void ShaderLibrary::rename(const int index, const QString& name) {
    QFile file = shaderFile(index);
    file.remove();
    shaders[index].name(name);
    saveShaderToFile(index);
    updated();
}

void ShaderLibrary::saveShaderCode(const long unsigned int index, const QString& newSource) {
    Shader& current = shaders[index];
    shaders[index] = Shader(current.name(), newSource);
    saveShaderToFile(index);
    updated();
}