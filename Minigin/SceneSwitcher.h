#pragma once
#include "BaseComponent.h"
#include "Scene.h"

class SceneSwitcher :
	public BaseComponent, public Observer
{
public:
	void Update() override {};
	void Render() override {};
	void LoadLevel1();
	void LoadLevel2();
	void LoadLevel3();
	void Notify(const dae::GameObject& actor, Event event) override;
	~SceneSwitcher();
private:
	void Reset();
	void AddFpsComponent(dae::Scene& scene, glm::vec3 pos);
	void AddPeterPepper(dae::Scene& scene, glm::vec3 pos);
	void AddSausage(dae::Scene& scene, glm::vec3 pos);
	struct sceneObj
	{
		std::shared_ptr<dae::GameObject> Object;
		glm::vec3 StartPos;
	};
	sceneObj m_PeterPepper;
	std::vector<sceneObj> m_Sausages;
	int m_CurrLevel{ 0 };
	bool madePP = false;
};
