#include "MiniginPCH.h"
#include "PhysicsManager.h"

int PhysicsManager::AddRigidBody(glm::vec4 posSize)
{
	++m_IdNr;

	posSize.x -= posSize.z / 2.f;
	posSize.y -= posSize.w;

	Body b;
	b.rect = posSize;
	b.ColType = CollisionType::COLLIDER;

	m_RigidBodies.insert(std::pair<int, Body>(m_IdNr, b));

	return m_IdNr;
}

void PhysicsManager::SetSize(int id, glm::vec2 newsize)
{
	auto& curr = m_RigidBodies.at(id).rect;

	//reset to sdl standard
	curr.x += curr.z / 2.f;
	curr.y += curr.w;

	//give new size and adjust pos to that
	curr.z = newsize.x;
	curr.w = newsize.y;

	//re-adjust pos
	curr.x -= curr.z / 2.f;
	curr.y -= curr.w;
}

glm::vec4 PhysicsManager::GetCollisionBoundaries(int id) const
{
	return m_RigidBodies.at(id).rect;
}

void PhysicsManager::SetCollision(int id, CollisionType col)
{
	m_RigidBodies.at(id).ColType = col;
}

void PhysicsManager::ResetPos(int id, glm::vec2 pos)
{
	auto& curr = m_RigidBodies.at(id);
	pos.x -= curr.rect.z / 2.f;
	pos.y -= curr.rect.w;

	curr.rect.x = pos.x;
	curr.rect.y = pos.y;
}

std::vector<std::string> PhysicsManager::IsOverlapping(int id)
{
	std::vector<std::string> temp;
	for (auto element : m_RigidBodies)
	{
		if (element.first != id)
			if (std::find(m_RigidBodies.at(id).OverlappingTags.begin(), m_RigidBodies.at(id).OverlappingTags.end(), element.second.Tag) != m_RigidBodies.at(id).OverlappingTags.end())
				if (AreOverlapping(element.second.rect, m_RigidBodies.at(id).rect))
					temp.push_back(element.second.Tag);
	}
	return temp;
}

void PhysicsManager::AddOverlappingTags(int id, std::vector<std::string> tags)
{
	for (auto element : tags)
		m_RigidBodies.at(id).OverlappingTags.push_back(element);
}

void PhysicsManager::SetTag(int id, std::string tag)
{
	m_RigidBodies.at(id).Tag = tag;
}

bool PhysicsManager::AreOverlapping(glm::vec4 first, glm::vec4 second)
{
	glm::vec2 l1 = { first.x,first.y + first.w };
	glm::vec2 r1 = { first.x + first.z,first.y };

	glm::vec2 l2 = { second.x,second.y + second.w };
	glm::vec2 r2 = { second.x + second.z,second.y };

	if (l1.x == r1.x || l1.y == r1.y || l2.x == r2.x
		|| l2.y == r2.y) {
		// the line cannot have positive overlap
		return false;
	}

	// If one rectangle is on left side of other
	if (l1.x >= r2.x || l2.x >= r1.x)
		return false;

	// If one rectangle is above other
	if (r1.y >= l2.y || r2.y >= l1.y)
		return false;
	return true;
}

bool PhysicsManager::CanMove(int id, glm::vec2 delta)
{
	auto& curr = m_RigidBodies.at(id);
	auto future = curr.rect;

	future.x += delta.x;
	future.y += delta.y;

	if (m_RigidBodies.at(id).ColType == CollisionType::COLLIDER)
	{
		for (auto& rb : m_RigidBodies)
			if (std::find(m_RigidBodies.at(id).OverlappingTags.begin(), m_RigidBodies.at(id).OverlappingTags.end(), rb.second.Tag) == m_RigidBodies.at(id).OverlappingTags.end()) // if item not in list
				if (rb.first != id && rb.second.ColType == CollisionType::COLLIDER)
					if (AreOverlapping(rb.second.rect, future))
						return false;
	}

	curr.rect = future;
	return true;
}