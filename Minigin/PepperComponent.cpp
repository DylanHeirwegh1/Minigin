#include "MiniginPCH.h"
#include "PepperComponent.h"

#include "EnemyComponent.h"

void PepperComponent::Update()
{
	m_AccuTime += Timer::GetInstance().GetElapsedSeconds();
	if (m_AccuTime > m_MaxTime)
	{
		dae::SceneManager::GetInstance().GetActiveScene().Remove(m_Id);
		return;
	}
	HandleEnemies();
}

void PepperComponent::HandleEnemies()
{
	if (!m_Rb)
	{
		m_Rb = m_Owner->GetComponent<RigidBody>();
	}
	auto overlappers = m_Rb->GetOverlappersWithTag("Enemy");
	for (auto element : overlappers)
	{
		element->GetComponent<EnemyComponent>()->Stun();
	}
}