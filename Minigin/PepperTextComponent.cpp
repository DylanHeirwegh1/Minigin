#include "MiniginPCH.h"
#include "PepperTextComponent.h"

#include "PeterPepperComponent.h"
#include "TextComponent.h"

void PepperTextComponent::Update()
{
}

void PepperTextComponent::Render()
{
}

void PepperTextComponent::Notify(const dae::GameObject& actor, Event event)
{
	switch (event)
	{
	case Event::PepperThrown:
		ChangeText(actor);
		break;
	}
}

void PepperTextComponent::Refresh(const dae::GameObject& actor)
{
	ChangeText(actor);
}

void PepperTextComponent::ChangeText(const dae::GameObject& actor)
{
	auto text = m_Owner->GetComponent<TextComponent>();
	auto pp = actor.GetComponent<PeterPepperComponent>();

	text->SetText("Peppers: " + std::to_string(pp->GetPepper()));
}