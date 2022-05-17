#include "MiniginPCH.h"
#pragma once
#include "GameObject.h"
class Command
{

public:
	explicit Command(std::shared_ptr<dae::GameObject> gameActor) { m_GameActor = gameActor; }
	virtual ~Command() = default;
	virtual void Execute() = 0;
	//virtual void Undo() = 0;
protected:
	std::shared_ptr<dae::GameObject> m_GameActor{ nullptr };
};

class FireCommand : public Command
{
public:
	FireCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	void Execute() override { /*m_GameActor->Fire();*/ }
};
class JumpCommand : public Command
{
public:
	JumpCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	void Execute() override { /*m_GameActor->Jump();*/ }
};

class DuckCommand : public Command
{
public:
	DuckCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	void Execute() override { /*m_GameActor->Duck();*/ }
};
class FartCommand : public Command
{
public:
	FartCommand(std::shared_ptr<dae::GameObject> gameActor) : Command(gameActor) {}
	void Execute() override { /*m_GameActor->Fart();*/ }
};