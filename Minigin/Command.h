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

class DieCommand : public Command
{
public:
	DieCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	bool Execute() override {
		m_GameActor->GetComponent<PeterPepperComponent>()->Die(); return true;
	}
};
class AddScoreCommand : public Command
{
public:
	AddScoreCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	bool Execute() override { m_GameActor->GetComponent<PeterPepperComponent>()->AddScore(); return true; }
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
	bool Execute() override { m_GameActor->GetComponent<MovementComponent>()->MoveUp(); return true; }
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
	bool Execute() override { m_GameActor->GetComponent<SceneSwitcher>()->LoadLevel1(); return true; }
};
class LoadLevelTwoCommand : public Command
{
public:
	LoadLevelTwoCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	bool Execute() override { m_GameActor->GetComponent<SceneSwitcher>()->LoadLevel2(); return true; }
};
class LoadLevelThreeCommand : public Command
{
public:
	LoadLevelThreeCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	bool Execute() override { m_GameActor->GetComponent<SceneSwitcher>()->LoadLevel3(); return true; }
};