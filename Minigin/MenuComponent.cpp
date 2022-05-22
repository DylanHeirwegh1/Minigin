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

	ComposeWindow();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}
void MenuComponent::Update()
{
}

void MenuComponent::ComposeWindow()
{
	ImGui::SetNextWindowPos({ 0,0 });
	ImGui::Begin("Options", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Button("PvE");
	ImGui::Button("Co-op");
	ImGui::Button("PvP");

	ImGui::End();
}