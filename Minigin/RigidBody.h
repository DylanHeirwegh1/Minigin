#pragma once
#include "BaseComponent.h"
#include "PhysicsManager.h"
class RigidBody : public BaseComponent
{
public:

	void Render() override;
	void Update() override {};
	void Initialize(dae::GameObject* owner) override;

	void SetSize(glm::vec2 size);
	void Move(float x, float y);
	void SetVisible(bool visible) { m_Visible = visible; }
	void SetCollision(PhysicsManager::CollisionType col);
	void ResetPos();
	void OverlapWithTag(std::vector<std::string> tags);
	void SetTag(std::string tag);
	std::vector<std::string> GetOverlappers();

private:
	glm::vec2 m_Size;
	int m_Id{ 0 };
	bool m_Visible = false;
};
