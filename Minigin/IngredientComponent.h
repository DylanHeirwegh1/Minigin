#pragma once

#include "BaseComponent.h"
#include "RigidBody.h"
#include "MovementComponent.h"

class IngredientComponent :
	public BaseComponent
{
public:
	void Render() override;
	void Update() override;
	void Initialize(dae::GameObject* owner) override;
	void Drop();
private:
	void HandleIngredientInteration();
	void HandlePlayerInteraction();
	bool AreAllSegmentsWalked();
	void Reset();
	void HandlePlate();
	void AddObservers();
	bool LevelComplete();
	bool m_ObserversAdded = false;
	std::pair<float, bool> m_MiddlePoints[5]{};
	RigidBody* m_Rb = nullptr;
	MovementComponent* m_Movement = nullptr;
	std::unique_ptr<Subject> m_Subject{ std::make_unique<Subject>() };
	int m_MinYLevel = 530;
};
