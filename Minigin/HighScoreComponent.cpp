#include "MiniginPCH.h"
#include "HighScoreComponent.h"
#include <iostream>
#include <fstream>

#include "PeterPepperComponent.h"
#include "TextComponent.h"

void HighScoreComponent::Update()
{
}

void HighScoreComponent::Initialize(dae::GameObject* owner)
{
	m_Owner = owner;
	ReadHighScore();
	RefreshText(m_HighScore);
}

void HighScoreComponent::Render()
{
}

void HighScoreComponent::ReadHighScore()
{
	std::ifstream is("../Data/TextFiles/Highscore.txt");
	is >> m_HighScore;
	is.close();
}

void HighScoreComponent::RefreshText(int score)
{
	if (score < m_HighScore)return;
	m_Owner->GetComponent<TextComponent>()->SetText("Highscore: " + std::to_string(score));

	UpdateHighScore(score);
}

void HighScoreComponent::UpdateHighScore(int highscore)
{
	if (highscore < m_HighScore)return;

	std::ofstream os("../Data/TextFiles/Highscore.txt");
	os << highscore;
	os.close();
}

void HighScoreComponent::Notify(const dae::GameObject& actor, Event event)
{
	switch (event)
	{
	case Event::ScoreChanged:
		RefreshText(actor.GetComponent<PeterPepperComponent>()->GetScore());
		break;
	}
}