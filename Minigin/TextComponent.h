#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>
#include "Font.h"
#include "Texture2D.h"

class TextComponent : public BaseComponent
{
public:

	void Update() override;
	void Render() override;

	void SetText(const std::string& text);
	void SetFont(std::shared_ptr<dae::Font> font);
	void SetColor(SDL_Color color);

private:
	bool m_NeedsUpdate{ true };
	std::string m_Text{};

	std::shared_ptr<dae::Font> m_Font{};
	std::shared_ptr<dae::Texture2D> m_TextTexture{};
	SDL_Color m_Color{ 255,255,255 };
};

