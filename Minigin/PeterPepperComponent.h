#pragma once
#include "BaseComponent.h"
#include "MovementComponent.h"

class PeterPepperComponent : public BaseComponent
{
public:
	void Render() override;
	void Update() override;
	void Die();
	void AddScore();
	const int GetLives() { return m_Lives; };
	const int GetScore() { return m_Score; }
	Subject* GetSubject() const { return m_ActorChanged.get(); };
	void Attack();

private:

	void HandleAttackRate();
	void DetermineDirection(std::shared_ptr<dae::GameObject> game);
	std::unique_ptr<Subject> m_ActorChanged{ std::make_unique<Subject>() };
	int m_Lives = 3;
	int m_Score = 0;
	int m_Peppers = 5;
	MovementComponent::MovementState m_CurrentState = MovementComponent::MovementState::Idle;
	void HandleStateUpdate();
	void HandleEnemyCollision();
	float m_AttackTime = 1;
	float m_AttackAccuTime = 0.f;
	bool m_CanAttack = true;
	bool m_CanHandleStates = true;
	MovementComponent* m_Movement = nullptr;
};
