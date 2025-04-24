#include <post_processing.h>

#include <utils.h>

post_processing::post_processing(const window& window) : m_Window(window)
{
    const auto quadVertices = std::vector<float>
    {
        -1.0f, -1.0f,  0.0f, 0.0f,
        -1.0f, 1.0f,  0.0f, 1.0f,
         1.0f, 1.0f,  1.0f, 1.0f,

        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, 1.0f,  1.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f
    };

    utils::gl::GenerateVertexBuffer(m_vao, m_vbo, quadVertices);
    utils::gl::UploadVertexAttribute(0, 2, 4 * sizeof(float), 0, nullptr);
    utils::gl::UploadVertexAttribute(1, 2, 4 * sizeof(float), 1, reinterpret_cast<void*>(2 * sizeof(float)));

    const auto width = m_Window.props().width;
    const auto height = m_Window.props().height;

    utils::gl::GenerateFrameBufferObject(width, height, m_fbo, m_texture_color_buffer);
}