#include "MiniginPCH.h"
#include "EnemyComponent.h"

#include "ImageComponent.h"
#include "MovementComponent.h"
#include "PhysicsManager.h"

void EnemyComponent::Update()
{
	if (!m_MovementComponent) m_MovementComponent = m_Owner->GetComponent<MovementComponent>();
	if (!m_ImageComponent) m_ImageComponent = m_Owner->GetComponent<ImageComponent>();
	if (!m_Rb) m_Rb = m_Owner->GetComponent<RigidBody>();

	HandleMovement();
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

void EnemyComponent::HandleMovement()
{
	auto target = m_Target->GetWorldPosition();
	auto myPos = m_Owner->GetWorldPosition();
	float epsilon = 1.f;

	if (!m_MovementComponent) return;
	if (target.x < myPos.x) m_MovementComponent->MoveLeft();
	else m_MovementComponent->MoveRight();

	if (target.y < myPos.y - epsilon) m_MovementComponent->MoveUp();
	else if (target.y > myPos.y + epsilon) m_MovementComponent->MoveDown();
}

void EnemyComponent::HandleInteractions()
{
	auto overlappers = m_Rb->GetOverlappersWithTag("Ingredient");
	if (overlappers.size() == 0) return;
	for (auto overlapper : overlappers)
	{
		if (overlapper->GetComponent<MovementComponent>()->GetCurrentState() == MovementComponent::MovementState::GoingDown)
		{
			m_Owner->SetActive(false);
		}
	}
}

void EnemyComponent::HandleSprite(MovementComponent::MovementState state)
{
	if (m_CurrentState == MovementComponent::MovementState::GoingRight) m_ImageComponent->FlipTexture(SDL_FLIP_NONE);

	//switch texture settings for each state
	switch (state)
	{
	case MovementComponent::MovementState::GoingDown:
		m_ImageComponent->SetStartFrame(4);
		m_ImageComponent->SetEndFrame(5);

		break;
	case MovementComponent::MovementState::GoingUp:
		m_ImageComponent->SetStartFrame(0);
		m_ImageComponent->SetEndFrame(1);
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