#include "MiniginPCH.h"
#include "SceneSwitcher.h"

#include "BTScene.h"
#include "EnemyComponent.h"
#include "HighScoreComponent.h"
#include "LivesComponent.h"
//#include "MenuComponent.h"
#include "PepperTextComponent.h"
#include "ResourceManager.h"
#include "SceneLoader.h"
#include "ScoreComponent.h"
#include "TextComponent.h"

void SceneSwitcher::LoadLevel1()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("level1" + std::to_string(rand()));
	SceneLoader::GetInstance().LoadLevelFromFile(L"../Data/TextFiles/level.json", scene);
	AddPeterPepper(scene, { 100,221,0 });
	AddMrsSalt(scene, { 150,221,0 });

	AddPlayerSausage(scene, { 399,138,0 });

	if (m_CurrGameMode != GameMode::PVP)
		AddSausage(scene, { 399,138,0 });

	AddSausage(scene, { 510,138,0 });
	AddSausage(scene, { 10,138,0 });
	AddSausage(scene, { 10,399,0 });
	AddEgg(scene, { 10,510,0 });

	AddFpsComponent(scene, { 600,50,0 });

	AddPickle(scene, { 499,528,0 });
	AddText(scene);
	SetInputCommands();
	m_FirstLoad = false;

	dae::SceneManager::GetInstance().RemoveOld();
}

void SceneSwitcher::LoadLevel2()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("level2" + std::to_string(rand()));
	SceneLoader::GetInstance().LoadLevelFromFile(L"../Data/TextFiles/level2.json", scene);

	AddPeterPepper(scene, { 100,222,0 });
	AddMrsSalt(scene, { 150,222,0 });
	AddPlayerSausage(scene, { 399,136,0 });

	if (m_CurrGameMode != GameMode::PVP)
		AddSausage(scene, { 399,134,0 });

	AddSausage(scene, { 510,134,0 });
	AddSausage(scene, { 10,134,0 });
	AddSausage(scene, { 10,399,0 });
	AddEgg(scene, { 10,410,0 });

	AddFpsComponent(scene, { 600,50,0 });

	AddPickle(scene, { 399,136,0 });
	AddText(scene);
	SetInputCommands();

	dae::SceneManager::GetInstance().RemoveOld();
}

void SceneSwitcher::LoadLevel3()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("level3" + std::to_string(rand()));
	SceneLoader::GetInstance().LoadLevelFromFile(L"../Data/TextFiles/level3.json", scene);

	AddPeterPepper(scene, { 20,600,0 });
	AddMrsSalt(scene, { 20,550,0 });
	AddPlayerSausage(scene, { 399,136,0 });

	if (m_CurrGameMode != GameMode::PVP)
		AddSausage(scene, { 399,134,0 });

	AddSausage(scene, { 540,300,0 });
	AddSausage(scene, { 10,136,0 });
	AddSausage(scene, { 460,399,0 });
	AddEgg(scene, { 610,350,0 });

	AddFpsComponent(scene, { 600,50,0 });

	AddPickle(scene, { 399,136,0 });
	AddText(scene);
	SetInputCommands();

	dae::SceneManager::GetInstance().RemoveOld();
}

void SceneSwitcher::Initialize(dae::GameObject* owner)
{
	m_Owner = owner;
	LoadLevel(1);
}

void SceneSwitcher::LoadLevel(int nr)
{
	std::cout << "Load level" << nr << std::endl;
	m_Enemies.clear();
	m_CurrLevel = nr;
	switch (m_CurrLevel)
	{
	case 1:
		LoadLevel1();
		break;
	case 2:
		LoadLevel2();
		break;
	case 3:
		LoadLevel3();
		break;
	default:
		break;
	}
}

void SceneSwitcher::SwitchGameMode(GameMode mode)
{
	m_CurrGameMode = mode;
	std::cout << "New game mode\n";
	LoadLevel(m_CurrLevel);
}

void SceneSwitcher::Notify(const dae::GameObject& /*actor*/, Event event)
{
	switch (event)
	{
	case Event::ActorDied:
		Reset();
		break;
	case Event::LoadLevel1:
		if (m_CurrLevel != 1)LoadLevel(1);
		break;
	case Event::LoadLevel2:
		if (m_CurrLevel != 2)LoadLevel(2);
		break;
	case Event::LoadLevel3:
		if (m_CurrLevel != 3)LoadLevel(3);
		break;
	case Event::COOP:
		SwitchGameMode(GameMode::COOP);
		break;
	case Event::SINGLE:
		SwitchGameMode(GameMode::SINGLE);
		break;
	case Event::PVP:
		SwitchGameMode(GameMode::PVP);
		break;
	case Event::LevelComplete:
		m_CurrLevel++;
		LoadLevel((m_CurrLevel - 1) % 3 + 1);
		break;
	case Event::EnemyDied:
		HandleRespawnEnemies();
	}
}

SceneSwitcher::~SceneSwitcher()
{
}

void SceneSwitcher::Reset()
{
	if (m_PeterPepper.Object->GetComponent<PeterPepperComponent>()->GetLives() == 0)
	{
		//m_PeterPepper.Object->SetActive(false);
		LoadLevel(1);
		m_PeterPepper.Object->GetComponent<PeterPepperComponent>()->GameReset();
		m_Salt.Object->GetComponent<PeterPepperComponent>()->GameReset();

		m_PPScoreText->GetComponent<ScoreComponent>()->Refresh(*m_PeterPepper.Object.get());

		m_PPLivesText->GetComponent<LivesComponent>()->Refresh(*m_PeterPepper.Object.get());
		m_SaltLivesText->GetComponent<LivesComponent>()->Refresh(*m_Salt.Object.get());
		m_PPPeppersText->GetComponent<PepperTextComponent>()->Refresh(*m_PeterPepper.Object.get());
		m_SaltPeppersText->GetComponent<PepperTextComponent>()->Refresh(*m_Salt.Object.get());
	}

	if (m_Salt.Object->GetComponent<PeterPepperComponent>()->GetLives() == 0)
		m_Salt.Object->SetActive(false);

	m_PeterPepper.Object->SetWorldPosition(m_PeterPepper.StartPos);
	m_PeterPepper.Object->GetComponent<RigidBody>()->ResetPos();

	m_PlayerSausage.Object->SetWorldPosition(m_PlayerSausage.StartPos);
	m_PlayerSausage.Object->GetComponent<RigidBody>()->ResetPos();

	m_Salt.Object->SetWorldPosition(m_Salt.StartPos);
	m_Salt.Object->GetComponent<RigidBody>()->ResetPos();

	for (auto& sausage : m_Enemies)
	{
		sausage.Object->SetActive(true);
		sausage.Object->SetWorldPosition(sausage.StartPos);
		sausage.Object->GetComponent<RigidBody>()->ResetPos();
	};
}

void SceneSwitcher::SetInputCommands()
{
	if (!m_FirstLoad) return;

	unsigned int controller1 = dae::InputManager::GetInstance().AddController();
	unsigned int controller2 = dae::InputManager::GetInstance().AddController();

	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_W, std::make_shared<MoveUpCommand>(m_PeterPepper.Object), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_S, std::make_shared<MoveDownCommand>(m_PeterPepper.Object), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_A, std::make_shared<MoveLeftCommand>(m_PeterPepper.Object), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_D, std::make_shared<MoveRightCommand>(m_PeterPepper.Object), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_SPACE, std::make_shared<AttackCommand>(m_PeterPepper.Object), dae::KeyState::Pressed);

	dae::InputManager::GetInstance().AddKeyCommand(XBox360Controller::ControllerButton::ButtonUP, std::make_shared<MoveUpCommand>(m_PeterPepper.Object), controller1, dae::KeyState::Pressed);
	dae::InputManager::GetInstance().AddKeyCommand(XBox360Controller::ControllerButton::ButtonDOWN, std::make_shared<MoveDownCommand>(m_PeterPepper.Object), controller1, dae::KeyState::Pressed);
	dae::InputManager::GetInstance().AddKeyCommand(XBox360Controller::ControllerButton::ButtonLEFT, std::make_shared<MoveLeftCommand>(m_PeterPepper.Object), controller1, dae::KeyState::Pressed);
	dae::InputManager::GetInstance().AddKeyCommand(XBox360Controller::ControllerButton::ButtonRIGHT, std::make_shared<MoveRightCommand>(m_PeterPepper.Object), controller1, dae::KeyState::Pressed);
	dae::InputManager::GetInstance().AddKeyCommand(XBox360Controller::ControllerButton::ButtonA, std::make_shared<AttackCommand>(m_PeterPepper.Object), controller1, dae::KeyState::Down);

	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_UP, std::make_shared<MoveUpCommand>(m_Salt.Object), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_DOWN, std::make_shared<MoveDownCommand>(m_Salt.Object), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_LEFT, std::make_shared<MoveLeftCommand>(m_Salt.Object), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_RIGHT, std::make_shared<MoveRightCommand>(m_Salt.Object), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_RSHIFT, std::make_shared<AttackCommand>(m_Salt.Object), dae::KeyState::Pressed);

	dae::InputManager::GetInstance().AddKeyCommand(XBox360Controller::ControllerButton::ButtonUP, std::make_shared<MoveUpCommand>(m_Salt.Object), controller2, dae::KeyState::Pressed);
	dae::InputManager::GetInstance().AddKeyCommand(XBox360Controller::ControllerButton::ButtonDOWN, std::make_shared<MoveDownCommand>(m_Salt.Object), controller2, dae::KeyState::Pressed);
	dae::InputManager::GetInstance().AddKeyCommand(XBox360Controller::ControllerButton::ButtonLEFT, std::make_shared<MoveLeftCommand>(m_Salt.Object), controller2, dae::KeyState::Pressed);
	dae::InputManager::GetInstance().AddKeyCommand(XBox360Controller::ControllerButton::ButtonRIGHT, std::make_shared<MoveRightCommand>(m_Salt.Object), controller2, dae::KeyState::Pressed);
	dae::InputManager::GetInstance().AddKeyCommand(XBox360Controller::ControllerButton::ButtonA, std::make_shared<AttackCommand>(m_Salt.Object), controller2, dae::KeyState::Down);

	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_UP, std::make_shared<MoveUpCommand>(m_PlayerSausage.Object), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_DOWN, std::make_shared<MoveDownCommand>(m_PlayerSausage.Object), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_LEFT, std::make_shared<MoveLeftCommand>(m_PlayerSausage.Object), dae::KeyState::Down);
	dae::InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_RIGHT, std::make_shared<MoveRightCommand>(m_PlayerSausage.Object), dae::KeyState::Down);

	dae::InputManager::GetInstance().AddKeyCommand(XBox360Controller::ControllerButton::ButtonUP, std::make_shared<MoveUpCommand>(m_PlayerSausage.Object), controller2, dae::KeyState::Pressed);
	dae::InputManager::GetInstance().AddKeyCommand(XBox360Controller::ControllerButton::ButtonDOWN, std::make_shared<MoveDownCommand>(m_PlayerSausage.Object), controller2, dae::KeyState::Pressed);
	dae::InputManager::GetInstance().AddKeyCommand(XBox360Controller::ControllerButton::ButtonLEFT, std::make_shared<MoveLeftCommand>(m_PlayerSausage.Object), controller2, dae::KeyState::Pressed);
	dae::InputManager::GetInstance().AddKeyCommand(XBox360Controller::ControllerButton::ButtonRIGHT, std::make_shared<MoveRightCommand>(m_PlayerSausage.Object), controller2, dae::KeyState::Pressed);

	m_PeterPepper.Object->GetComponent<PeterPepperComponent>()->GetSubject()->AddObserver(this);
	m_Salt.Object->GetComponent<PeterPepperComponent>()->GetSubject()->AddObserver(this);
}

void SceneSwitcher::AddFpsComponent(dae::Scene& scene, glm::vec3 pos)
{
	auto FPSTimer = std::make_shared<dae::GameObject>();
	auto FpsFont = dae::ResourceManager::GetInstance().LoadFont("Font/Lingua.otf", 24);
	FPSTimer->SetWorldPosition(pos);
	FPSTimer->AddComponent<TextComponent>()->SetFont(FpsFont);
	FPSTimer->GetComponent<TextComponent>()->SetColor({ 0,255,0,255 });
	FPSTimer->AddComponent<FPSComponent>();
	scene.Add(FPSTimer);
}

void SceneSwitcher::AddPeterPepper(dae::Scene& scene, glm::vec3 pos)
{
	m_PeterPepper.StartPos = pos;
	if (!m_FirstLoad)
	{
		m_PeterPepper.Object->GetComponent<RigidBody>()->RemakeCol();
		m_PeterPepper.Object->SetWorldPosition(m_PeterPepper.StartPos);
		m_PeterPepper.Object->GetComponent<RigidBody>()->ResetPos();
	}
	else
	{
		m_PeterPepper.Object = std::make_shared<dae::GameObject>();
		m_PeterPepper.Object->SetWorldPosition(m_PeterPepper.StartPos);
		m_PeterPepper.Object->AddComponent<ImageComponent>()->SetTexture("Sprites/PeterPepper.png");
		m_PeterPepper.Object->GetComponent<ImageComponent>()->MakeAnimated(2, 9, 6);
		m_PeterPepper.Object->GetComponent<ImageComponent>()->SetStartFrame(3);
		m_PeterPepper.Object->AddComponent<MovementComponent>()->SetMovementSpeed({ 75,50 });
		m_PeterPepper.Object->GetComponent<ImageComponent>()->SetDimensions(40, 40);
		m_PeterPepper.Object->GetComponent<ImageComponent>()->SetFramesPerSecond(15);
		m_PeterPepper.Object->AddComponent<PeterPepperComponent>();
	}
	m_PeterPepper.Object->AddComponent<RigidBody>()->SetSize({ 28,35 });
	m_PeterPepper.Object->GetComponent<RigidBody>()->SetTag("Player");
	m_PeterPepper.Object->GetComponent<RigidBody>()->OverlapWithTag({ "Enemy" , "Ingredient","Ladder" });
	m_PeterPepper.Object->GetComponent<RigidBody>()->SetCollision(PhysicsManager::CollisionType::TRIGGER);
	m_PeterPepper.Object->GetComponent<RigidBody>()->SetVisible(true);
	scene.Add(m_PeterPepper.Object);
}

void SceneSwitcher::AddMrsSalt(dae::Scene& scene, glm::vec3 pos)
{
	m_Salt.StartPos = pos;
	if (!m_FirstLoad)
	{
		m_Salt.Object->GetComponent<RigidBody>()->RemakeCol();
	}
	else
	{
		m_Salt.Object = std::make_shared<dae::GameObject>();
		m_Salt.Object->AddComponent<ImageComponent>()->SetTexture("Sprites/PeterPepper.png");
		m_Salt.Object->GetComponent<ImageComponent>()->MakeAnimated(2, 9, 6);
		m_Salt.Object->GetComponent<ImageComponent>()->SetStartFrame(3);
		m_Salt.Object->AddComponent<MovementComponent>()->SetMovementSpeed({ 75,50 });
		m_Salt.Object->GetComponent<ImageComponent>()->SetDimensions(40, 40);
		m_Salt.Object->GetComponent<ImageComponent>()->SetFramesPerSecond(15);
		m_Salt.Object->AddComponent<PeterPepperComponent>();
	}
	m_Salt.Object->SetWorldPosition(m_Salt.StartPos);
	m_Salt.Object->AddComponent<RigidBody>()->SetSize({ 28,39 });
	m_Salt.Object->GetComponent<RigidBody>()->SetTag("Player");
	m_Salt.Object->GetComponent<RigidBody>()->OverlapWithTag({ "Enemy" , "Ingredient","Ladder" });
	m_Salt.Object->GetComponent<RigidBody>()->SetCollision(PhysicsManager::CollisionType::TRIGGER);
	m_Salt.Object->GetComponent<RigidBody>()->ResetPos();
	m_Salt.Object->SetActive(false);
	scene.Add(m_Salt.Object);

	if (m_CurrGameMode == GameMode::COOP && m_Salt.Object->GetComponent<PeterPepperComponent>()->GetLives() != 0)
		m_Salt.Object->SetActive(true);
	else m_Salt.Object->SetActive(false);
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
	m_Enemies.emplace_back(sausage);
	scene.Add(sausage.Object);

	sausage.Object->GetComponent<EnemyComponent>()->GetSubject()->AddObserver(m_PeterPepper.Object->GetComponent<PeterPepperComponent>());
	sausage.Object->GetComponent<EnemyComponent>()->GetSubject()->AddObserver(m_Salt.Object->GetComponent<PeterPepperComponent>());
	sausage.Object->GetComponent<EnemyComponent>()->GetSubject()->AddObserver(this);
}

void SceneSwitcher::AddEgg(dae::Scene& scene, glm::vec3 pos)
{
	AddSausage(scene, pos);
	auto& egg = m_Enemies[m_Enemies.size() - 1];
	egg.Object->GetComponent<ImageComponent>()->SetTexture("Sprites/Egg.png");
	egg.Object->GetComponent<EnemyComponent>()->SetType(EnemyComponent::Type::Egg);
}

void SceneSwitcher::AddPickle(dae::Scene& scene, glm::vec3 pos)
{
	AddSausage(scene, pos);
	auto& pickle = m_Enemies[m_Enemies.size() - 1];
	pickle.Object->GetComponent<ImageComponent>()->SetTexture("Sprites/Pickle.png");
	pickle.Object->GetComponent<EnemyComponent>()->SetType(EnemyComponent::Type::Pickle);
}

void SceneSwitcher::AddPlayerSausage(dae::Scene& scene, glm::vec3 pos)
{
	m_PlayerSausage.StartPos = pos;
	if (!m_FirstLoad)
	{
		m_PlayerSausage.Object->GetComponent<RigidBody>()->RemakeCol();
	}
	else
	{
		m_PlayerSausage.Object = std::make_shared<dae::GameObject>();
		m_PlayerSausage.Object->SetWorldPosition(m_PlayerSausage.StartPos);
		m_PlayerSausage.Object->AddComponent<EnemyComponent>()->SetTarget(m_PeterPepper.Object.get());
		m_PlayerSausage.Object->GetComponent<EnemyComponent>()->SetPlayer(true);
		m_PlayerSausage.Object->AddComponent<MovementComponent>()->SetMovementSpeed({ 50,40 });
		m_PlayerSausage.Object->AddComponent<ImageComponent>()->SetTexture("Sprites/Sausage.png");
		m_PlayerSausage.Object->GetComponent<ImageComponent>()->SetDimensions(40, 40);
		m_PlayerSausage.Object->GetComponent<ImageComponent>()->MakeAnimated(2, 6, 3);
		m_PlayerSausage.Object->GetComponent<ImageComponent>()->SetStartFrame(2);
		m_PlayerSausage.Object->GetComponent<ImageComponent>()->SetFramesPerSecond(10);

		m_PlayerSausage.Object->GetComponent<EnemyComponent>()->GetSubject()->AddObserver(m_PeterPepper.Object->GetComponent<PeterPepperComponent>());
		m_PlayerSausage.Object->GetComponent<EnemyComponent>()->GetSubject()->AddObserver(m_Salt.Object->GetComponent<PeterPepperComponent>());
	}

	m_PlayerSausage.Object->SetWorldPosition(m_PlayerSausage.StartPos);
	m_PlayerSausage.Object->AddComponent<RigidBody>()->SetSize({ 28,36 });
	m_PlayerSausage.Object->GetComponent<RigidBody>()->SetTag("Enemy");
	m_PlayerSausage.Object->GetComponent<RigidBody>()->OverlapWithTag({ "Player" , "Ingredient","Ladder","Pepper" });
	m_PlayerSausage.Object->GetComponent<RigidBody>()->SetCollision(PhysicsManager::CollisionType::TRIGGER);
	m_PlayerSausage.Object->GetComponent<RigidBody>()->ResetPos();
	scene.Add(m_PlayerSausage.Object);

	if (m_CurrGameMode == GameMode::PVP)
		m_PlayerSausage.Object->SetActive(true);
	else m_PlayerSausage.Object->SetActive(false);
	m_PlayerSausage.Object->GetComponent<EnemyComponent>()->GetSubject()->AddObserver(this);
}

void SceneSwitcher::AddText(dae::Scene& scene)
{
	if (!m_FirstLoad)
	{
		scene.Add(m_PPLivesText);
		scene.Add(m_PPScoreText);
		scene.Add(m_HighScoreText);
		scene.Add(m_PPPeppersText);

		if (m_CurrGameMode == GameMode::COOP)
		{
			scene.Add(m_SaltLivesText);
			scene.Add(m_SaltPeppersText);
		}
		return;
	}
	auto pp = m_PeterPepper.Object->GetComponent<PeterPepperComponent>();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Font/Lingua.otf", 24);

	m_PPLivesText = std::make_shared<dae::GameObject>();
	auto life = m_PPLivesText->AddComponent<TextComponent>();
	life->SetText("Lives: 3");
	life->SetFont(font);
	auto ppLives = m_PPLivesText->AddComponent<LivesComponent>();
	scene.Add(m_PPLivesText);
	//m_PPLivesText->AddComponent<HighScoreComponent>();

	pp->GetSubject()->AddObserver(ppLives);

	m_PPScoreText = std::make_shared<dae::GameObject>();
	m_PPScoreText->SetWorldPosition({ 0,20,0 });
	auto score = m_PPScoreText->AddComponent<TextComponent>();

	score->SetText("Score: 0");
	score->SetFont(font);
	auto ppScore = m_PPScoreText->AddComponent<ScoreComponent>();
	scene.Add(m_PPScoreText);

	pp->GetSubject()->AddObserver(ppScore);

	auto salt = m_Salt.Object->GetComponent<PeterPepperComponent>();

	m_SaltLivesText = std::make_shared<dae::GameObject>();
	m_SaltLivesText->SetWorldPosition({ 200,0,0 });
	auto saltLifeText = m_SaltLivesText->AddComponent<TextComponent>();
	saltLifeText->SetText("Lives: 3");
	saltLifeText->SetFont(font);
	auto saltLives = m_SaltLivesText->AddComponent<LivesComponent>();
	if (m_CurrGameMode == GameMode::COOP)
		scene.Add(m_SaltLivesText);

	salt->GetSubject()->AddObserver(saltLives);

	m_HighScoreText = std::make_shared<dae::GameObject>();
	m_HighScoreText->SetWorldPosition({ 300,0,0 });
	auto highText = m_HighScoreText->AddComponent<TextComponent>();
	highText->SetFont(font);
	auto highScoreComp = m_HighScoreText->AddComponent < HighScoreComponent >();
	highScoreComp->UpdateHighScore(0);
	scene.Add(m_HighScoreText);

	m_PeterPepper.Object->GetComponent<PeterPepperComponent>()->GetSubject()->AddObserver(highScoreComp);

	m_PPPeppersText = std::make_shared<dae::GameObject>();
	m_PPPeppersText->SetWorldPosition({ 100,50,0 });
	auto pepperText = m_PPPeppersText->AddComponent<TextComponent>();
	pepperText->SetFont(font);
	pepperText->SetText("Peppers: 5");
	auto peppercomp = m_PPPeppersText->AddComponent < PepperTextComponent >();
	scene.Add(m_PPPeppersText);

	m_PeterPepper.Object->GetComponent<PeterPepperComponent>()->GetSubject()->AddObserver(peppercomp);

	m_SaltPeppersText = std::make_shared<dae::GameObject>();
	m_SaltPeppersText->SetWorldPosition({ 220,50,0 });
	auto saltText = m_SaltPeppersText->AddComponent<TextComponent>();
	saltText->SetFont(font);
	saltText->SetText("Peppers: 5");
	auto saltComp = m_SaltPeppersText->AddComponent < PepperTextComponent >();
	if (m_CurrGameMode == GameMode::COOP)
		scene.Add(m_SaltPeppersText);

	m_Salt.Object->GetComponent<PeterPepperComponent>()->GetSubject()->AddObserver(saltComp);
}

void SceneSwitcher::HandleRespawnEnemies()
{
	if (!m_PlayerSausage.Object->IsActive() && m_CurrGameMode == GameMode::PVP)
	{
		m_PlayerSausage.Object->SetWorldPosition(m_PlayerSausage.StartPos);
		m_PlayerSausage.Object->SetActive(true);
		m_PlayerSausage.Object->GetComponent<RigidBody>()->ResetPos();
	}
	for (const auto& enemy : m_Enemies)
	{
		if (enemy.Object->IsActive()) continue;

		enemy.Object->SetWorldPosition(enemy.StartPos);
		enemy.Object->SetActive(true);
		enemy.Object->GetComponent<RigidBody>()->ResetPos();
	}
}