#pragma once
#include "GameObject.h"
#include "MovementComponent.h"
#include "PeterPepperComponent.h"
#include "SceneSwitcher.h"

class Command
{
public:
	explicit Command(std::shared_ptr<dae::GameObject> gameActor) { m_GameActor = gameActor; }
	virtual ~Command() = default;
	virtual bool Execute() = 0;
	//virtual void Undo() = 0;
protected:
	std::shared_ptr<dae::GameObject> m_GameActor{ nullptr };
};

class QuitCommand : public Command
{
public:
	QuitCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	bool Execute() override { return false; }
};

class MoveRightCommand : public Command
{
public:
	MoveRightCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	bool Execute() override { m_GameActor->GetComponent<MovementComponent>()->MoveRight(); return true; }
};
class MoveLeftCommand : public Command
{
public:
	MoveLeftCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	bool Execute() override { m_GameActor->GetComponent<MovementComponent>()->MoveLeft(); return true; }
};
class MoveUpCommand : public Command
{
public:
	MoveUpCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	bool Execute() override
	{
		m_GameActor->GetComponent<MovementComponent>()->MoveUp(); return true;
	}
};
class MoveDownCommand : public Command
{
public:
	MoveDownCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	bool Execute() override { m_GameActor->GetComponent<MovementComponent>()->MoveDown(); return true; }
};
class AttackCommand : public Command
{
public:
	AttackCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	bool Execute() override { m_GameActor->GetComponent<PeterPepperComponent>()->Attack(); return true; }
};
class LoadLevelOneCommand : public Command
{
public:
	LoadLevelOneCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	bool Execute() override { m_GameActor->GetComponent<SceneSwitcher>()->LoadLevel(1); return true; }
};
class LoadLevelTwoCommand : public Command
{
public:
	LoadLevelTwoCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	bool Execute() override { m_GameActor->GetComponent<SceneSwitcher>()->LoadLevel(2); return true; }
};
class LoadLevelThreeCommand : public Command
{
public:
	LoadLevelThreeCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	bool Execute() override { m_GameActor->GetComponent<SceneSwitcher>()->LoadLevel(3); return true; }
};
class SwitchToCoopCommand : public Command
{
public:
	SwitchToCoopCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	bool Execute() override { m_GameActor->GetComponent<SceneSwitcher>()->SwitchGameMode(SceneSwitcher::GameMode::COOP); return true; }
};
class SwitchToPvpCommand : public Command
{
public:
	SwitchToPvpCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	bool Execute() override { m_GameActor->GetComponent<SceneSwitcher>()->SwitchGameMode(SceneSwitcher::GameMode::PVP); return true; }
};
class SwitchToSingleCommand : public Command
{
public:
	SwitchToSingleCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	bool Execute() override { m_GameActor->GetComponent<SceneSwitcher>()->SwitchGameMode(SceneSwitcher::GameMode::SINGLE); return true; }
};