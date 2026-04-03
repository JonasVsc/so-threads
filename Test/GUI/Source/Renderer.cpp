#include "Renderer.h"
#include "Window.h"

namespace canvas
{
	ImVec4 Renderer::s_clear_color{ 0.45f, 0.55f, 0.60f, 1.00f };
	SDL_Renderer* Renderer::s_handle{ nullptr };
	SDL_Window* Renderer::s_window{ nullptr };

	bool Renderer::init(Window& window)
	{
		s_handle = SDL_CreateRenderer(window.get_handle(), nullptr);
		s_window = window.get_handle();

		return s_handle != nullptr;
	}

	void Renderer::shutdown()
	{
		if (s_handle)
		{
			SDL_DestroyRenderer(s_handle);
			s_handle = nullptr;
			s_window = nullptr;
		}
	}

	void Renderer::begin()
	{
		ImGuiIO& io = ImGui::GetIO();
		SDL_SetRenderScale(s_handle, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
		SDL_SetRenderDrawColorFloat(s_handle, s_clear_color.x, s_clear_color.y, s_clear_color.z, s_clear_color.w);
		SDL_RenderClear(s_handle);
	}

	void Renderer::end()
	{
		SDL_RenderPresent(s_handle);
	}

} // namespace canvas