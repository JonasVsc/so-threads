#pragma once
#include <SDL3/SDL_video.h>

namespace canvas
{
	class Window
	{
	public:

		Window(const char* title, int width, int height);

		~Window();

		void poll_events();

		inline bool should_close() const { return m_should_close; }
		
		inline SDL_Window* get_handle() const { return m_handle; }

	private:

		SDL_Window* m_handle{ nullptr };
		bool m_should_close{ false };

	}; // class Window

} // canvas