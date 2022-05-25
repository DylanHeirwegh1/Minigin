#pragma once
#include "BaseComponent.h"
#include "RigidBody.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Timer.h"
class PepperComponent :
	public BaseComponent
{
public:
	void Update() override;
	void Render() override {};
	void SetId(unsigned int id) { m_Id = id; }
private:
	void HandleEnemies();
	float m_MaxTime = 1.f;
	float m_AccuTime = 0.f;
	unsigned int  m_Id{};
	RigidBody* m_Rb{ nullptr };
};
