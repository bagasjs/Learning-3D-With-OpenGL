#include "Shader.hpp"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

int Shader::GetUniformLocation(const std::string& name) const
{
    int location = glGetUniformLocation(m_ID, name.c_str());
    return location;
}

void Shader::SetUniform(const std::string& name, Type type, int count, const void* data, bool transponse)
{
    int location = GetUniformLocation(name);
    switch (type) {
        case Type::FLOAT: glUniform1fv(location, count, (float*)data); break;
        case Type::VEC2: glUniform2fv(location, count, (float*)data); break;
        case Type::VEC3: glUniform3fv(location, count, (float*)data); break;
        case Type::VEC4: glUniform4fv(location, count, (float*)data); break;
        case Type::INT: glUniform1iv(location, count, (int*)data); break;
        case Type::IVEC2: glUniform2iv(location, count, (int*)data); break;
        case Type::IVEC3: glUniform3iv(location, count, (int*)data); break;
        case Type::IVEC4: glUniform4iv(location, count, (int*)data); break;
        case Type::MAT3: glUniformMatrix3fv(location, count, transponse ? GL_TRUE : GL_FALSE, (float*)data); break;
        case Type::MAT4: glUniformMatrix4fv(location, count, transponse ? GL_TRUE : GL_FALSE, (float*)data); break;
    }
}

Shader::Shader(const std::string& vertSrc, const std::string& fragSrc)
    : m_Error(false)
{
    uint32_t vertModule = 0, fragModule = 0;
    vertModule = LoadModule(GL_VERTEX_SHADER, vertSrc);
    if(!m_Error) {
        fragModule = LoadModule(GL_FRAGMENT_SHADER, fragSrc);
        if(!m_Error) {
            m_ID = glCreateProgram();
            glAttachShader(m_ID, vertModule);
            glAttachShader(m_ID, fragModule);
            glLinkProgram(m_ID);
            int success;
            glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
            if(!success) {
                char infoLog[512];
                m_Error = true;
                glGetProgramInfoLog(m_ID, sizeof(infoLog), NULL, infoLog);
                m_Reason.append(infoLog);
            }
            glDeleteShader(fragModule);
        }
        glDeleteShader(vertModule);
    }
}

Shader::~Shader()
{
    glDeleteProgram(m_ID);
}

uint32_t Shader::LoadModule(int type, const std::string& source)
{
    const char* realSrc = source.c_str();
    uint32_t module = glCreateShader(type);
    glShaderSource(module, 1, &realSrc, NULL);
    glCompileShader(module);

    int success = 0;
    glGetShaderiv(module, GL_COMPILE_STATUS, &success);
    if(!success) {
        char infoLog[512];
        m_Error = true;
        glGetShaderInfoLog(module, sizeof(infoLog), NULL, infoLog);
        m_Reason.append(infoLog);
        return 0;
    }

    return module;
}

Shader Shader::CreateFromFile(const std::string& vertSrcPath, const std::string& fragSrcPath)
{
    std::string vertSrc = LoadFileData(vertSrcPath);
    std::string fragSrc = LoadFileData(fragSrcPath);
    return Shader(vertSrc, fragSrc);
}

std::string LoadFileData(const std::string& filepath) 
{
    std::ifstream f(filepath);
    std::stringstream ss;
    std::string tmp;
    while(!f.eof()) {
        std::getline(f, tmp);
        ss << tmp << std::endl;
    }
    return ss.str();
}

