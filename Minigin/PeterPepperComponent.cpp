#include "MiniginPCH.h"
#include "PeterPepperComponent.h"

#include "ImageComponent.h"

void PeterPepperComponent::Render()
{
}

void PeterPepperComponent::Update()
{
	HandleStateUpdate();
}

void PeterPepperComponent::Die()
{
	--m_Lives;
	m_ActorChanged->Notify(*m_Owner, Event::ActorDied);
}

void PeterPepperComponent::AddScore()
{
	m_Score += 100;
	m_ActorChanged->Notify(*m_Owner, Event::EnemyCrushed);
}

void PeterPepperComponent::HandleStateUpdate()
{
	auto mov = m_Owner->GetComponent<MovementComponent>();
	if (!mov) return;
	auto newState = mov->GetCurrentState();
	if (m_CurrentState == newState) return;

	auto sprite = m_Owner->GetComponent<ImageComponent>();
	if (!sprite) return;

	if (m_CurrentState == MovementComponent::MovementState::GoingRight) sprite->FlipTexture(SDL_FLIP_NONE);

	switch (newState)
	{
	case MovementComponent::MovementState::GoingDown:

		break;
	case MovementComponent::MovementState::GoingUp:

		break;
	case MovementComponent::MovementState::GoingLeft:

		break;
	case MovementComponent::MovementState::GoingRight:
		sprite->FlipTexture(SDL_FLIP_HORIZONTAL);

		break;
	case MovementComponent::MovementState::Idle:
		break;
	}
	m_CurrentState = newState;
}