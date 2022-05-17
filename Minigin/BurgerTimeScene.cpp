#include "MiniginPCH.h"
#include "BurgerTimeScene.h"

#include <direct.h>

#include "Command.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "InputManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextComponent.h"

BurgerTimeScene::BurgerTimeScene()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("sound");
	auto FPSTimer = std::make_shared<dae::GameObject>();
	/*auto FpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	FPSTimer->AddComponent<TextComponent>()->SetFont(FpsFont);
	FPSTimer->GetComponent<TextComponent>()->SetColor({ 0,255,0,255 });
	FPSTimer->AddComponent<FPSComponent>();*/

	char c[256]{};
	SDL_filesystem_h_::_getcwd(c, 256);
	std::cout << "Current directory is: " << std::string(c);
	FPSTimer->AddComponent<ImageComponent>();
	FPSTimer->GetComponent<ImageComponent>()->SetTexture("Sprites/level.png");
	auto wSize = dae::Renderer::GetInstance().GetWindowDimensions();

	FPSTimer->SetWorldPosition({ wSize.x / 2,wSize.y,0 });
	FPSTimer->GetComponent<ImageComponent>()->SetDimensions(wSize.x, wSize.y);

	scene.Add(FPSTimer);

	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_UP, std::make_shared<QuitCommand>(nullptr), dae::KeyState::Pressed);
}