#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include <iostream>
#include <vector>

class BaseComponent;

namespace dae
{
	class Texture2D;
	class GameObject final : public SceneObject
	{
	public:
		GameObject(float posX, float posY);
		GameObject();
		~GameObject();

		void Update() override;
		void Render() const override;

		template<typename T> T* AddComponent();
		template<typename T> T* GetComponent()const;
		template<typename T> void RemoveComponent();
		void SetParent(GameObject* parent, bool keepWorldPos);
		GameObject* GetParent() const;
		size_t GetChildCount() const;
		GameObject* GetChildAt(int index) const;

		glm::vec3 GetWorldPosition();
		void SetWorldPosition(glm::vec3 v);
		void SetActive(bool active);
		bool IsActive() { return m_Active; }
		void SetId(unsigned int id) { m_Id = id; }
		unsigned int getId() { return m_Id; }

	private:
		void RemoveChild(GameObject* childToReturn);
		void AddChild(GameObject* child);
		void RemoveChild(int index);
		void SetLocalPosition(glm::vec3 transform);
		void SetPositionDirty();
		void UpdateWorldPosition();

		glm::vec3 GetLocalPosition();

		glm::vec3 m_WorldPosition{};
		GameObject* m_Parent = nullptr;
		std::vector<BaseComponent*> m_Components;
		std::vector<GameObject*> m_Children;

		glm::vec3 m_LocalPosition{};
		bool m_PositionDirty{ true };
		bool m_Active{ true };
		unsigned int m_Id{ 0 };
	};

	//Component handling
	template<typename T>
	inline T* GameObject::AddComponent()
	{
		T* Component = new T();
		static_cast<BaseComponent*>(Component)->Initialize(this);
		m_Components.push_back(Component);
		return Component;
	}
	template<typename T>
	inline T* GameObject::GetComponent()const
	{

		for (size_t i = 0; i < m_Components.size(); i++)
		{
			if (typeid(*m_Components[i]) == typeid(T))
			{
				return static_cast<T*>(m_Components[i]);
			}
		}
		
		return nullptr;
	}
	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		int index{ 0 };


		for (auto comp : m_Components)
		{
			if (typeid(*comp) == typeid(T))
			{
				delete comp;
				comp = nullptr;
				break;
			}
			++index;
		}
		m_Components.erase(m_Components.begin() + index);
	}
}
