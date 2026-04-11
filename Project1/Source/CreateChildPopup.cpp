#include "CreateChildPopup.h"
#include <imgui.h>

CreateChildPopup::CreateChildPopup(std::vector<std::unique_ptr<Child>>& childs)
    : m_childs(childs)
{
}

void CreateChildPopup::draw()
{
    if (ImGui::BeginPopupModal("Create Child", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) 
    {
        ImGui::InputText("Name", m_child_form.name, sizeof(m_child_form.name));
        ImGui::InputFloat("Tempo brincar (s)", &m_child_form.Tb);
        ImGui::InputFloat("Tempo descansar (s)", &m_child_form.Td);
        ImGui::Checkbox("Has Ball?", &m_child_form.has_ball);

        ImGui::Separator();

        if (ImGui::Button("Cancel", ImVec2(120, 0)))
        {
            ImGui::CloseCurrentPopup();
            reset();
        }

        ImGui::SameLine();
        if (ImGui::Button("Create"))
        {
            m_childs.push_back(std::make_unique<Child>());
            m_childs.back()->create(m_child_form.name, m_child_form.has_ball, m_child_form.Tb, m_child_form.Td);
            
            ImGui::CloseCurrentPopup();
            reset();
        }

        ImGui::EndPopup();
    }
}

void CreateChildPopup::reset()
{
    m_child_form = {};
}
