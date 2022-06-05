#pragma once
#include "BaseComponent.h"

#include "ImageComponent.h"
#include "MovementComponent.h"

class EnemyComponent : public BaseComponent
{
public:
	enum class Type
	{
		Hotdog,
		Egg,
		Pickle
	};
	void Update() override;
	void Render() override;
	void SetTarget(dae::GameObject* target);
	void Die();
	void Stun();
	bool IsStunned() { return m_Stunned; }
	void SetPlayer(bool value) { m_IsPlayer = value; }
	Subject* GetSubject() const { return m_Subject.get(); };
	void SetType(Type type) { m_Type = type; }

private:
	void HandleMovement();
	void HandleInteractions();
	void HandleSprite(MovementComponent::MovementState state);
	dae::GameObject* m_Target{ nullptr };
	MovementComponent* m_MovementComponent = nullptr;
	ImageComponent* m_ImageComponent = nullptr;
	RigidBody* m_Rb = nullptr;

	MovementComponent::MovementState m_CurrentState = MovementComponent::MovementState::Idle;

	bool m_ChoseRandomDirectionY = false;
	bool m_ChoseRandomDirectionX = false;
	bool m_RandIsUp = false;
	bool m_RandIsLeft = false;
	bool m_CanRefreshY = true;
	bool m_Stunned = false;
	bool m_Dead = false;
	bool m_IsPlayer = false;
	float  m_AccuTime = 0.f;
	float m_DeathAccuTime = 0.f;

	void HandleXMovement(const glm::vec3& myPos, const glm::vec3& target);
	void HandleYMovement(const glm::vec3& myPos, const glm::vec3& target);
	void HandleStunTimer();
	void HandleDeath();
	Type m_Type{ Type::Hotdog };
	std::unique_ptr<Subject> m_Subject{ std::make_unique<Subject>() };
};
