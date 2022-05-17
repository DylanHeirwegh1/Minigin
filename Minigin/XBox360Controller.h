#pragma once
class XBox360Controller
{
private:
	class XBox360ControllerImpl;

public:
	enum class ControllerButton
	{
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
		ButtonUP = 0x0001,
		ButtonDOWN = 0x0002,
		ButtonLEFT = 0x0004,
		ButtonRIGHT = 0x0008,
		ButtonSTART = 0x0010,
		ButtonBACK = 0x0020,
		ButtonLT = 0x0040,
		ButtonRT = 0x0080,
		ButtonLS = 0x0100,
		ButtonRS = 0x0200,
		KeyUp = 0x26
	};
	XBox360Controller(int controllerIdx);
	~XBox360Controller();
	XBox360ControllerImpl* m_pImpl = nullptr;
	void Update();
	bool IsDown(unsigned int button)const;
	bool IsUp(unsigned int ControllerButton) const;
	bool IsPressed(unsigned int controllerButton) const;
};
