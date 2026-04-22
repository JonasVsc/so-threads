#pragma once
#include "Basket.h"
#include "Child.h"

#include "Viewport.h"
#include "ControlPanel.h"
#include "Logger.h"

#include "SpriteSheet.h"

#include <Canvas.h>
#include <memory>
#include <vector>

class Application
{
public:

    Application();

    void run();

private:

    void update();

    std::unique_ptr<canvas::Window> m_window{ nullptr };

    Basket m_basket{};
    std::vector<std::unique_ptr<Child>> m_childs{};

    Viewport m_viewport{};
    ControlPanel m_control_panel{ m_childs };
    Logger m_logger{};

    std::unique_ptr<SpriteSheet> m_sprite_sheet{ nullptr };

    // debug

    SDL_Texture* m_child_texture{ nullptr };

    SDL_FRect m_rect; // screen position
    SDL_Rect m_src; // spritesheet frame

    int m_frame{ 0 };
    float m_anim_timer{ 0.0f };

}; // class Application