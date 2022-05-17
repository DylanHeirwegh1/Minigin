#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "SDL.h"
class ImageComponent : public BaseComponent
{
public:
	void SetTexture(const std::string& filename);
	void Render() override;
	void Update() override;
	void MakeAnimated(int rows, int cols, int totalFrames);
	void SetFramesPerSecond(int fps);
	void SetDimensions(float w, float h);
	void FlipTexture();
	void SetStartFrame(int frame);
	void SetEndFrame(int frame);

private:
	std::shared_ptr <dae::Texture2D> m_Texture{};
	float m_AccuTime{};
	int m_FramesPerSecond{ 21 };
	bool m_IsSprite{ false };
	SDL_RendererFlip m_CurrRFlip{ SDL_FLIP_NONE };

	int m_Rows{ 3 };
	int m_Cols{ 3 };
	int m_CurrentFrame{ 0 };
	int m_StartFrame{ 0 };
	int m_EndFrame{ 0 };
	glm::vec2 m_Scale{ 0.f, 0.f };
};
