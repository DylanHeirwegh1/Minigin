#include "MiniginPCH.h"
#include "BaseComponent.h"

#include "GameObject.h"

void BaseComponent::Initialize(dae::GameObject* owner)
{
	m_Owner = owner;
}

