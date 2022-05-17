#pragma once
#include "BaseComponent.h"

class PeterPepperComponent : public BaseComponent
{
public:
	void Render() override;
	void Update() override;
	void Die();
	void AddScore();
	const int GetLives() { return m_Lives; };
	const int GetScore() { return m_Score; }
	virtual Subject* GetSubject() const { return m_ActorChanged.get(); };


private:
	std::unique_ptr<Subject> m_ActorChanged{ std::make_unique<Subject>() };
	int m_Lives = 3;
	int m_Score = 0;

};

