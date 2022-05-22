#include "MiniginPCH.h"
#include "BTScene.h"
#include "SceneLoader.h"
#include "MenuComponent.h"

class EnemyComponent;

BTScene::BTScene()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("sound");
	SceneLoader::GetInstance().LoadLevelFromFile(L"../Data/TextFiles/level.json", scene);

	auto FPSTimer = std::make_shared<dae::GameObject>();
	auto FpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	FPSTimer->AddComponent<TextComponent>()->SetFont(FpsFont);
	FPSTimer->GetComponent<TextComponent>()->SetColor({ 0,255,0,255 });
	FPSTimer->AddComponent<FPSComponent>();
	scene.Add(FPSTimer);

	m_PeterPepper = std::make_shared<dae::GameObject>();
	m_PeterPepper->SetWorldPosition({ 100,231,0 });
	m_PeterPepper->AddComponent<ImageComponent>()->SetTexture("Sprites/PeterPepper.png");
	m_PeterPepper->GetComponent<ImageComponent>()->MakeAnimated(2, 9, 6);
	m_PeterPepper->GetComponent<ImageComponent>()->SetStartFrame(3);
	m_PeterPepper->AddComponent<MovementComponent>();
	m_PeterPepper->GetComponent<ImageComponent>()->SetDimensions(40, 40);
	m_PeterPepper->GetComponent<ImageComponent>()->SetFramesPerSecond(15);
	m_PeterPepper->AddComponent<PeterPepperComponent>();
	m_PeterPepper->AddComponent<RigidBody>()->SetSize({ 28,40 });
	m_PeterPepper->GetComponent<RigidBody>()->SetTag("Player");
	m_PeterPepper->GetComponent<RigidBody>()->OverlapWithTag({ "Enemy" , "Ingredient" });
	scene.Add(m_PeterPepper);

	m_Sausage = std::make_shared<dae::GameObject>();
	m_Sausage->SetWorldPosition({ 399,135,0 });
	m_Sausage->AddComponent<RigidBody>()->SetSize({ 28,35 });
	m_Sausage->GetComponent<RigidBody>()->SetVisible(true);
	m_Sausage->GetComponent<RigidBody>()->OverlapWithTag({ "Player" , "Ingredient" });
	m_Sausage->GetComponent<RigidBody>()->SetTag("Enemy");

	m_Sausage->AddComponent<EnemyComponent>()->SetTarget(m_PeterPepper.get());
	m_Sausage->AddComponent<MovementComponent>()->SetMovementSpeed({ 75,75 });
	m_Sausage->AddComponent<ImageComponent>()->SetTexture("Sprites/Sausage.png");
	m_Sausage->GetComponent<ImageComponent>()->SetDimensions(40, 40);
	m_Sausage->GetComponent<ImageComponent>()->MakeAnimated(1, 6, 3);
	m_Sausage->GetComponent<ImageComponent>()->SetStartFrame(2);
	m_Sausage->GetComponent<ImageComponent>()->SetFramesPerSecond(10);

	scene.Add(m_Sausage);

	auto im = std::make_shared<dae::GameObject>();
	im->AddComponent<MenuComponent>();
	scene.Add(im);

	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_A, std::make_shared<QuitCommand>(nullptr), dae::KeyState::Up);

	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_UP, std::make_shared<MoveUpCommand>(m_PeterPepper), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_DOWN, std::make_shared<MoveDownCommand>(m_PeterPepper), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_LEFT, std::make_shared<MoveLeftCommand>(m_PeterPepper), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_RIGHT, std::make_shared<MoveRightCommand>(m_PeterPepper), dae::KeyState::Down);

	m_PeterPepper->GetComponent<PeterPepperComponent>()->GetSubject()->AddObserver(this);
}

void BTScene::Reset()
{
	m_PeterPepper->SetWorldPosition({ 100, 231, 0 });
	m_PeterPepper->GetComponent<RigidBody>()->ResetPos();

	m_PeterPepper->SetWorldPosition({ 100, 231, 0 });
	m_PeterPepper->GetComponent<RigidBody>()->ResetPos();

	m_PeterPepper->SetWorldPosition({ 100, 231, 0 });
	m_PeterPepper->GetComponent<RigidBody>()->ResetPos();

	m_Sausage->SetWorldPosition({ 399,135,0 });
	m_Sausage->GetComponent<RigidBody>()->ResetPos();
}

void BTScene::Notify(const dae::GameObject&, Event event)
{
	switch (event)
	{
	case Event::ActorDied:
		Reset();
	}
}

void BTScene::AddBlock(dae::Scene& scene, glm::vec2 pos, glm::vec2 size)
{
	std::shared_ptr<dae::GameObject> currBlock = std::make_shared<dae::GameObject>();

	currBlock->SetWorldPosition({ pos.x,pos.y,0 });
	currBlock->AddComponent<RigidBody>()->SetSize({ size.x,size.y });
	scene.Add(currBlock);
}