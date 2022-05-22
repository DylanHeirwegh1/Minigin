#pragma once
#include "Observer.h"
#include "Scene.h"
#include "FPSComponent.h"
#include "ImageComponent.h"
#include "InputManager.h"
#include "MovementComponent.h"
#include "PeterPepperComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "RigidBody.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "EnemyComponent.h"
class BTScene : public Observer
{
public:
	BTScene();
	~BTScene() = default;
	BTScene(const BTScene& other) = delete;
	BTScene(BTScene&& other) noexcept = delete;
	BTScene& operator=(const BTScene& other) = delete;
	BTScene& operator=(BTScene&& other) noexcept = delete;

	void Reset();
	void Notify(const dae::GameObject& actor, Event event) override;

private:
	void AddBlock(dae::Scene& scene, glm::vec2 pos, glm::vec2 size);
	std::shared_ptr<dae::GameObject>m_PeterPepper;
	std::shared_ptr<dae::GameObject>m_Sausage;
};
