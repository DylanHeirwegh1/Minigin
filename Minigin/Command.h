#pragma once
#include "GameObject.h"

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
