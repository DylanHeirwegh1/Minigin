#include "MiniginPCH.h"
#include "FPSComponent.h"
#include <SDL_ttf.h>
#include "Renderer.h"
#include "TextComponent.h"


void FPSComponent::Render()
{
}

void FPSComponent::Update()
{
	auto textComponent = m_Owner->GetComponent<TextComponent>();
	if (!textComponent) return;


	m_ElapsedTime += Timer::GetInstance().GetElapsedSeconds();
	int fps = static_cast<int>(1.f / Timer::GetInstance().GetElapsedSeconds());

	if (m_ElapsedTime > m_SecondsPerUpdate)
	{
		m_ElapsedTime -= m_SecondsPerUpdate;
		textComponent->SetText(std::to_string(fps));
	}
}

void FPSComponent::SetSecondsPerUpdate(float SecondsPerUpdate)
{
	m_SecondsPerUpdate = SecondsPerUpdate;
}


