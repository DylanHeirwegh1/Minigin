#include "MiniginPCH.h"
#include "BTScene.h"
#include "SceneLoader.h"
#include "MenuComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "EnemyComponent.h"
#include "Renderer.h"
#include "SceneSwitcher.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"

class EnemyComponent;

BTScene::BTScene()
{
	auto obj = std::make_shared<dae::GameObject>();
	obj->AddComponent<SceneSwitcher>();
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_1, std::make_shared<LoadLevelOneCommand>(obj), dae::KeyState::Up);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_2, std::make_shared<LoadLevelTwoCommand>(obj), dae::KeyState::Up);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_3, std::make_shared<LoadLevelThreeCommand>(obj), dae::KeyState::Up);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_A, std::make_shared<QuitCommand>(nullptr), dae::KeyState::Up);
}