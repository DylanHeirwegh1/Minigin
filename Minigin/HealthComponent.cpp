#include "MiniginPCH.h"
#include "HealthComponent.h"

#include "PeterPepperComponent.h"
#include "TextComponent.h"
#include "SDL_mixer.h"

HealthComponent::HealthComponent()
{
	SDL_GetAudioDriver(0);
}

void HealthComponent::Render()
{
}

void HealthComponent::Update()
{
}

void HealthComponent::Notify(const dae::GameObject& actor, Event event)
{
	switch (event)
	{
	case Event::ActorDied:
		GetOwner()->GetComponent < TextComponent >()->SetText("Remaining Lives: " + std::to_string(actor.GetComponent<PeterPepperComponent>()->GetLives()));
		break;
	}
}