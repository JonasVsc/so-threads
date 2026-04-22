#include "Renderer.h"
#include "Window.h"

namespace canvas
{
	ImVec4 Renderer::s_clear_color{ 0.35f, 0.60f, 0.30f, 1.00f };
	SDL_Renderer* Renderer::s_handle{ nullptr };
	SDL_Window* Renderer::s_window{ nullptr };
	SDL_Texture* Renderer::s_out{ nullptr };
	bool Renderer::s_use_offscreen{ false };

	bool Renderer::init(Window& window, bool offscreen)
	{
		s_handle = SDL_CreateRenderer(window.get_handle(), nullptr);
		s_window = window.get_handle();
		s_use_offscreen = offscreen;

		int w, h;
		SDL_GetWindowSize(window.get_handle(), &w, &h);

		if (offscreen)
		{
			s_out = SDL_CreateTexture(s_handle, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
		}

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
		if (s_out)
		{
			SDL_SetRenderTarget(s_handle, s_out);
		}

		ImGuiIO& io = ImGui::GetIO();
		SDL_SetRenderScale(s_handle, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
		SDL_SetRenderDrawColorFloat(s_handle, s_clear_color.x, s_clear_color.y, s_clear_color.z, s_clear_color.w);
		SDL_RenderClear(s_handle);
	}

	void Renderer::end()
	{
		if (s_out)
		{
			SDL_SetRenderTarget(s_handle, nullptr);
		}
	}

	void Renderer::on_resize()
	{
		if (!s_use_offscreen || !s_handle || !s_window)
		{
			return;
		}

		// Destruir textura antiga
		if (s_out)
		{
			SDL_DestroyTexture(s_out);
			s_out = nullptr;
		}

		// Criar nova textura com as novas dimensões
		int w, h;
		SDL_GetWindowSize(s_window, &w, &h);
		s_out = SDL_CreateTexture(s_handle, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
	}

} // namespace canvas