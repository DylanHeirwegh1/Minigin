#include "pch.h"
#include "EnemyComponent.h"

#include "ImageComponent.h"
#include "MovementComponent.h"
#include "PhysicsManager.h"
#include "Timer.h"

void EnemyComponent::Update()
{
	HandleStunTimer();
	HandleDeath();
	if (!m_MovementComponent) m_MovementComponent = m_Owner->GetComponent<MovementComponent>();
	if (!m_ImageComponent) m_ImageComponent = m_Owner->GetComponent<ImageComponent>();
	if (!m_Rb) m_Rb = m_Owner->GetComponent<RigidBody>();

	if (!m_Stunned)HandleMovement();

	HandleInteractions();
	HandleSprite(m_MovementComponent->GetCurrentState());
}
void EnemyComponent::Render()
{
}
void EnemyComponent::SetTarget(dae::GameObject* target)
{
	m_Target = target;
}
void EnemyComponent::Die()
{
	if (m_Dead)return;
	m_Dead = true;

	switch (m_Type)
	{
	case Type::Hotdog:
		m_Subject->Notify(*m_Owner, Event::HotDogDied);
		break;
	case Type::Egg:
		m_Subject->Notify(*m_Owner, Event::EggDied);
		break;
	case Type::Pickle:
		m_Subject->Notify(*m_Owner, Event::PickleDied);
		break;
	}
}
void EnemyComponent::Stun()
{
	m_Stunned = true;
}
void EnemyComponent::HandleMovement()
{
	if (!m_MovementComponent) return;
	if (m_IsPlayer) return;

	auto target = m_Target->GetWorldPosition();
	auto myPos = m_Owner->GetWorldPosition();

	HandleXMovement(myPos, target);
	HandleYMovement(myPos, target);
}
void EnemyComponent::HandleInteractions()
{
	auto overlappers = m_Rb->GetOverlappersWithTag("Ingredient");
	if (overlappers.size() == 0) return;
	for (const auto& overlapper : overlappers)
	{
		if (overlapper->GetComponent<MovementComponent>()->GetCurrentState() == MovementComponent::MovementState::GoingDown)
		{
			Die();
		}
	}
}
void EnemyComponent::HandleSprite(MovementComponent::MovementState state)
{
	if (m_Dead)
	{
		m_ImageComponent->SetStartFrame(6);
		m_ImageComponent->SetEndFrame(9);
		return;
	}
	if (m_Stunned)
	{
		m_ImageComponent->SetStartFrame(10);
		m_ImageComponent->SetEndFrame(11);
		return;
	}
	if (m_CurrentState == MovementComponent::MovementState::GoingRight) m_ImageComponent->FlipTexture(SDL_FLIP_NONE);

	//switch texture settings for each state
	switch (state)
	{
	case MovementComponent::MovementState::GoingDown:
		m_ImageComponent->SetStartFrame(0);
		m_ImageComponent->SetEndFrame(1);

		break;
	case MovementComponent::MovementState::GoingUp:
		m_ImageComponent->SetStartFrame(4);
		m_ImageComponent->SetEndFrame(5);
		break;
	case MovementComponent::MovementState::GoingLeft:
		m_ImageComponent->SetStartFrame(2);
		m_ImageComponent->SetEndFrame(3);
		break;
	case MovementComponent::MovementState::GoingRight:
		m_ImageComponent->FlipTexture(SDL_FLIP_HORIZONTAL);
		m_ImageComponent->SetStartFrame(2);
		m_ImageComponent->SetEndFrame(3);
		break;
	case MovementComponent::MovementState::Idle:
		m_ImageComponent->SetStartFrame(2);
		m_ImageComponent->SetEndFrame(3);
		break;
	}
	m_CurrentState = state;
}
void EnemyComponent::HandleXMovement(const glm::vec3& myPos, const glm::vec3& target)
{
	float epsilon = 0.5f;

	if (m_ChoseRandomDirectionX)
		if (m_RandIsLeft)
			m_MovementComponent->MoveLeft();
		else
			m_MovementComponent->MoveRight();
	else
	{
		if (abs(myPos.x - target.x) <= epsilon)
		{
			m_ChoseRandomDirectionX = true;
			if (rand() % 2 == 0)
			{
				m_MovementComponent->MoveLeft();
				m_RandIsLeft = true;
			}
			else
			{
				m_MovementComponent->MoveRight();
				m_RandIsLeft = false;
			}
		}
		else if (target.x < myPos.x) m_MovementComponent->MoveLeft();
		else m_MovementComponent->MoveRight();
	}
}
void EnemyComponent::HandleYMovement(const glm::vec3& myPos, const glm::vec3& target)
{
	float epsilon = 0.5f;
	if (!m_MovementComponent->IsOnLadder(0))
	{
		m_ChoseRandomDirectionY = false;
		m_CanRefreshY = true;
		return;
	}
	else m_ChoseRandomDirectionX = false;

	if (m_ChoseRandomDirectionY)
	{
		if (m_RandIsUp)m_MovementComponent->MoveUp();
		else m_MovementComponent->MoveDown();
	}
	else
	{
		if (abs(myPos.y - target.y) <= epsilon && !m_MovementComponent->IsGrounded(-1))
		{
			if (!m_CanRefreshY)return;
			m_CanRefreshY = false;
			m_ChoseRandomDirectionY = true;
			if (rand() % 2 == 0)
			{
				m_MovementComponent->MoveDown();
				m_RandIsUp = false;
			}
			else
			{
				m_MovementComponent->MoveUp();
				m_RandIsUp = true;
			}
		}
		else if (myPos.y < target.y)
			m_MovementComponent->MoveDown();
		else
			m_MovementComponent->MoveUp();
	}
}
void EnemyComponent::HandleStunTimer()
{
	if (!m_Stunned)return;
	float max = 3.f;

	m_AccuTime += Timer::GetInstance().GetElapsedSeconds();
	if (max < m_AccuTime)
	{
		m_Stunned = false;
		m_AccuTime = 0.f;
	}
}
void EnemyComponent::HandleDeath()
{
	if (!m_Dead)return;
	float delay = .4f;
	m_DeathAccuTime += Timer::GetInstance().GetElapsedSeconds();
	if (m_DeathAccuTime > delay)
	{
		m_Owner->SetActive(false);
		m_DeathAccuTime = 0.f;
		m_Dead = false;
		m_Subject->Notify(*m_Owner, Event::EnemyDied);
	}
}