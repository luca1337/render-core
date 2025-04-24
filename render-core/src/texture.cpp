#include <texture.h>

#include <logger.h>
#include <utils.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

texture::~texture()
{
    if (m_texture_id != 0)
    {
        glDeleteTextures(1, &m_texture_id);
        m_texture_id = 0;
    }
}

texture::texture(const texture& other)
{
    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glCopyImageSubData(other.m_texture_id, GL_TEXTURE_2D, 0, 0, 0, 0, m_texture_id, GL_TEXTURE_2D, 0, 0, 0, 0, m_width, m_height, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

texture::texture(const std::string &file_path)
{
    int width, height, nrChannels;
    const auto data = stbi_load(file_path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        m_width = width;
        m_height = height;

        const auto format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

        m_texture_id = utils::gl::GenerateOpenGLTexture(m_width, m_height, data, format, format, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

        stbi_image_free(data);
    }
    else
    {
        LOG_CRITICAL("Failed to load texture");
    }
}

texture::texture(unsigned width, unsigned height, color color)
{
    auto data = new unsigned char[width * height * 4];
    if (!data)
    {
        LOG_CRITICAL("Failed to allocate memory for texture data");
        return;
    }

    for (unsigned i = 0; i < width * height; ++i)
    {
        data[i * 4 + 0] = color.r;
        data[i * 4 + 1] = color.g;
        data[i * 4 + 2] = color.b;
        data[i * 4 + 3] = color.a;
    }

    m_texture_id = utils::gl::GenerateOpenGLTexture(width, height, data, GL_RGBA, GL_RGBA, GL_REPEAT, GL_REPEAT, true);

    delete[] data;
}
