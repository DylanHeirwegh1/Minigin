#include "MiniginPCH.h"
#include "IngredientComponent.h"

#include "PeterPepperComponent.h"

//when a player overlaps, look at the position of the players, compare them to the array positions
//drop an ingredient when it gets walked over completely
void IngredientComponent::Initialize(dae::GameObject* owner)
{
	m_Owner = owner;
}

void IngredientComponent::HandlePlayerInteraction()
{
	const float offset = 2.f;
	auto pos = m_Owner->GetWorldPosition().x;

	auto rbWidth = m_Rb->GetDimensions().x;
	auto segmentWidth = rbWidth / 5.f;

	m_MiddlePoints[0].first = pos - rbWidth / 2.f;
	for (size_t i = 1; i < 4; i++)
	{
		m_MiddlePoints[i].first = pos - rbWidth / 2.f + segmentWidth + i * segmentWidth;
	}
	m_MiddlePoints[4].first = pos + rbWidth / 2.f;

	auto overlappers = m_Rb->GetOverlappersWithTag("Player");
	if (overlappers.size() != 0)
	{
		for (const auto& overlapper : overlappers)
		{
			float currPosX = overlapper->GetWorldPosition().x;
			for (size_t i = 0; i < 5; i++)
			{
				if ((currPosX < m_MiddlePoints[i].first + offset) && (currPosX > m_MiddlePoints[i].first - offset) && !m_MiddlePoints[i].second)
				{
					m_MiddlePoints[i].second = true;
					m_Subject->Notify(*m_Owner, Event::SegmentWalked);
					if (AreAllSegmentsWalked())
					{
						Drop();
						Reset();
					}
				}
			}
		}
	}
}

void IngredientComponent::Drop()
{
	m_Subject->Notify(*m_Owner, Event::BurgerDropped);
	m_Rb->TurnOffCollisionForSeconds(.5f);
}

bool IngredientComponent::AreAllSegmentsWalked()
{
	for (size_t i = 0; i < 5; i++)
	{
		if (!m_MiddlePoints[i].second) return false;
	}
	return true;
}

void IngredientComponent::Reset()
{
	for (int i = 0; i < 5; ++i)
		m_MiddlePoints[i].second = false;
}

void IngredientComponent::HandlePlate()
{
	m_Rb->EnableCollision(true);
	m_Rb->RemoveTag("Ingredient");
	m_Rb->Freeze();
}

void IngredientComponent::AddObservers()
{
	auto players = PhysicsManager::GetInstance().GetObjectsWithTag("Player");
	if (players.size() == 0)return;

	m_Subject->AddObserver(players[0]->GetComponent<PeterPepperComponent>());

	m_ObserversAdded = true;
}

bool IngredientComponent::LevelComplete()
{
	auto ingrCol = PhysicsManager::GetInstance().GetColsWithTag("Ingredient");
	for (size_t i = 0; i < ingrCol.size(); i++)
	{
		if (ingrCol[i].y < m_MinYLevel)
		{
			std::cout << ingrCol[i].y << std::endl;
			return false;
		}
	}
	return true;
}

void IngredientComponent::Render()
{
}

void IngredientComponent::Update()
{
	if (!m_ObserversAdded) AddObservers();

	if (!m_Rb)
	{
		m_Rb = m_Owner->GetComponent<RigidBody>();
		return;
	}
	if (!m_Movement) m_Movement = m_Owner->GetComponent<MovementComponent>();

	m_Movement->Fall();
	HandlePlayerInteraction();
	HandleIngredientInteration();
}

void IngredientComponent::HandleIngredientInteration()
{
	if (m_Movement->GetCurrentState() == MovementComponent::MovementState::GoingDown)
	{
		auto plates = m_Rb->GetOverlappersWithTag("Plate");

		if (plates.size() != 0)
			HandlePlate();
		auto overlappers = m_Rb->GetOverlappersWithTag("Ingredient");

		if (overlappers.size() == 0)
			return;

		if (overlappers[0]->GetComponent<RigidBody>()->IsFrozen())
		{
			HandlePlate();
			if (LevelComplete())
				m_Subject->Notify(*m_Owner, Event::LevelComplete);
			return;
		}

		auto otherMov = overlappers[0]->GetComponent<MovementComponent>();
		if (m_Movement->GetCurrentState() == MovementComponent::MovementState::Idle && otherMov->GetCurrentState() == MovementComponent::MovementState::GoingDown)
			Drop();
		else if (m_Movement->GetCurrentState() == MovementComponent::MovementState::GoingDown && otherMov->GetCurrentState() == MovementComponent::MovementState::Idle)
		{
			overlappers[0]->GetComponent<IngredientComponent>()->Drop();
			m_Rb->EnableCollision(true);
		}
	}
}