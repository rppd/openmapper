#include "shader.h"

#include <qopengl.h>

#include "QOpenGLShaderProgram"

void Shader::compile(const QString& source) {
    compileFormSource(source);
    uniforms = QList<Uniform>();
    loadUniforms();
    _source = source;
}

void Shader::loadUniforms() {
    QOpenGLShaderProgram* testProgram = new QOpenGLShaderProgram();
    testProgram->addShader(QOpenGLShader::Fragmet, this);
    GLint count;
    GLint program = program->programId();
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &count);

    GLint i;
    GLint size;
    GLenum type;
    const GLsizei bufSize = 64;
    GLchar name[bufSize];
    GLsizei nameSize;
    for (i=0; i<count; i++) {
        getGetActiveAttrib(program, (GLunit) i, bufSize, &nameSize, &size, &type, name);
        Uniform uniform;
        switch (type) {
            case GL_FLOAT:
                uniform.type = UniformType::FLOAT;
                break;
            case GL_FLOAT_VEC2:
                uniform.type = UniformType::VEC2;
                break;
            default:
                uniform.type = UniformType::UNSUPPORTED;
                break;
        }
        uniform.name = QString(name);
        uniforms.append(uniform);
    }
}