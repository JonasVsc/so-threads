#include "ControlPanel.h"
#include <imgui.h>

ControlPanel::ControlPanel(std::vector<std::unique_ptr<Child>>& childs)
	: m_childs(childs)
{
}


void ControlPanel::draw()
{
    ImGui::Begin("Painel de controle");

    if (ImGui::Button("Create Child"))
	{
		ImGui::OpenPopup("Create Child");
	}

	m_create_child_popup.draw();

	ImGui::SameLine();
	ImGui::Text("| K = [ %zu ]", m_childs.size());

    ImGui::End();
}