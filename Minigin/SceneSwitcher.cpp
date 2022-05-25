#include "MiniginPCH.h"
#include "SceneSwitcher.h"

#include "BTScene.h"
#include "EnemyComponent.h"
#include "ResourceManager.h"
#include "SceneLoader.h"
#include "TextComponent.h"

void SceneSwitcher::LoadLevel1()
{
	if (m_CurrLevel != 0)
		dae::SceneManager::GetInstance().RemoveScene();
	m_CurrLevel = 1;

	int r = rand();

	auto& scene = dae::SceneManager::GetInstance().CreateScene("level1" + std::to_string(r));

	SceneLoader::GetInstance().LoadLevelFromFile(L"../Data/TextFiles/level.json", scene);

	AddPeterPepper(scene, { 100,220,0 });
	//AddSausage(scene, { 399,138,0 });
	AddFpsComponent(scene, { 200,50,0 });

	m_PeterPepper.Object->GetComponent<PeterPepperComponent>()->GetSubject()->AddObserver(this);
}

void SceneSwitcher::LoadLevel2()
{
	std::cout << "LoadLevel2";
}

void SceneSwitcher::LoadLevel3()
{
	std::cout << "LoadLevel3";
}

void SceneSwitcher::Notify(const dae::GameObject& /*actor*/, Event event)
{
	switch (event)
	{
	case Event::ActorDied:
		Reset();
		break;
	}
}

SceneSwitcher::~SceneSwitcher()
{
	std::cout << "DESTRUCTOR;";
}

void SceneSwitcher::Reset()
{
	m_PeterPepper.Object->SetWorldPosition(m_PeterPepper.StartPos);
	m_PeterPepper.Object->GetComponent<RigidBody>()->ResetPos();

	for (auto sausage : m_Sausages)
	{
		sausage.Object->SetWorldPosition(sausage.StartPos);
		sausage.Object->GetComponent<RigidBody>()->ResetPos();
	};
}

void SceneSwitcher::AddFpsComponent(dae::Scene& scene, glm::vec3 pos)
{
	auto FPSTimer = std::make_shared<dae::GameObject>();
	auto FpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	FPSTimer->SetWorldPosition(pos);
	FPSTimer->AddComponent<TextComponent>()->SetFont(FpsFont);
	FPSTimer->GetComponent<TextComponent>()->SetColor({ 0,255,0,255 });
	FPSTimer->AddComponent<FPSComponent>();
	scene.Add(FPSTimer);
}

void SceneSwitcher::AddPeterPepper(dae::Scene& scene, glm::vec3 pos)
{
	m_PeterPepper.StartPos = pos;
	if (madePP)
	{
		m_PeterPepper.Object->GetComponent<RigidBody>()->RemakeCol();
		m_PeterPepper.Object->SetWorldPosition(m_PeterPepper.StartPos);
		m_PeterPepper.Object->AddComponent<RigidBody>()->SetSize({ 28,39 });
		m_PeterPepper.Object->GetComponent<RigidBody>()->SetTag("Player");
		m_PeterPepper.Object->GetComponent<RigidBody>()->OverlapWithTag({ "Enemy" , "Ingredient","Ladder" });
		m_PeterPepper.Object->GetComponent<RigidBody>()->SetCollision(PhysicsManager::CollisionType::TRIGGER);
		m_PeterPepper.Object->GetComponent<RigidBody>()->ResetPos();
		scene.Add(m_PeterPepper.Object);

		return;
	}
	m_PeterPepper.Object = std::make_shared<dae::GameObject>();
	m_PeterPepper.Object->SetWorldPosition(m_PeterPepper.StartPos);
	m_PeterPepper.Object->AddComponent<ImageComponent>()->SetTexture("Sprites/PeterPepper.png");
	m_PeterPepper.Object->GetComponent<ImageComponent>()->MakeAnimated(2, 9, 6);
	m_PeterPepper.Object->GetComponent<ImageComponent>()->SetStartFrame(3);
	m_PeterPepper.Object->AddComponent<MovementComponent>()->SetMovementSpeed({ 75,50 });
	m_PeterPepper.Object->GetComponent<ImageComponent>()->SetDimensions(40, 40);
	m_PeterPepper.Object->GetComponent<ImageComponent>()->SetFramesPerSecond(15);
	m_PeterPepper.Object->AddComponent<PeterPepperComponent>();

	madePP = true;
	m_PeterPepper.Object->AddComponent<RigidBody>()->SetSize({ 28,39 });
	m_PeterPepper.Object->GetComponent<RigidBody>()->SetTag("Player");
	m_PeterPepper.Object->GetComponent<RigidBody>()->OverlapWithTag({ "Enemy" , "Ingredient","Ladder" });
	m_PeterPepper.Object->GetComponent<RigidBody>()->SetCollision(PhysicsManager::CollisionType::TRIGGER);

	//dae::InputManager::GetInstance().ClearCommands();
	scene.Add(m_PeterPepper.Object);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_UP, std::make_shared<MoveUpCommand>(m_PeterPepper.Object), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_DOWN, std::make_shared<MoveDownCommand>(m_PeterPepper.Object), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_LEFT, std::make_shared<MoveLeftCommand>(m_PeterPepper.Object), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_RIGHT, std::make_shared<MoveRightCommand>(m_PeterPepper.Object), dae::KeyState::Down);
}

void SceneSwitcher::AddSausage(dae::Scene& scene, glm::vec3 pos)
{
	sceneObj sausage{};
	sausage.StartPos = pos;
	sausage.Object = std::make_shared<dae::GameObject>();
	sausage.Object->SetWorldPosition(pos);
	sausage.Object->AddComponent<RigidBody>()->SetSize({ 28,36 });
	sausage.Object->GetComponent<RigidBody>()->OverlapWithTag({ "Player" , "Ingredient","Ladder","Pepper" });
	sausage.Object->GetComponent<RigidBody>()->SetTag("Enemy");
	sausage.Object->AddComponent<EnemyComponent>()->SetTarget(m_PeterPepper.Object.get());
	sausage.Object->AddComponent<MovementComponent>()->SetMovementSpeed({ 50,40 });
	sausage.Object->AddComponent<ImageComponent>()->SetTexture("Sprites/Sausage.png");
	sausage.Object->GetComponent<ImageComponent>()->SetDimensions(40, 40);
	sausage.Object->GetComponent<ImageComponent>()->MakeAnimated(2, 6, 3);
	sausage.Object->GetComponent<ImageComponent>()->SetStartFrame(2);
	sausage.Object->GetComponent<ImageComponent>()->SetFramesPerSecond(10);
	sausage.Object->GetComponent<RigidBody>()->SetCollision(PhysicsManager::CollisionType::TRIGGER);
	m_Sausages.emplace_back(sausage);
	scene.Add(sausage.Object);
}