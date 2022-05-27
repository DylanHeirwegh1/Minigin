#include "MiniginPCH.h"
#include "LivesComponent.h"

#include "PeterPepperComponent.h"
#include "TextComponent.h"

void LivesComponent::Notify(const dae::GameObject& actor, Event event)
{
	switch (event)
	{
	case Event::ActorDied:
		ChangeText(actor);
		break;
	}
}

void LivesComponent::Update()
{
}

void LivesComponent::Render()
{
}

void LivesComponent::ChangeText(const dae::GameObject& actor)
{
	auto text = m_Owner->GetComponent<TextComponent>();
	auto pp = actor.GetComponent<PeterPepperComponent>();

	text->SetText("Lives: " + std::to_string(pp->GetLives()));
}