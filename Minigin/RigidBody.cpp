#include "MiniginPCH.h"
#include "RigidBody.h"

#include "Renderer.h"
#include "Timer.h"

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

void RigidBody::Update()
{
	CalcVelocity();
	if (!m_ColTurnoff) return;
	m_AccuTime += Timer::GetInstance().GetElapsedSeconds();
	if (m_AccuTime > m_MaxTime)
	{
		m_AccuTime = 0.f;
		m_MaxTime = 0.f;
		m_ColTurnoff = false;
		PhysicsManager::GetInstance().SetCollision(m_Id, PhysicsManager::CollisionType::COLLIDER);
	}
}

void RigidBody::Initialize(dae::GameObject* owner)
{
	m_Owner = owner;
	auto p = m_Owner->GetWorldPosition();
	m_Id = PhysicsManager::GetInstance().AddRigidBody(m_Owner, glm::vec4(p.x, p.y, m_Size.x, m_Size.y));
}

void RigidBody::SetSize(glm::vec2 size)
{
	m_Size = size;
	PhysicsManager::GetInstance().SetSize(m_Id, size);
}

void RigidBody::Move(float x, float y)
{
	if (m_Freeze)return;
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

void RigidBody::TurnOffCollisionForSeconds(float sec)
{
	m_ColTurnoff = true;
	m_MaxTime = sec;
	PhysicsManager::GetInstance().SetCollision(m_Id, PhysicsManager::CollisionType::NONE);
}

void RigidBody::EnableCollision(bool val)
{
	if (val)PhysicsManager::GetInstance().SetCollision(m_Id, PhysicsManager::CollisionType::COLLIDER);
	else PhysicsManager::GetInstance().SetCollision(m_Id, PhysicsManager::CollisionType::NONE);
}

bool RigidBody::GetCollision() const
{
	if (PhysicsManager::GetInstance().GetCollision(m_Id) == PhysicsManager::CollisionType::NONE)
	{
		return false;
	}
	return true;
}

void RigidBody::RemoveTag(std::string tag)
{
	PhysicsManager::GetInstance().RemoveOverlappingTag(m_Id, tag);
}

std::vector<dae::GameObject*> RigidBody::GetOverlappers()
{
	return PhysicsManager::GetInstance().GetOverlappers(m_Id);
}

std::vector<dae::GameObject*> RigidBody::GetOverlappersWithTag(const std::string& tag)
{
	return PhysicsManager::GetInstance().GetOverlappersWithTag(m_Id, tag);
}

std::vector<std::string> RigidBody::GetOverlapperTags()
{
	return PhysicsManager::GetInstance().GetOverlappingTags(m_Id);
}

void RigidBody::CalcVelocity()
{
	auto currP = m_Owner->GetWorldPosition();
	m_Velocity = { currP.x - m_PrevPos.x, currP.y - m_PrevPos.y };
	m_PrevPos = currP;
}