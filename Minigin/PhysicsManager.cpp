#include "MiniginPCH.h"
#include "PhysicsManager.h"

int PhysicsManager::AddRigidBody(dae::GameObject* gameObj, glm::vec4 posSize)
{
	++m_IdNr;

	posSize.x -= posSize.z / 2.f;
	posSize.y -= posSize.w;

	Body b;
	b.rect = posSize;
	b.ColType = CollisionType::COLLIDER;
	b.owner = gameObj;
	m_RigidBodies.insert(std::pair<int, Body>(m_IdNr, b));

	return m_IdNr;
}

void PhysicsManager::ClearRigidBodys()
{
	m_RigidBodies.erase(m_RigidBodies.begin(), m_RigidBodies.end());
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

PhysicsManager::CollisionType PhysicsManager::GetCollision(int m_Id) const
{
	return m_RigidBodies.at(m_Id).ColType;
}

void PhysicsManager::ResetPos(int id, glm::vec2 pos)
{
	auto& curr = m_RigidBodies.at(id);
	pos.x -= curr.rect.z / 2.f;
	pos.y -= curr.rect.w;

	curr.rect.x = pos.x;
	curr.rect.y = pos.y;
}

std::vector<std::string> PhysicsManager::GetOverlappingTags(int id)
{
	std::vector<std::string> temp;
	for (auto element : m_RigidBodies)
	{
		if (element.second.owner->IsActive())
			if (element.first != id)
				if (std::find(m_RigidBodies.at(id).OverlappingTags.begin(), m_RigidBodies.at(id).OverlappingTags.end(), element.second.Tag) != m_RigidBodies.at(id).OverlappingTags.end())
					if (AreOverlapping(element.second.rect, m_RigidBodies.at(id).rect))
						temp.push_back(element.second.Tag);
	}
	return temp;
}

std::vector<dae::GameObject*> PhysicsManager::GetOverlappers(int id)
{
	std::vector<dae::GameObject*> result;
	for (auto element : m_RigidBodies)
	{
		if (element.second.owner->IsActive())
			if (element.first != id)
				if (std::find(m_RigidBodies.at(id).OverlappingTags.begin(), m_RigidBodies.at(id).OverlappingTags.end(), element.second.Tag) != m_RigidBodies.at(id).OverlappingTags.end())
					if (AreOverlapping(element.second.rect, m_RigidBodies.at(id).rect))
						result.push_back(element.second.owner);
	}
	return result;
}

std::vector<dae::GameObject*> PhysicsManager::GetOverlappersWithTag(int id, const std::string& tag)
{
	std::vector<dae::GameObject*> result;
	for (auto element : m_RigidBodies)
	{
		if (element.second.owner->IsActive())
			if (element.first != id)
				if (std::find(m_RigidBodies.at(id).OverlappingTags.begin(), m_RigidBodies.at(id).OverlappingTags.end(), element.second.Tag) != m_RigidBodies.at(id).OverlappingTags.end())
					if (AreOverlapping(element.second.rect, m_RigidBodies.at(id).rect))
						if (element.second.Tag == tag)
							result.push_back(element.second.owner);
	}
	return result;
}

void PhysicsManager::AddOverlappingTags(int id, std::vector<std::string> tags)
{
	for (auto element : tags)
		m_RigidBodies.at(id).OverlappingTags.push_back(element);
}

void PhysicsManager::RemoveOverlappingTag(int id, std::string tag)
{
	auto& tags = m_RigidBodies[id].OverlappingTags;
	tags.erase(std::remove(tags.begin(), tags.end(), tag), tags.end());
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
		return false;
	}

	if (l1.x >= r2.x || l2.x >= r1.x)
		return false;

	if (r1.y >= l2.y || r2.y >= l1.y)
		return false;
	return true;
}

std::vector <dae::GameObject*> PhysicsManager::GetObjectsWithTag(std::string tag)
{
	std::vector <dae::GameObject*> result;
	for (auto element : m_RigidBodies)
	{
		if (element.second.Tag == tag)
			result.emplace_back(element.second.owner);
	}
	return result;
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
std::vector<glm::vec4> PhysicsManager::GetColsWithTag(std::string tag)
{
	std::vector<glm::vec4>result;
	for (auto rig : m_RigidBodies)
		if (rig.second.Tag == tag)result.push_back(rig.second.rect);

	return result;
}