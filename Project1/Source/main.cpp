#include <Canvas.h>

#include "ChildForm.h"
#include "Child.h"

#include <vector>
#include <memory>

static constexpr uint32_t basket_capacity{ 15u };

// Sync objects
static SDL_Mutex* mtx{ nullptr };
static SDL_Semaphore* basket_empty{ nullptr };
static SDL_Semaphore* basket_full{ nullptr };

int main()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Error: SDL_Init(): %s\n", SDL_GetError());
		return 1;
	}

	// Setup Sync Objects
	mtx = SDL_CreateMutex();
	basket_empty = SDL_CreateSemaphore(basket_capacity);
	basket_full = SDL_CreateSemaphore(0u);

	canvas::Window window("so-threads Projeto1", 640, 480);
	canvas::Renderer::init(window);
	canvas::Gui::init();

	// app state
	std::vector<std::unique_ptr<Child>> childs;

	while (!window.should_close())
	{
		canvas::Input::update();
		window.poll_events();

		canvas::Renderer::begin();
		canvas::Gui::begin();

		ImGui::Begin("Painel de controle");

		if (ImGui::Button("Create Child"))
		{
			ImGui::OpenPopup("Create Child");
		}

		ImGui::SameLine();
		ImGui::Text("| K = [ %d ]", childs.size());

		if (ImGui::BeginPopupModal("Create Child", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {

			// Parâmetros do Child
			ImGui::InputText("Name", ChildForm::name(), 255, ImGuiItemFlags_Disabled);
			ImGui::InputFloat("Tempo brincar (s)", ChildForm::Tb());
			ImGui::InputFloat("Tempo descansar (s)", ChildForm::Td());
			ImGui::Checkbox("Possui bola", ChildForm::ball());

			ImGui::Separator();

			// Botão Cancel
			if (ImGui::Button("Cancel", ImVec2(120, 0)))
			{
				ImGui::CloseCurrentPopup();
			}
			
			ImGui::SameLine();
			// Botão Confirm
			if (ImGui::Button("Create", ImVec2(120, 0))) 
			{
				childs.push_back(ChildForm::create());
				ImGui::CloseCurrentPopup();
			}



			ImGui::EndPopup();
		}

		

		if (ImGui::BeginTable("ChildTable", 2))
		{
			ImGui::TableSetupColumn("Child");
			ImGui::TableSetupColumn("Status");
			ImGui::TableHeadersRow();
			ImGui::EndTable();
		}


		ImGui::End();


		ImGui::Begin("Log de eventos");


		ImGui::End();

		canvas::Gui::render();
		canvas::Renderer::end();
	}

	SDL_Quit();
	return 0;
}