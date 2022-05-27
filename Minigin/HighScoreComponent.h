#pragma once
#include "BaseComponent.h"

class HighScoreComponent :
	public BaseComponent, public Observer
{
public:
	void Update() override;
	void Initialize(dae::GameObject* owner) override;
	void Render() override;
	void UpdateHighScore(int highscore);
	void Notify(const dae::GameObject& actor, Event event) override;

private:
	int m_HighScore{ 0 };
	void ReadHighScore();
	void RefreshText(int score);
};
