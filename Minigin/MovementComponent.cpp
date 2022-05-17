#include "MiniginPCH.h"
#include "MovementComponent.h"

#include "ImageComponent.h"
#include "Timer.h"

void MovementComponent::Update()
{
	CalcVelocity();
	DetermineState();
}

void MovementComponent::MoveRight()
{
	if (m_State == MovementState::GoingUp || m_State == MovementState::GoingDown) return;
	EditOwnerPos(m_MovementSpeed.x * Timer::GetInstance().GetElapsedSeconds());
}

void MovementComponent::MoveLeft()
{
	if (m_State == MovementState::GoingUp || m_State == MovementState::GoingDown) return;
	EditOwnerPos(-m_MovementSpeed.x * Timer::GetInstance().GetElapsedSeconds());
}

void MovementComponent::MoveUp()
{
	if (m_State == MovementState::GoingLeft || m_State == MovementState::GoingRight) return;
	EditOwnerPos(0, -m_MovementSpeed.y * Timer::GetInstance().GetElapsedSeconds());
}

void MovementComponent::MoveDown()
{
	if (m_State == MovementState::GoingLeft || m_State == MovementState::GoingRight) return;
	EditOwnerPos(0, m_MovementSpeed.y * Timer::GetInstance().GetElapsedSeconds());
}

MovementComponent::MovementState MovementComponent::GetCurrentState()
{
	return m_State;
}

void MovementComponent::EditOwnerPos(float x, float y)
{
	auto pos = m_Owner->GetWorldPosition();
	pos.y += y;
	pos.x += x;
	m_Owner->SetWorldPosition(pos);
}

void MovementComponent::CalcVelocity()
{
	auto currP = m_Owner->GetWorldPosition();
	m_Velocity = { currP.x - m_PrevPos.x, currP.y - m_PrevPos.y };
	m_PrevPos = currP;
}

void MovementComponent::DetermineState()
{
	float x = m_Velocity.x;
	float y = m_Velocity.y;
	if (m_Velocity == glm::vec2{ 0, 0 })m_State = MovementState::Idle;
	else if (y > 0) m_State = MovementState::GoingDown;
	else if (y < 0) m_State = MovementState::GoingUp;
	else if (x > 0) m_State = MovementState::GoingRight;
	else if (x < 0) m_State = MovementState::GoingLeft;
}