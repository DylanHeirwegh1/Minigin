#pragma once
#include "BaseComponent.h"
#include "PhysicsManager.h"
class RigidBody : public BaseComponent
{
public:
	~RigidBody();
	void Render() override;
	void Update() override;
	void Initialize(dae::GameObject* owner) override;

	void RemakeCol();

	void SetSize(glm::vec2 size);
	void Move(float x, float y);
	void SetVisible(bool visible) { m_Visible = visible; }
	void SetCollision(PhysicsManager::CollisionType col);
	void ResetPos();
	void OverlapWithTag(std::vector<std::string> tags);
	void SetTag(std::string tag);
	void TurnOffCollisionForSeconds(float sec);
	void EnableCollision(bool val);
	bool GetCollision()const;
	void RemoveTag(std::string tag);

	void Freeze(bool val = true) { m_Freeze = val; }
	bool IsFrozen() { return m_Freeze; }
	glm::vec2 GetVelocity() { return m_Velocity; }
	glm::vec2 GetDimensions() { return m_Size; }
	std::vector<dae::GameObject*> GetOverlappers();
	std::vector<dae::GameObject*> GetOverlappersWithTag(const std::string& tag);
	std::vector<std::string> GetOverlapperTags();
	glm::vec4 GetColRect();

private:

	glm::vec2 m_Size;
	int m_Id{ 0 };
	bool m_Visible = false;
	float m_AccuTime = 0.f;
	bool m_ColTurnoff = false;
	bool m_Freeze = false;
	float m_MaxTime = 0.f;
	void CalcVelocity();
	glm::vec2 m_Velocity{ 0.f,0.f };
	glm::vec2 m_PrevPos{ 0.f,0.f };
};
