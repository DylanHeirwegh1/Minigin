#pragma once
#include "Observer.h"
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update(float deltaTime);
		void FixedUpdate();
		void Render();
		dae::Scene& GetActiveScene();
		void RemoveScene() { m_Scenes.pop_back(); std::cout << "\nNrOfScenes:" << m_Scenes.size() << std::endl; }

	private:

		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		Scene* m_ActiveScene{};
	};
}
