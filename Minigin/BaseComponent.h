#pragma once

#include "Subject.h"
#include "Transform.h"

namespace  dae
{
	class GameObject;
}

class BaseComponent
{
public:
	explicit BaseComponent() = default;
	virtual ~BaseComponent() = default;
	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Initialize(dae::GameObject* owner);

protected:
	dae::GameObject* m_Owner;
	dae::GameObject* GetOwner() const { return m_Owner; }
};