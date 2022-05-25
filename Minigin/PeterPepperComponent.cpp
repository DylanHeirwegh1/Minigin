#include "MiniginPCH.h"
#include "PeterPepperComponent.h"

#include "EnemyComponent.h"
#include "ImageComponent.h"
#include "PepperComponent.h"
#include "Scene.h"
#include "SceneManager.h"

void PeterPepperComponent::Render()
{
}

void PeterPepperComponent::Update()
{
	HandleAttackRate();
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

void PeterPepperComponent::Attack()
{
	if (!m_CanAttack || m_Peppers == 0)return;
	--m_Peppers;
	m_CanAttack = false;
	m_Movement->Freeze(true);
	auto& scene = dae::SceneManager::GetInstance().GetActiveScene();

	auto pepper = std::make_shared<dae::GameObject>();
	DetermineDirection(pepper);
	auto rb = pepper->AddComponent<RigidBody>();
	rb->SetSize({ 50,40 });
	rb->SetVisible(true);
	rb->SetTag("Pepper");
	rb->OverlapWithTag({ "Player", "Block", "Ladder","Enemy", "Ingredient" });
	rb->SetCollision(PhysicsManager::CollisionType::TRIGGER);
	auto p = pepper->AddComponent<PepperComponent>();

	auto img = pepper->AddComponent<ImageComponent>();
	img->SetTexture("Sprites/Salt.png");
	img->MakeAnimated(1, 4, 4);
	img->SetFramesPerSecond(4);
	img->SetDimensions(50, 40);

	if (m_Owner->GetComponent<MovementComponent>()->GetCurrentState() == MovementComponent::MovementState::GoingRight)
		img->FlipTexture(SDL_FLIP_HORIZONTAL);
	auto id = scene.Add(pepper);
	p->SetId(id);
}

void PeterPepperComponent::HandleAttackRate()
{
	if (m_CanAttack) return;
	m_AttackAccuTime += Timer::GetInstance().GetElapsedSeconds();
	if (m_AttackAccuTime > m_AttackTime)
	{
		m_AttackAccuTime = 0.f;
		m_CanAttack = true;
		m_CanHandleStates = true;
		m_Movement->Freeze(false);
	}
}

void PeterPepperComponent::DetermineDirection(std::shared_ptr<dae::GameObject> obj)
{
	auto currstate = m_Owner->GetComponent<MovementComponent>()->GetCurrentState();
	glm::vec2 dir{};
	switch (currstate)
	{
	case  MovementComponent::MovementState::GoingDown:
		dir = { 0,1 };
		break;
	case  MovementComponent::MovementState::GoingUp:
		dir = { 0,0 };
		break;
	case  MovementComponent::MovementState::GoingLeft:
		dir = { -1,.5 };
		break;
	case  MovementComponent::MovementState::GoingRight:
		dir = { 1,.5 };
		break;
	default:
		dir = { 0,1 };
		break;
	}

	glm::vec3 pos{ };
	auto originRect = m_Owner->GetComponent<RigidBody>()->GetColRect();
	pos.x = originRect.x + dir.x * originRect.z;
	pos.y = originRect.y + originRect.w * dir.y * 2.f;
	pos.z = 0;

	obj->SetWorldPosition(pos);
}

void PeterPepperComponent::HandleStateUpdate()
{
	if (!m_Movement) m_Movement = m_Owner->GetComponent<MovementComponent>();
	if (!m_Movement) return;
	if (!m_CanHandleStates)return;
	auto newState = m_Movement->GetCurrentState();
	//if (m_CurrentState == newState) return;

	auto sprite = m_Owner->GetComponent<ImageComponent>();
	if (!sprite) return;

	if (m_CurrentState == MovementComponent::MovementState::GoingRight) sprite->FlipTexture(SDL_FLIP_NONE);

	// pp is attacking

	//switch texture settings for each state

	switch (newState)
	{
	case MovementComponent::MovementState::GoingDown:
		if (!m_CanAttack)
		{
			sprite->SetStartFrame(9);
			sprite->SetEndFrame(9);
			m_CanHandleStates = false;
			break;
		}
		sprite->SetStartFrame(0);
		sprite->SetEndFrame(2);
		break;
	case MovementComponent::MovementState::GoingUp:
		if (!m_CanAttack)
		{
			sprite->SetStartFrame(11);
			sprite->SetEndFrame(11);
			m_CanHandleStates = false;
			break;
		}
		sprite->SetStartFrame(6);
		sprite->SetEndFrame(8);
		break;
	case MovementComponent::MovementState::GoingLeft:
		if (!m_CanAttack)
		{
			sprite->SetStartFrame(10);
			sprite->SetEndFrame(10);
			m_CanHandleStates = false;
			break;
		}
		sprite->SetStartFrame(3);
		sprite->SetEndFrame(5);
		break;
	case MovementComponent::MovementState::GoingRight:
		sprite->FlipTexture(SDL_FLIP_HORIZONTAL);
		if (!m_CanAttack)
		{
			sprite->SetStartFrame(10);
			sprite->SetEndFrame(10);
			m_CanHandleStates = false;
			break;
		}
		sprite->SetStartFrame(3);
		sprite->SetEndFrame(5);
		break;
	case MovementComponent::MovementState::Idle:
		if (!m_CanAttack)
		{
			sprite->SetStartFrame(9);
			sprite->SetEndFrame(9);
			m_CanHandleStates = false;
			break;
		}
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

	for (auto element : rb->GetOverlappersWithTag("Enemy"))
	{
		if (!element->GetComponent<EnemyComponent>()->IsStunned())
		{
			Die();
			return;
		}
	}
}