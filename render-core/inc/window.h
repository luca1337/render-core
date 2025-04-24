#pragma once

#include <functional>
#include <memory>

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include <export.h>

struct window_props
{
	int width = {};
	int height = {};
};

class RENDER_API window
{
public:
	window(const unsigned depth, const unsigned major_version, const unsigned minor_version);
	window(const window &) = delete;
	window(window &&) = delete;

	auto update(const std::function<void(float)> &render_hook, const std::function<void(float)> &render_gui_hook = nullptr) -> void;
	auto close_window() -> void;

	[[nodiscard]] auto props() const { return m_props; }
	[[nodiscard]] auto is_open() const { return m_is_open; }

	[[nodiscard]] auto get_gl_context() const { return m_sdl_gl_context; }
	[[nodiscard]] const auto &get_key_state() const { return m_keys; }

	auto set_post_processing_enabled(const bool enabled) { m_is_post_processing_enabled = enabled; }
	auto set_post_processing(const std::shared_ptr<class post_processing> &post_processing) { m_post_processing = post_processing; }

	float m_delta_time = {};

private:
	window_props m_props = {};
	SDL_Window *m_sdl_window_handle = {};
	SDL_GLContext m_sdl_gl_context = {};

	std::shared_ptr<class post_processing> m_post_processing = nullptr;

	bool m_is_open = {};
	bool m_is_post_processing_enabled = {};
	const unsigned char *m_keys = {};

private:
	auto render_scene_without_post_processing(const std::function<void(float)>& render_hook) -> void;
};