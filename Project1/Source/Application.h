#pragma once
#include "Basket.h"
#include "Child.h"

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

    std::unique_ptr<canvas::Window> m_window{ nullptr };

    Basket m_basket{};
    std::vector<std::unique_ptr<Child>> m_childs{};

    ControlPanel m_control_panel{ m_childs };
    Logger m_logger{};

    std::unique_ptr<SpriteSheet> m_sprite_sheet{ nullptr };

}; // class Application