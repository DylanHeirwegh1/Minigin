#include "MiniginPCH.h"
#include "ScoreComponent.h"

#include "PeterPepperComponent.h"
#include "TextComponent.h"


ScoreComponent::ScoreComponent()
{
}

void ScoreComponent::Render()
{
}

void ScoreComponent::Update()
{
}

void ScoreComponent::Notify(const dae::GameObject& actor, Event event)
{
	switch (event)
	{
	case(Event::EnemyCrushed):

		m_Owner->GetComponent<TextComponent>()->SetText("Score: " + std::to_string(actor.GetComponent<PeterPepperComponent>()->GetScore()));
		break;
	}

}
