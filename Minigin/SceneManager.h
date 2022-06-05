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
		void RemoveOld();

	private:

		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::shared_ptr<Scene> m_ActiveScene{};
		std::shared_ptr<Scene> m_Old{};
	};
}
