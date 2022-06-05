#include "MiniginPCH.h"
#include "BTScene.h"
#include "SceneLoader.h"
//#include "MenuComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "EnemyComponent.h"
#include "Renderer.h"
#include "SceneSwitcher.h"
#include "SoundSystem.h"
//#include "backends/imgui_impl_opengl2.h"
//#include "backends/imgui_impl_sdl.h"

class EnemyComponent;

BTScene::BTScene()
{
	std::cout << "Load other level: press 1,2,3\n";
	std::cout << "Switch game mode: \n";
	std::cout << "PVP: p \n";
	std::cout << "COOP: o \n";
	std::cout << "SINGLE PLAYER: i \n";

	std::cout << "Move: WASD OR ARROWS\n";
	std::cout << "Attack: SPACE OR RSHIFT\n";

	auto obj = std::make_shared<dae::GameObject>();
	obj->AddComponent<SceneSwitcher>();

	ServiceLocator::RegisterSoundSystem(std::make_shared<SDLSoundSystem>());
	auto& t1 = ServiceLocator::GetSoundSystem();
	auto id = t1.AddAudioClip("../Data/Audio/Background.mp3", 100, -1);
	t1.Play(static_cast<soundId>(id), 100);

	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_1, std::make_shared<LoadLevelOneCommand>(obj), dae::KeyState::Pressed);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_2, std::make_shared<LoadLevelTwoCommand>(obj), dae::KeyState::Pressed);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_3, std::make_shared<LoadLevelThreeCommand>(obj), dae::KeyState::Pressed);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_ESCAPE, std::make_shared<QuitCommand>(nullptr), dae::KeyState::Pressed);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_I, std::make_shared<SwitchToSingleCommand>(obj), dae::KeyState::Pressed);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_O, std::make_shared<SwitchToCoopCommand>(obj), dae::KeyState::Pressed);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_P, std::make_shared<SwitchToPvpCommand>(obj), dae::KeyState::Pressed);
}