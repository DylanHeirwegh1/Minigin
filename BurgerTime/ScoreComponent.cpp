#include "pch.h"
#include "ScoreComponent.h"

#include "PeterPepperComponent.h"
#include "TextComponent.h"

void ScoreComponent::Render()
{
}

void ScoreComponent::ChangeText(const dae::GameObject& object)
{
	auto text = m_Owner->GetComponent<TextComponent>();
	auto pp = object.GetComponent<PeterPepperComponent>();

	text->SetText("Score: " + std::to_string(pp->GetScore()));
}

void ScoreComponent::Update()
{
}

void ScoreComponent::Notify(const dae::GameObject& object, Event event)
{
	switch (event)
	{
	case Event::ScoreChanged:
		ChangeText(object);
		break;;
	}
}
void ScoreComponent::Refresh(const dae::GameObject& actor)
{
	ChangeText(actor);
}