#pragma once
#include "BaseComponent.h"
#include "RigidBody.h"

class MovementComponent : public BaseComponent
{
public:
	enum class MovementState
	{
		GoingUp = 0,
		GoingDown = 1,
		GoingRight = 2,
		GoingLeft = 3,
		Idle = 4
	};
	void Update() override;
	void Render() override {};
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	void SetMovementSpeed(glm::vec2 vel) { m_MovementSpeed = vel; }
	MovementState GetCurrentState();

private:

	void EditOwnerPos(float x, float y = 0);
	void CalcVelocity();
	void DetermineState();

	glm::vec2 m_MovementSpeed{ 100,100 };
	MovementState m_State = MovementState::Idle;

	glm::vec2 m_Velocity{ 0.f,0.f };
	glm::vec2 m_PrevPos{ 0.f,0.f };
	RigidBody* m_Rb{ nullptr };
};
