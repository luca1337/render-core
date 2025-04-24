#include <window.h>

#include <post_processing.h>

window::window(const unsigned depth, const unsigned major_version, const unsigned minor_version) : m_props{}
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major_version);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor_version);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, depth);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        close_window();
        return;
    }

    m_sdl_window_handle = SDL_CreateWindow("SDL2 Window", m_props.width, m_props.height, SDL_WINDOW_OPENGL);
    if (!m_sdl_window_handle)
    {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        close_window();
        return;
    }

    m_sdl_gl_context = SDL_GL_CreateContext(m_sdl_window_handle);
    if (!m_sdl_gl_context)
    {
        SDL_Log("OpenGL context creation failed: %s", SDL_GetError());
        close_window();
        return;
    }

    SDL_GL_SetSwapInterval(0); // Disable VSync

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress))) 
    {
        SDL_Log("Failed to initialize GLAD");
        close_window();
        return;
    }

    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_keys = reinterpret_cast<const unsigned char*>(SDL_GetKeyboardState(nullptr));

    m_is_open = true;
}

auto window::update(const std::function<void(float)> &render_hook, const std::function<void(float)> &render_gui_hook) -> void
{
    auto prev_time = SDL_GetPerformanceCounter();

    while (m_is_open)
    {
        auto ev = SDL_Event{};
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_EVENT_QUIT)
            {
                close_window();
            }
        }

        const auto current_time = SDL_GetPerformanceCounter();
        m_delta_time = static_cast<float>(current_time - prev_time) / SDL_GetPerformanceFrequency();
        prev_time = current_time;

        if (m_is_post_processing_enabled)
        {
            m_post_processing->render_to_scene(m_delta_time, [&](){ render_scene_without_post_processing(render_hook); });
        }
        else
        {
            render_scene_without_post_processing(render_hook);
            // .. render_gui(render_gui_hook);
        }

        SDL_GL_SwapWindow(m_sdl_window_handle);
    }
}

auto window::close_window() -> void
{
    if (m_sdl_window_handle)
    {
        SDL_DestroyWindow(m_sdl_window_handle);
        m_sdl_window_handle = nullptr;
    }

    SDL_Quit();
    m_is_open = false;
}

auto window::render_scene_without_post_processing(const std::function<void(float)> &render_hook) -> void
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.13f, 0.13f, 0.13f, 1.0f);

    if (render_hook != nullptr)
    {
        render_hook(m_delta_time);
    }
}
