#pragma once

#include <color.h>

#include <tuple>
#include <string>

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <export.h>

class RENDER_API texture
{
public:
	/**
	 * \brief Class destructor
	 */
	~texture();

	/**
	 * \brief Class custom copy-constructor
	 */
	texture(const texture&);

	/**
	 * \brief Load texture from path (.jpg, .png. etc..)
	 * \param file_path where is the texture located?
	 */
	explicit texture(const std::string &file_path);

	/**
	 * \brief Create a raw texture from memory with a color, width and height
	 * \param width width in pixels
	 * \param height height in pixels
	 * \param color color of the texture
	 */
	texture(unsigned width, unsigned height, color color);

	/**
	 * \brief Get ID associated to this texture
	 */
	auto get_id() const { return m_texture_id; }

	auto get_width() const { return m_width; }
	auto get_height() const { return m_height; }

private:
	GLuint m_texture_id = {};
	unsigned m_width = {};
	unsigned m_height = {};
};