#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	deltaTime;
	/*for (auto& scene : m_Scenes)
	{
		scene->Update();
	}*/
	if (m_ActiveScene)
		m_ActiveScene->Update();
}

void dae::SceneManager::FixedUpdate()
{
}

void dae::SceneManager::Render()
{
	/*for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}*/

	if (m_ActiveScene)
		m_ActiveScene->Render();
}

dae::Scene& dae::SceneManager::GetActiveScene()
{
	return *m_ActiveScene;
}

void dae::SceneManager::RemoveScene()
{
	if (m_Scenes.size() > 0)
		m_Scenes.pop_back();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	m_ActiveScene = scene.get();
	return *scene;
}