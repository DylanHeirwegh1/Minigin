#include "MiniginPCH.h"
#include "RigidBody.h"

#include "Renderer.h"

void RigidBody::Render()
{
	if (!m_Visible)return;

	auto renderer = dae::Renderer::GetInstance().GetSDLRenderer();

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	auto pos = PhysicsManager::GetInstance().GetCollisionBoundaries(m_Id);

	auto r = SDL_Rect(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(pos.z), static_cast<int>(pos.w));

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 1);
	SDL_RenderDrawRect(renderer, &r);
}

void RigidBody::Initialize(dae::GameObject* owner)
{
	m_Owner = owner;
	auto p = m_Owner->GetWorldPosition();
	m_Id = PhysicsManager::GetInstance().AddRigidBody(glm::vec4(p.x, p.y, m_Size.x, m_Size.y));
}

void RigidBody::SetSize(glm::vec2 size)
{
	PhysicsManager::GetInstance().SetSize(m_Id, size);
}

void RigidBody::Move(float x, float y)
{
	if (PhysicsManager::GetInstance().CanMove(m_Id, { x,y }))
	{
		auto pos = m_Owner->GetWorldPosition();
		pos.y += y;
		pos.x += x;
		m_Owner->SetWorldPosition(pos);
	}

	//call the physics manager for permission for the move;
}

void RigidBody::SetCollision(PhysicsManager::CollisionType col)
{
	PhysicsManager::GetInstance().SetCollision(m_Id, col);
}

void RigidBody::ResetPos()
{
	//TODO observer idea
	auto p = m_Owner->GetWorldPosition();
	PhysicsManager::GetInstance().ResetPos(m_Id, { p.x,p.y });
}

void RigidBody::OverlapWithTag(std::vector<std::string> tags)
{
	PhysicsManager::GetInstance().AddOverlappingTags(m_Id, tags);
}

void RigidBody::SetTag(std::string tag)
{
	PhysicsManager::GetInstance().SetTag(m_Id, tag);
}

std::vector<std::string> RigidBody::GetOverlappers()
{
	return PhysicsManager::GetInstance().IsOverlapping(m_Id);
}