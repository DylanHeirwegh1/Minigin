#pragma once
#include "BaseComponent.h"
#include "MovementComponent.h"

class PeterPepperComponent : public BaseComponent, public Observer
{
public:
	void Render() override;
	void Update() override;
	void Die();
	const int GetLives() { return m_Lives; }
	const int GetScore() { return m_Score; }
	const int GetPepper() { return m_Peppers; }
	Subject* GetSubject() const { return m_Subject.get(); };
	void Attack();
	void Notify(const dae::GameObject& actor, Event event) override;
	void GameReset() { m_Lives = 3; m_Score = 0; m_Peppers = 5; }

private:
	void HandleDeath();
	void AddScore(int score);
	void InitSound();
	void HandleAttackRate();
	void DetermineDirection(std::shared_ptr<dae::GameObject> game);
	std::unique_ptr<Subject> m_Subject{ std::make_unique<Subject>() };
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
	bool m_AddedSound{ false };
	int m_SoundID = 0;
	int m_WalkSoundId = 0;
	bool m_Dead = false;
	float m_DeathAccuTime = 0.f;;
};
