#pragma once
#include "BaseComponent.h"

class MovementComponent : public BaseComponent
{
public:
	void Update() override;
	void Render() override {};
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
private:
	enum class State
	{
		GoingUp = 0,
		GoingDown = 1,
		GoingRight = 2,
		GoingLeft = 3,
		Idle = 4
	};

	void EditOwnerPos(float x, float y = 0);
	void CalcVelocity();
	void DetermineState();
	void UpdateSprite();
	glm::vec2 m_MovementSpeed{ 100,100 };
	State m_State = State::Idle;

	glm::vec2 m_Velocity{ 0.f,0.f };
	glm::vec2 m_PrevPos{ 0.f,0.f };
};