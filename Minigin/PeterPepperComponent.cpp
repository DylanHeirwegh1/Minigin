#include "MiniginPCH.h"
#include "PeterPepperComponent.h"

#include "ImageComponent.h"

void PeterPepperComponent::Render()
{
}

void PeterPepperComponent::Update()
{
	HandleStateUpdate();
	HandleEnemyCollision();
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

	//switch texture settings for each state
	switch (newState)
	{
	case MovementComponent::MovementState::GoingDown:
		sprite->SetStartFrame(0);
		sprite->SetEndFrame(2);

		break;
	case MovementComponent::MovementState::GoingUp:
		sprite->SetStartFrame(6);
		sprite->SetEndFrame(8);
		break;
	case MovementComponent::MovementState::GoingLeft:
		sprite->SetStartFrame(3);
		sprite->SetEndFrame(5);
		break;
	case MovementComponent::MovementState::GoingRight:
		sprite->FlipTexture(SDL_FLIP_HORIZONTAL);
		sprite->SetStartFrame(3);
		sprite->SetEndFrame(5);
		break;
	case MovementComponent::MovementState::Idle:
		sprite->SetStartFrame(1);
		sprite->SetEndFrame(1);
		break;
	}
	m_CurrentState = newState;
}

void PeterPepperComponent::HandleEnemyCollision()
{
	auto rb = m_Owner->GetComponent<RigidBody>();
	if (!rb) return;

	for (auto element : rb->GetOverlapperTags())
	{
		if (element == "Enemy")
		{
			Die();
			return;
		}
	}
}