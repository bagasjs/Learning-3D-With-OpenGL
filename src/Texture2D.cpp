#include "Texture2D.hpp"
#include <glad/glad.h>

Texture2D::Texture2D(const int8_t* data, int width, int height, int channels)
    : m_ID(0), m_DataFormat(0)
{
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
    m_DataFormat = channels == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, m_DataFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &m_ID);
}

void Texture2D::Enable(int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture2D::Update(const int8_t* data, int width, int height)
{
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, m_DataFormat, GL_UNSIGNED_BYTE, data);
}
