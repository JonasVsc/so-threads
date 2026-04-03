#include<SDL3/SDL.h>
#include "Input.h"
#include "Window.h"
#include "Renderer.h"
#include "Gui.h"

int main()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Error: SDL_Init(): %s\n", SDL_GetError());
		return 1;
	}

	canvas::Window window("so-threads TestGui", 640, 480);

	canvas::Renderer::init(window);
	canvas::Gui::init();

	while (!window.should_close())
	{
		canvas::Input::update();
		window.poll_events();

		canvas::Renderer::begin();
		canvas::Gui::begin();
		
		ImGui::Begin("ClearColor");

		ImVec4 color;
		ImGui::ColorEdit4("Color", canvas::Renderer::get_clear_color(), 0);
		
		ImGui::End();

		canvas::Gui::render();
		canvas::Renderer::end();
	}

	canvas::Gui::shutdown();
	canvas::Renderer::shutdown();

	SDL_Quit();
	return 0;
}