#include "Gui.h"
#include "Renderer.h"

#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>


namespace canvas
{
	void Gui::init()
	{
		float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGuiStyle& style = ImGui::GetStyle();
		style.ScaleAllSizes(main_scale);
		style.FontScaleDpi = main_scale;
		ImGui::StyleColorsDark();

		// Setup Platform/Renderer backends
		ImGui_ImplSDL3_InitForSDLRenderer(Renderer::get_window(), Renderer::get_handle());
		ImGui_ImplSDLRenderer3_Init(Renderer::get_handle());
	}

	void Gui::shutdown()
	{
		ImGui_ImplSDLRenderer3_Shutdown();
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext();
	}

	void Gui::begin()
	{
		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();
	}

	void Gui::render()
	{
		ImGui::Render();

		// Clear and prepare for UI rendering
		SDL_SetRenderTarget(Renderer::get_handle(), nullptr);
		SDL_SetRenderDrawColorFloat(Renderer::get_handle(), 0.1f, 0.1f, 0.1f, 1.0f);
		SDL_RenderClear(Renderer::get_handle());

		// Render ImGui UI on top
		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), Renderer::get_handle());

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}

		// Present frame
		SDL_RenderPresent(Renderer::get_handle());
	}

} // namespace canvas