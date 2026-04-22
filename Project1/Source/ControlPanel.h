#pragma once
#include "Basket.h"
#include "Child.h"

#include "CreateChildPopup.h"

class ControlPanel
{
public:

    ControlPanel(std::vector<std::unique_ptr<Child>>& childs);

    void render();

private:

    std::vector<std::unique_ptr<Child>>& m_childs;

    CreateChildPopup m_create_child_popup{ m_childs };
};