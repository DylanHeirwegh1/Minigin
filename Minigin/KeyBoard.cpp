#include "MiniginPCH.h"
#include "KeyBoard.h"

//#include "backends/imgui_impl_sdl.h"

KeyBoard::KeyBoard()
{
}

bool KeyBoard::IsDown(unsigned int key)
{
	return m_CurrState[key];
}

bool KeyBoard::IsPressed(unsigned int key)
{
	return m_CurrState[key] && !m_PrevState[key];
}

bool KeyBoard::IsReleased(unsigned int key)
{
	return !m_CurrState[key] && m_PrevState[key];
}

void KeyBoard::Update()
{
	//ImGui_ImplSDL2_ProcessEvent(&m_Event);
	CopyMemory(&m_PrevState, &m_CurrState, sizeof(bool) * 256);
	ZeroMemory(&m_CurrState, sizeof(bool) * 256);

	SDL_PollEvent(&m_Event);
	const Uint8* state = SDL_GetKeyboardState(NULL);
	for (size_t i = 0; i < 256; ++i)
		m_CurrState[i] = state[i];
}