#include <input.h>

std::unordered_map<SDL_Keycode, bool> input::m_key_states = {};

auto input::is_key_pressed(const window &window, SDL_Keycode key) -> bool
{
    auto current_key_state = window.get_key_state();

    auto pressed = false;

    if (current_key_state[SDL_GetScancodeFromKey(key, nullptr)] && !m_key_states[key])
    {
        pressed = true;
    }

    m_key_states[key] = current_key_state[SDL_GetScancodeFromKey(key, nullptr)];

    return pressed;
}
