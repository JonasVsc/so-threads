#include "ControlPanel.h"
#include <imgui.h>

ControlPanel::ControlPanel(std::vector<std::unique_ptr<Child>>& childs)
	: m_childs(childs)
{
}


void ControlPanel::render()
{
    if (ImGui::Button("Create Child"))
	{
		ImGui::OpenPopup("Create Child");
	}

	m_create_child_popup.render();

	ImGui::SameLine();
	ImGui::Text("| K = [ %zu ]", m_childs.size());
}