#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	std::cout << "DESTRUCTOR SCENE\n";
};

unsigned int Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	++m_IdCounter;
	m_Objects.push_back({ m_IdCounter,object });
	return m_IdCounter;
}

void dae::Scene::Remove(unsigned int id)
{
	auto it = std::ranges::find(m_Objects, id,
		&std::pair<unsigned int, std::shared_ptr<SceneObject>>::first);

	m_Objects.erase(it);

	//pVector.erase(std::remove(pVector.begin(), pVector.end(), obj), pVector.end());
}

void Scene::Update()
{
	for (auto& object : m_Objects)
		object.second->Update();
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		if (m_Objects.size() != 0)
			object.second->Render();
	}
}