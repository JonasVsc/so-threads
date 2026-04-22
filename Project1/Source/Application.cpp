#include "Application.h"
#include <imgui.h>
#include <imgui_internal.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace
{
    void build_dockspace()
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags flags =
            ImGuiWindowFlags_NoDocking |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus;

        ImGui::Begin("DockSpace", nullptr, flags);

        ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
        ImGui::DockSpace(dockspace_id);

        static bool first = true;
        if (first)
        {
            first = false;

            ImGui::DockBuilderRemoveNode(dockspace_id);
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
            ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

            ImGuiID main = dockspace_id;

            ImGuiID left = ImGui::DockBuilderSplitNode(main, ImGuiDir_Right, 0.2f, nullptr, &main);
            ImGuiID bottom = ImGui::DockBuilderSplitNode(main, ImGuiDir_Down, 0.25f, nullptr, &main);

            ImGui::DockBuilderDockWindow("Viewport", main);
            ImGui::DockBuilderDockWindow("Painel", left);
            ImGui::DockBuilderDockWindow("Logger", bottom);

            ImGui::DockBuilderFinish(dockspace_id);
        }

        ImGui::End();
    }

} // namespace


Application::Application()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Error: SDL_Init(): %s\n", SDL_GetError());
        return;
	}

    m_window = std::make_unique<canvas::Window>("so-threads Projeto1", 1280, 720);   

    canvas::Renderer::init(*m_window, true);
    canvas::Gui::init();

    
    // load spritesheet
    int width, height, channels;

    unsigned char* data = stbi_load("player.png", &width, &height, &channels, 4);

}

void Application::run()
{
    canvas::Time::init();

    m_rect = SDL_FRect{ 0.0f, 0.0f, 100.0f, 100.0f };

    while(!m_window->should_close())
    {
        canvas::Time::tick();
        canvas::Input::update();
        m_window->poll_events();

        update();

        // Handle window resize
        if (m_window->was_resized())
        {
            canvas::Renderer::on_resize();
            m_window->clear_resize_flag();
        }

        // FRAME 1: Render to offscreen texture
        canvas::Renderer::begin();

        SDL_SetRenderDrawColorFloat(canvas::Renderer::get_handle(), 1.0f, 0.0f, 0.0f, 1.0f);
        SDL_RenderFillRect(canvas::Renderer::get_handle(), &m_rect);

        canvas::Renderer::end();

        // FRAME 2: Render UI and display offscreen texture
        canvas::Gui::begin();

        build_dockspace();

        ImGuiWindowFlags viewport_flags = 
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoBackground;

        if (ImGui::Begin("Viewport", nullptr, viewport_flags))
        {
            m_viewport.render();
            ImGui::End();
        }

        if (ImGui::Begin("Painel"))
        {
            m_control_panel.render();
            ImGui::End();
        }

        if (ImGui::Begin("Logger"))
        {
            m_logger.render();
            ImGui::End();
        }

        canvas::Gui::render();
    }

    m_window.reset();
    SDL_Quit();
}

void Application::update()
{
    float speed = 500.0f * canvas::Time::delta_time();

    if(canvas::Input::is_key_down(KeyCode::W))
    {
        m_rect.y -= speed;
    }
    if (canvas::Input::is_key_down(KeyCode::A))
    {
        m_rect.x -= speed;
    }
    if (canvas::Input::is_key_down(KeyCode::S))
    {
        m_rect.y += speed;
    }
    if (canvas::Input::is_key_down(KeyCode::D))
    {
        m_rect.x += speed;
    }
}
