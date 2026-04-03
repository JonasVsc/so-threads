#include "Window.h"
#include "Input.h"

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <imgui_impl_sdl3.h>

namespace canvas
{
	static KeyCode translate_key(SDL_Keycode key)
	{
		switch (key)
		{
		case SDLK_A: return KeyCode::A;
		case SDLK_W: return KeyCode::W;
		case SDLK_S: return KeyCode::S;
		case SDLK_D: return KeyCode::D;

		case SDLK_SPACE: return KeyCode::Space;
		case SDLK_ESCAPE: return KeyCode::Escape;

		case SDLK_LEFT:  return KeyCode::Left;
		case SDLK_RIGHT: return KeyCode::Right;
		case SDLK_UP:    return KeyCode::Up;
		case SDLK_DOWN:  return KeyCode::Down;

		default: return KeyCode::Unknown;
		}
	}

	Window::Window(const char* title, int width, int height)
	{
		m_handle = SDL_CreateWindow(title, width, height, 0);
	}

	Window::~Window()
	{
		SDL_DestroyWindow(m_handle);
		m_should_close = true;
	}

	void Window::poll_events()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL3_ProcessEvent(&event);
			if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
			{
				m_should_close = true;
			}

			switch (event.type)
			{
			case SDL_EVENT_KEY_DOWN:
			{
				KeyCode key = translate_key(event.key.key);
				Input::set_key(key, true);
				break;
			}
			case SDL_EVENT_KEY_UP:
			{
				KeyCode key = translate_key(event.key.key);
				Input::set_key(key, false);
				break;
			}
			case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
			{
				m_should_close = true;
				break;
			}
			}
		}
	}

} // namespace canvas