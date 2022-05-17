#include "pch.h"
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif
#include <SDL_filesystem.h>

#include <SDL_pixels.h>
#include <SDL_scancode.h>

#include "FPSComponent.h"
#include "ImageComponent.h"
#include "Minigin.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include <direct.h>

#include "Renderer.h"

void InitGame()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("sound");

	auto Level = std::make_shared<dae::GameObject>();
	Level->AddComponent<ImageComponent>();
	Level->GetComponent<ImageComponent>()->SetTexture("Sprites/level.png");
	auto wSize = dae::Renderer::GetInstance().GetWindowDimensions();
	Level->SetWorldPosition({ wSize.x / 2,wSize.y,0 });
	Level->GetComponent<ImageComponent>()->SetDimensions(wSize.x, wSize.y);
	scene.Add(Level);

	auto FPSTimer = std::make_shared<dae::GameObject>();
	auto FpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	FPSTimer->AddComponent<TextComponent>()->SetFont(FpsFont);
	FPSTimer->GetComponent<TextComponent>()->SetColor({ 0,255,0,255 });
	FPSTimer->AddComponent<FPSComponent>();
	scene.Add(FPSTimer);

	auto pp = std::make_shared<dae::GameObject>();
	pp->AddComponent<ImageComponent>()->SetTexture("Sprites/PeterPepper.png");
	pp->GetComponent<ImageComponent>()->MakeAnimated(2, 9, 6);
	pp->GetComponent<ImageComponent>()->SetStartFrame(3);
	pp->AddComponent<MovementComponent>();
	pp->GetComponent<ImageComponent>()->SetDimensions(40, 40);
	pp->GetComponent<ImageComponent>()->SetFramesPerSecond(15);

	scene.Add(pp);

	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_A, std::make_shared<QuitCommand>(nullptr), dae::KeyState::Up);

	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_UP, std::make_shared<MoveUpCommand>(pp), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_DOWN, std::make_shared<MoveDownCommand>(pp), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_LEFT, std::make_shared<MoveLeftCommand>(pp), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_RIGHT, std::make_shared<MoveRightCommand>(pp), dae::KeyState::Down);
}
int main(int, char* []) {
	dae::Minigin engine;
	engine.Initialize();
	InitGame();
	engine.Run();
	return 0;
}