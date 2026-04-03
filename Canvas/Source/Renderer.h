#pragma once
#include <imgui.h>
#include <SDL3/SDL_render.h>

namespace canvas
{
	class Window;
	class Renderer
	{
	public:

		static bool init(Window& window);

		static void shutdown();

		static void begin();

		static void end();

		static void set_clear(ImVec4& clear_color) { s_clear_color = clear_color; }

		static SDL_Renderer* get_handle() { return s_handle; }
		static SDL_Window* get_window() { return s_window; }
		static float* get_clear_color() { return &s_clear_color.x; }
	private:

		static ImVec4 s_clear_color;
		static SDL_Renderer* s_handle;
		static SDL_Window* s_window;

	}; // class Renderer

} // namespace canvas