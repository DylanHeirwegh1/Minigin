#pragma once
#include "Singleton.h"
#include <map>

#include "GameObject.h"
#include "glm/glm.hpp"

class PhysicsManager : public dae::Singleton<PhysicsManager>
{
public:
	enum class CollisionType
	{
		NONE,
		TRIGGER,
		COLLIDER
	};

	int AddRigidBody(dae::GameObject* gameObj, glm::vec4 posSize);

	bool CanMove(int id, glm::vec2 move);

	void SetSize(int id, glm::vec2 size);
	void AddOverlappingTags(int id, std::vector<std::string> tags);
	void RemoveOverlappingTag(int id, std::string tag);
	void SetTag(int id, std::string tag);
	void SetCollision(int, CollisionType);
	void ResetPos(int, glm::vec2);
	bool AreOverlapping(glm::vec4 first, glm::vec4 second);
	glm::vec4 GetCollisionBoundaries(int id)const;
	std::vector<glm::vec4> GetColsWithTag(std::string tag);

	std::vector<std::string > GetOverlappingTags(int id);
	std::vector<dae::GameObject* > GetOverlappers(int id);

	std::vector<dae::GameObject* > GetOverlappersWithTag(int id, const std::string& tag);
	CollisionType GetCollision(int m_Id)const;

private:

	struct Body
	{
		glm::vec4 rect;
		CollisionType col = CollisionType::COLLIDER;
		CollisionType ColType = CollisionType::COLLIDER;
		std::string Tag = "Default";
		std::vector<std::string> OverlappingTags{};
		dae::GameObject* owner;
	};

	std::map<int, Body> m_RigidBodies{};
	int m_IdNr{ 0 };
};
