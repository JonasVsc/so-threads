#include "Gui.h"
#include "Renderer.h"

#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>


namespace canvas
{
	void Gui::init()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
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
		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), Renderer::get_handle());
	}

} // namespace canvas