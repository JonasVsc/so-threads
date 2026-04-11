#pragma once

#include "Basket.h"
#include "Child.h"

#include <memory>
#include <vector>


struct ChildForm
{
    char name[255];
    float Tb;
    float Td;
    bool has_ball;
};

class CreateChildPopup
{
public:

    CreateChildPopup(std::vector<std::unique_ptr<Child>>& childs);

    void draw();

    void reset();

private:

    std::vector<std::unique_ptr<Child>>& m_childs;    

    ChildForm m_child_form{};

}; // class CreateChildPopup