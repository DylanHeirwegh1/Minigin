#include "MiniginPCH.h"
#include "SoundScene.h"

#include "FPSComponent.h"
#include "ImageComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SoundSystem.h"
#include "TextComponent.h"

SoundScene::SoundScene()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("sound");
	auto FPSTimer = std::make_shared<dae::GameObject>();
	auto FpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	FPSTimer->AddComponent<TextComponent>()->SetFont(FpsFont);
	FPSTimer->GetComponent<TextComponent>()->SetColor({ 0,255,0,255 });
	FPSTimer->AddComponent<FPSComponent>();

	FPSTimer->AddComponent<ImageComponent>()->MakeAnimated(5, 5, 25);
	FPSTimer->GetComponent<ImageComponent>()->SetTexture("../Minigin/Tibo.png");
	FPSTimer->SetWorldPosition({ 200,200,0 });
	FPSTimer->GetComponent<ImageComponent>()->SetDimensions(.5, .5);
	//FPSTimer->GetComponent<ImageComponent>()->FlipTexture();

	scene.Add(FPSTimer);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_UP, std::make_shared<QuitCommand>(nullptr), dae::KeyState::Pressed);
}

SoundScene::~SoundScene()
{
}