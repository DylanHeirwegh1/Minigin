#include "MiniginPCH.h"
#include "PeterPepperComponent.h"

void PeterPepperComponent::Render()
{
}

void PeterPepperComponent::Update()
{
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
