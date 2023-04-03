#include "shader.h"

QString Shader::defaultShaderSource = "#version 330 core"
            "in vec2 vert;"
            "in vec2 uv;"
            "out vec4 FragColor;"
            "void main() { FragColor =  vec4((uv.x+uv.y)/2,0,1,1); };";
Shader Shader::defaultShader = Shader();


void Shader::source(const QString& newSource) {
    qShader->compileSourceCode(newSource);
    uniforms = QList<Uniform>();
    loadUniforms();
    _source = newSource;
}

void Shader::loadUniforms() {
    QOpenGLShaderProgram* testProgram = new QOpenGLShaderProgram();
    testProgram->addShader(qShader);
    GLint count;
    GLint program = testProgram->programId();
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    f->glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &count);

    GLint i;
    GLint size;
    GLenum type;
    const GLsizei bufSize = 64;
    GLchar name[bufSize];
    GLsizei nameSize;
    for (i=0; i<count; i++) {
        f->glGetActiveAttrib(program, (GLuint) i, bufSize, &nameSize, &size, &type, name);
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