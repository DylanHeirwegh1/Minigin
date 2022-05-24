#include "MiniginPCH.h"
#include "IngredientComponent.h"

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
		for (auto overlapper : overlappers)
		{
			float currPosX = overlapper->GetWorldPosition().x;
			for (size_t i = 0; i < 5; i++)
			{
				if ((currPosX < m_MiddlePoints[i].first + offset) && (currPosX > m_MiddlePoints[i].first - offset) && !m_MiddlePoints[i].second)
				{
					m_MiddlePoints[i].second = true;
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
	std::cout << "drop";
	//m_Rb->EnableCollision(false);
	m_Rb->TurnOffCollisionForSeconds(.5f);
	//get overlappers and turn on collision when overlapping ingredient
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

void IngredientComponent::Render()
{
}

void IngredientComponent::Update()
{
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