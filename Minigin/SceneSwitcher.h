#pragma once
#include "BaseComponent.h"
#include "Scene.h"

class SceneSwitcher :
	public BaseComponent, public Observer
{
public:
	enum class GameMode
	{
		SINGLE,
		PVP,
		COOP
	};
	void Initialize(dae::GameObject* owner) override;
	void Update() override {};
	void Render() override {};
	void LoadLevel(int nr);
	void SwitchGameMode(GameMode mode);
	void Notify(const dae::GameObject& actor, Event event) override;
	~SceneSwitcher();
private:
	void LoadLevel1();
	void LoadLevel2();
	void LoadLevel3();
	void Reset();
	void SetInputCommands();
	void AddFpsComponent(dae::Scene& scene, glm::vec3 pos);
	void AddPeterPepper(dae::Scene& scene, glm::vec3 pos);
	void AddMrsSalt(dae::Scene& scene, glm::vec3 pos);
	void AddSausage(dae::Scene& scene, glm::vec3 pos);
	void AddEgg(dae::Scene& scene, glm::vec3 pos);
	void AddPickle(dae::Scene& scene, glm::vec3 pos);
	void AddPlayerSausage(dae::Scene& scene, glm::vec3 pos);
	void AddMenu(dae::Scene& scene);
	void AddText(dae::Scene& scene);

	struct sceneObj
	{
		std::shared_ptr<dae::GameObject> Object;
		glm::vec3 StartPos;
	};

	sceneObj m_PeterPepper;
	sceneObj m_Salt;
	sceneObj m_PlayerSausage;
	std::shared_ptr<dae::GameObject> m_Menu;

	int m_CurrLevel{ 0 };
	bool m_FirstLoad = true;
	GameMode m_CurrGameMode{ GameMode::PVP };
	std::shared_ptr<dae::GameObject> m_PPLivesText;
	std::shared_ptr<dae::GameObject> m_PPScoreText;

	std::shared_ptr<dae::GameObject> m_SaltLivesText;
	std::shared_ptr<dae::GameObject> m_SaltScoreText;
	std::shared_ptr<dae::GameObject> m_HighScoreText;
	std::vector<sceneObj> m_Enemies;
};
