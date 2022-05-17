#include "MiniginPCH.h"
#include "GameObject.h"

#include "BaseComponent.h"

dae::GameObject::GameObject(float posX, float posY)
	: SceneObject()
{
	m_WorldPosition = { posX, posY, 0.f };
}

dae::GameObject::GameObject() : SceneObject()
{
}

dae::GameObject::~GameObject()
{
	for (auto& comp : m_Components)
	{
		delete comp;
	}
}

void dae::GameObject::Update() {
	for (auto component : m_Components)
	{
		component->Update();
	}
	for (auto child : m_Children)
	{
		child->Update();
	}
}

void dae::GameObject::Render() const
{
	for (auto component : m_Components)
	{
		component->Render();
	}
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPos)
{
	//remove itself as child from previous parent
	if (m_Parent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPos)
			SetLocalPosition(GetLocalPosition() - parent->GetWorldPosition());
		SetPositionDirty();
	}
	if (m_Parent)m_Parent->RemoveChild(this);
	m_Parent = parent;
	if (m_Parent) m_Parent->AddChild(this);
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_Parent;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_Children.size();
}

dae::GameObject* dae::GameObject::GetChildAt(int index) const
{
	if (static_cast<unsigned int>(index) > m_Children.size() - static_cast<unsigned int>(1)) return nullptr;
	return m_Children[index];
}

glm::vec3 dae::GameObject::GetWorldPosition()
{
	if (m_PositionDirty)
		UpdateWorldPosition();
	return m_WorldPosition;
}

void dae::GameObject::SetWorldPosition(glm::vec3 v)
{
	SetLocalPosition(v);
}

void dae::GameObject::RemoveChild(int index)
{
	if (static_cast<unsigned int>(index) > m_Children.size() - static_cast<unsigned int>(1)) return;

	//Remove the given child from the children list
	m_Children.erase(m_Children.begin() + index);

	//Remove itself as a parent of the child.
	m_Children.at(index)->SetParent(nullptr, true);

	//Update position, rotationand scale
}

void dae::GameObject::SetLocalPosition(glm::vec3 transform)
{
	m_LocalPosition = transform;
	SetPositionDirty();
}

void dae::GameObject::SetPositionDirty()
{
	m_PositionDirty = true;
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_PositionDirty)
	{
		if (m_Parent == nullptr)
			m_WorldPosition = m_LocalPosition;
		else
			m_WorldPosition = m_Parent->GetWorldPosition() + m_LocalPosition;
	}
	m_PositionDirty = false;
}

glm::vec3 dae::GameObject::GetLocalPosition()
{
	return m_LocalPosition;
}

void dae::GameObject::RemoveChild(GameObject* childToRemove)
{
	for (size_t i = 0; i < m_Children.size(); i++)
	{
		if (m_Children[i] == childToRemove)
		{
			//Remove the given child from the children list
			m_Children.erase(m_Children.begin() + i);
		}
	}
}

void dae::GameObject::AddChild(GameObject* child)
{
	m_Children.push_back(child);
}