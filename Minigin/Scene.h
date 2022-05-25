#pragma once
#include "SceneManager.h"

namespace dae
{
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		unsigned int Add(const std::shared_ptr<SceneObject>& object);
		void Remove(unsigned int id);
		void Update();
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	protected:
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::pair<unsigned int, std::shared_ptr<SceneObject>>> m_Objects{};

		static unsigned int m_IdCounter;
	};
}
