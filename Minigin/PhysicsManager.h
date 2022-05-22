#pragma once
#include "Singleton.h"
#include <map>
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

	int AddRigidBody(glm::vec4 posSize);
	bool CanMove(int id, glm::vec2 move);
	void SetSize(int id, glm::vec2 size);
	glm::vec4 GetCollisionBoundaries(int id)const;
	std::vector<std::string > IsOverlapping(int id);
	void AddOverlappingTags(int id, std::vector<std::string> tags);
	void SetTag(int id, std::string tag);
	void SetCollision(int, CollisionType);
	void ResetPos(int, glm::vec2);

private:
	struct Body
	{
		glm::vec4 rect;
		CollisionType col = CollisionType::COLLIDER;
		CollisionType ColType = CollisionType::COLLIDER;
		std::string Tag = "Default";
		std::vector<std::string> OverlappingTags{};
	};

	bool AreOverlapping(glm::vec4 first, glm::vec4 second);

	std::map<int, Body> m_RigidBodies{};
	int m_IdNr{ 0 };
};
