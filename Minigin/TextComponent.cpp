#include "MiniginPCH.h"
#include "TextComponent.h"
#include <SDL_ttf.h>

#include "GameObject.h"
#include "Renderer.h"



void TextComponent::Update()
{

	if (!m_NeedsUpdate) return;
	const auto surface = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
	if (surface == nullptr) return;

	auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surface);
	if (texture == nullptr) return;

	SDL_FreeSurface(surface);
	m_TextTexture = std::make_shared<dae::Texture2D>(texture);
	m_NeedsUpdate = false;

}

void TextComponent::Render()
{

	if (m_TextTexture != nullptr)
	{

		const auto& position = m_Owner->GetWorldPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_TextTexture, position.x, position.y);
	}
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextComponent::SetFont(std::shared_ptr<dae::Font> font)
{
	m_Font = font;
}



void TextComponent::SetColor(SDL_Color color)
{
	m_Color = color;
}


