#pragma once
#include "BaseComponent.h"
#include "RigidBody.h"
#include "glm/glm.hpp"
#include "SDL.h"
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
	void Fall();
	MovementState GetCurrentState();
	bool IsGrounded(float posX);
	bool IsOnLadder(float yOffset);
	void Freeze(bool val);
private:
	void EditOwnerPos(float x, float y = 0);

	void DetermineState();

	glm::vec2 m_MovementSpeed{ 100,100 };
	MovementState m_State = MovementState::Idle;
	bool m_OnLadder = false;
	RigidBody* m_Rb{ nullptr };
	bool m_CanWalk{ true };
};
