#include "MiniginPCH.h"
#include "MenuComponent.h"
#include "imgui.h"
#include "Renderer.h"
#include "SDL_opengl.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl2.h"
void MenuComponent::Initialize(dae::GameObject* owner)
{
	m_Owner = owner;
}

void MenuComponent::Render()
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(dae::Renderer::GetInstance().GetSDLWindow());
	ImGui::NewFrame();

	ImGui::SetNextWindowPos({ 0,0 });
	ImGui::Begin("Options", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::Button("Single")) m_Subject->Notify(*m_Owner, Event::SINGLE);
	else if (ImGui::Button("Co-op")) m_Subject->Notify(*m_Owner, Event::COOP);
	else if (ImGui::Button("PvP")) m_Subject->Notify(*m_Owner, Event::PVP);

	else if (ImGui::Button("Level1")) m_Subject->Notify(*m_Owner, Event::LoadLevel1);
	else if (ImGui::Button("Level2"))m_Subject->Notify(*m_Owner, Event::LoadLevel2);
	else if (ImGui::Button("Level3"))m_Subject->Notify(*m_Owner, Event::LoadLevel3);

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}
void MenuComponent::Update()
{
}