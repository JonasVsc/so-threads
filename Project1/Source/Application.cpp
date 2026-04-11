#include "Application.h"

Application::Application()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Error: SDL_Init(): %s\n", SDL_GetError());
        return;
	}

    m_window = std::make_unique<canvas::Window>("so-threads Projeto1", 640, 480);   

    canvas::Renderer::init(*m_window);
    canvas::Gui::init();

    m_sprite_sheet = std::make_unique<SpriteSheet>(canvas::Renderer::get_handle(), "assets/sprite_sheet.bmp");
}

void Application::run()
{
    canvas::Time::init();

    SDL_FRect rect{ 0.0f, 0.0f, 100.0f, 100.0f };

    while(!m_window->should_close())
    {
        canvas::Time::tick();
        canvas::Input::update();
        m_window->poll_events();

        canvas::Renderer::begin();
        canvas::Gui::begin();

        SDL_SetRenderDrawColorFloat(canvas::Renderer::get_handle(), 1.0f, 0.0f, 0.0f, 1.0f);
        SDL_RenderFillRect(canvas::Renderer::get_handle(), &rect);

        m_control_panel.draw();
        m_logger.draw();

        canvas::Gui::render();
        canvas::Renderer::end();
    }

    m_window.reset();
    SDL_Quit();
}
