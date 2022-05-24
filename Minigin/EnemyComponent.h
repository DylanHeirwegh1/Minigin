#pragma once
#include "BaseComponent.h"

#include "ImageComponent.h"
#include "MovementComponent.h"

class EnemyComponent : public BaseComponent
{
public:
	void Update() override;
	void Render() override;
	void SetTarget(dae::GameObject* target);

private:
	void HandleMovement();
	void HandleInteractions();
	void HandleSprite(MovementComponent::MovementState state);
	dae::GameObject* m_Target{ nullptr };
	MovementComponent* m_MovementComponent = nullptr;
	ImageComponent* m_ImageComponent = nullptr;
	RigidBody* m_Rb = nullptr;

	MovementComponent::MovementState m_CurrentState = MovementComponent::MovementState::Idle;
};
