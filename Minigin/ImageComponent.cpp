#include "MiniginPCH.h"
#include "ImageComponent.h"

#include "GameObject.h"

#include "ResourceManager.h"
#include "Renderer.h"
#include "Timer.h"

void ImageComponent::SetTexture(const std::string& filename)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void ImageComponent::Render()
{
	if (!m_Texture) return;
	const auto& pos = m_Owner->GetWorldPosition();
	if (m_IsSprite)
	{
		int w, h;
		SDL_QueryTexture(m_Texture->GetSDLTexture(), NULL, NULL, &w, &h);

		SDL_Rect dst, src;

		src.w = w / m_Cols;
		src.h = h / m_Rows;
		src.x = m_CurrentFrame % m_Cols * src.w;
		src.y = m_CurrentFrame / m_Cols * src.h;

		int destw, desth;
		if (m_Scale.x == 0 && m_Scale.y == 0)
		{
			destw = src.w;
			desth = src.h;
		}
		else
		{
			destw = static_cast<int>(m_Scale.x);
			desth = static_cast<int>(m_Scale.y);
		}

		dst.x = static_cast<int>(pos.x - (destw / 2));
		dst.y = static_cast<int>(pos.y - (desth));
		dst.w = static_cast<int>(destw);
		dst.h = static_cast<int>(desth);

		SDL_RenderCopyEx(dae::Renderer::GetInstance().GetSDLRenderer(), m_Texture->GetSDLTexture(), &src, &dst, 0, {}, m_CurrRFlip);
	}
	else
	{
		if (m_Scale.x == 0 && m_Scale.y == 0)
		{
			int w, h;
			SDL_QueryTexture(m_Texture->GetSDLTexture(), NULL, NULL, &w, &h);
			dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x - w / 2, pos.y - h);
		}
		else dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x - m_Scale.x / 2, pos.y - m_Scale.y, m_Scale.x, m_Scale.y);
	}
}

void ImageComponent::Update()
{
	if (!m_IsSprite) return;
	float frameTime = 1.f / m_FramesPerSecond;

	m_AccuTime += Timer::GetInstance().GetElapsedSeconds();
	if (m_AccuTime > frameTime)
	{
		++m_CurrentFrame %= m_EndFrame;
		if (m_CurrentFrame < m_StartFrame) m_CurrentFrame = m_StartFrame;
		m_AccuTime -= frameTime;
	}
}
void ImageComponent::MakeAnimated(int rows, int cols, int totalFrames)
{
	m_IsSprite = true;
	m_Rows = rows;
	m_Cols = cols;
	m_EndFrame = totalFrames;
}

void ImageComponent::SetFramesPerSecond(int fps)
{
	m_FramesPerSecond = fps;
}

void ImageComponent::SetDimensions(float w, float h)
{
	m_Scale.x = w;
	m_Scale.y = h;
}

void ImageComponent::FlipTexture(SDL_RendererFlip flip)
{
	m_CurrRFlip = flip;
}

void ImageComponent::SetStartFrame(int frame)
{
	m_StartFrame = frame;
}

void ImageComponent::SetEndFrame(int frame)
{
	m_EndFrame = frame;
}