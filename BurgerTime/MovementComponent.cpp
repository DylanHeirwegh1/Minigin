#include "pch.h"
#include "MovementComponent.h"

#include "ImageComponent.h"
#include "Timer.h"
#include <SDL_rect.h>

void MovementComponent::Update()
{
	DetermineState();
}

void MovementComponent::MoveRight()
{
	float offset = m_MovementSpeed.x * Timer::GetInstance().GetElapsedSeconds();
	if (IsGrounded(offset + m_Owner->GetWorldPosition().x))
		EditOwnerPos(offset);
}

void MovementComponent::MoveLeft()
{
	float offset = -m_MovementSpeed.x * Timer::GetInstance().GetElapsedSeconds();
	if (IsGrounded(offset + m_Owner->GetWorldPosition().x))
		EditOwnerPos(offset);
}

void MovementComponent::MoveUp()
{
	float offset = -m_MovementSpeed.y * Timer::GetInstance().GetElapsedSeconds();
	if (IsOnLadder(offset))
		EditOwnerPos(0, offset);
}

void MovementComponent::MoveDown()
{
	float offset = m_MovementSpeed.y * Timer::GetInstance().GetElapsedSeconds();
	if (IsOnLadder(offset))
		EditOwnerPos(0, offset);
}

void MovementComponent::Fall()
{
	EditOwnerPos(0, m_MovementSpeed.y * Timer::GetInstance().GetElapsedSeconds());
}

MovementComponent::MovementState MovementComponent::GetCurrentState()
{
	return m_State;
}

bool MovementComponent::IsGrounded(float posX)
{
	auto blocks = PhysicsManager::GetInstance().GetColsWithTag("Block");
	auto posY = m_Owner->GetWorldPosition().y;
	for (auto& block : blocks)
	{
		auto r = SDL_Rect{ static_cast<int>(block.x), static_cast<int>(block.y), static_cast<int>(block.z),
			static_cast<int>(block.w) };

		int x1{ static_cast<int>(posX) }, y1{ static_cast<int>(posY) }, x2{ x1 }, y2{ y1 + 1 };

		if (SDL_IntersectRectAndLine(&r, &x1, &y1, &x2, &y2))
		{
			return true;
		}
	}
	return false;
}

void MovementComponent::EditOwnerPos(float x, float y)
{
	//call the rigidbody and call the movement there
	if (!m_CanWalk)return;
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

bool MovementComponent::IsOnLadder(float yOffset)
{
	if (!m_Rb)
	{
		m_Rb = m_Owner->GetComponent<RigidBody>();
		return false;
	}

	auto obj = m_Rb->GetOverlappersWithTag("Ladder");
	if (obj.size() == 0)return false;

	auto otherRect = obj[0]->GetComponent<RigidBody>()->GetColRect();
	auto currRect = m_Rb->GetColRect();

	currRect.y += yOffset;
	if (yOffset > 0)//going down
	{
		currRect.y += currRect.w;
	}

	return (PhysicsManager::GetInstance().AreOverlapping(currRect, otherRect));
}

void MovementComponent::Freeze(bool val)
{
	m_CanWalk = !val;
}