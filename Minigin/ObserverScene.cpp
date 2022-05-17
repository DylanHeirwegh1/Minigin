#include "MiniginPCH.h"
#include "ObserverScene.h"

#include "FPSComponent.h"
#include "HealthComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "TextComponent.h"
#include "Scene.h"

ObserverScene::ObserverScene()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto FPSTimer = std::make_shared<dae::GameObject>();
	auto FpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	FPSTimer->AddComponent<TextComponent>()->SetFont(FpsFont);
	FPSTimer->GetComponent<TextComponent>()->SetColor({ 0,255,0,255 });
	FPSTimer->AddComponent<FPSComponent>();
	scene.Add(FPSTimer);

	auto PeterPepper = std::make_shared<dae::GameObject>();
	PeterPepper->AddComponent<PeterPepperComponent>();

	auto Score = std::make_shared<dae::GameObject>();
	Score->AddComponent<TextComponent>();
	Score->SetWorldPosition({ 0,120,0 });
	Score->GetComponent<TextComponent>()->SetFont(FpsFont);
	Score->GetComponent<TextComponent>()->SetColor({ 255,255,0,255 });
	Score->GetComponent<TextComponent>()->SetText("Score: 0");
	Score->AddComponent<ScoreComponent>();

	//lives
	auto Health = std::make_shared<dae::GameObject>();
	Health->AddComponent<TextComponent>();
	Health->SetWorldPosition({ 0,100,0 });
	Health->GetComponent<TextComponent>()->SetFont(FpsFont);
	Health->GetComponent<TextComponent>()->SetColor({ 255,255,0,255 });
	Health->GetComponent<TextComponent>()->SetText("Remaining Lives: 3");
	Health->AddComponent<HealthComponent>();

	PeterPepper->GetComponent<PeterPepperComponent>()->GetSubject()->AddObserver(Health->GetComponent<HealthComponent>());
	PeterPepper->GetComponent<PeterPepperComponent>()->GetSubject()->AddObserver(Score->GetComponent<ScoreComponent>());

	scene.Add(PeterPepper);
	scene.Add(Health);
	scene.Add(Score);
	//
	auto PeterPepper2 = std::make_shared<dae::GameObject>();
	PeterPepper2->AddComponent<PeterPepperComponent>();

	auto Score2 = std::make_shared<dae::GameObject>();
	Score2->AddComponent<TextComponent>();
	Score2->SetWorldPosition({ 0,220,0 });
	Score2->GetComponent<TextComponent>()->SetFont(FpsFont);
	Score2->GetComponent<TextComponent>()->SetColor({ 0,255,0,255 });
	Score2->GetComponent<TextComponent>()->SetText("Score: 0");
	Score2->AddComponent<ScoreComponent>();

	//lives
	auto Health2 = std::make_shared<dae::GameObject>();
	Health2->AddComponent<TextComponent>();
	Health2->SetWorldPosition({ 0,200,0 });
	Health2->GetComponent<TextComponent>()->SetFont(FpsFont);
	Health2->GetComponent<TextComponent>()->SetColor({ 0,255,0,255 });
	Health2->GetComponent<TextComponent>()->SetText("Remaining Lives: 3");
	Health2->AddComponent<HealthComponent>();

	PeterPepper2->GetComponent<PeterPepperComponent>()->GetSubject()->AddObserver(Health2->GetComponent<HealthComponent>());
	PeterPepper2->GetComponent<PeterPepperComponent>()->GetSubject()->AddObserver(Score2->GetComponent<ScoreComponent>());

	scene.Add(PeterPepper2);
	scene.Add(Health2);
	scene.Add(Score2);

	dae::InputManager::GetInstance().AddKeyCommand(XBox360Controller::ControllerButton::ButtonA, std::make_shared<DieCommand>(PeterPepper), 1, dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(XBox360Controller::ControllerButton::ButtonB, std::make_shared<QuitCommand>(PeterPepper), 1, dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(XBox360Controller::ControllerButton::ButtonA, std::make_shared<DieCommand>(PeterPepper2), 0, dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(XBox360Controller::ControllerButton::ButtonB, std::make_shared<QuitCommand>(PeterPepper2), 0, dae::KeyState::Down);
}

ObserverScene::~ObserverScene()
{
}