#pragma once
class KeyBoard
{
public:
	KeyBoard();
	bool IsDown(unsigned int key);
	bool IsPressed(unsigned int key);
	bool IsReleased(unsigned int key);
	void Update();

private:
	SDL_Event m_Event;
	bool m_PrevState[256]{};
	bool m_CurrState[256]{};
};
