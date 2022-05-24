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
	std::pair<float, bool> m_MiddlePoints[5]{};
	RigidBody* m_Rb = nullptr;
	MovementComponent* m_Movement = nullptr;
};
