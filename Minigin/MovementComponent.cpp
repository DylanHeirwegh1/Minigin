#include "MiniginPCH.h"
#include "MovementComponent.h"

#include "ImageComponent.h"
#include "Timer.h"

void MovementComponent::Update()
{
	DetermineState();
}

void MovementComponent::MoveRight()
{
	//if (m_State == MovementState::GoingUp || m_State == MovementState::GoingDown) return;
	EditOwnerPos(m_MovementSpeed.x * Timer::GetInstance().GetElapsedSeconds());
}

void MovementComponent::MoveLeft()
{
	//if (m_State == MovementState::GoingUp || m_State == MovementState::GoingDown) return;
	EditOwnerPos(-m_MovementSpeed.x * Timer::GetInstance().GetElapsedSeconds());
}

void MovementComponent::MoveUp()
{
	//if (m_State == MovementState::GoingLeft || m_State == MovementState::GoingRight) return;
	EditOwnerPos(0, -m_MovementSpeed.y * Timer::GetInstance().GetElapsedSeconds());
}

void MovementComponent::MoveDown()
{
	//if (m_State == MovementState::GoingLeft || m_State == MovementState::GoingRight) return;
	EditOwnerPos(0, m_MovementSpeed.y * Timer::GetInstance().GetElapsedSeconds());
}

MovementComponent::MovementState MovementComponent::GetCurrentState()
{
	return m_State;
}

void MovementComponent::EditOwnerPos(float x, float y)
{
	//call the rigidbody and call the movement there
	if (m_Rb)m_Rb->Move(x, y);
}

void MovementComponent::DetermineState()
{
	if (!m_Rb)
	{
		m_Rb = m_Owner->GetComponent<RigidBody>();
		return;
	}
	const float x = m_Rb->GetVelocity().x;
	const float y = m_Rb->GetVelocity().y;

	if (m_Rb->GetVelocity() == glm::vec2{ 0, 0 })m_State = MovementState::Idle;
	else if (y > .1) m_State = MovementState::GoingDown;
	else if (y < -.1) m_State = MovementState::GoingUp;
	else if (x > .1) m_State = MovementState::GoingRight;
	else if (x < -.1) m_State = MovementState::GoingLeft;
}