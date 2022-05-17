#include "MiniginPCH.h"
#include "XBox360Controller.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment (lib, "xinput.lib")

class XBox360Controller::XBox360ControllerImpl
{
public:
	XBox360ControllerImpl(int controllerIdx);
	void Update();
	bool IsDownThisFrame(unsigned int button) const;
	bool IsUpThisFrame(unsigned int button) const;
	bool IsPressed(unsigned int button) const;
private:
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};

	WORD buttonsPressedThisFrame{};
	WORD buttonsReleasedThisFrame{};

	int m_ControllerIndex{};
};

XBox360Controller::XBox360ControllerImpl::XBox360ControllerImpl(int controllerIdx)
{
	ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	m_ControllerIndex = controllerIdx;
}

void XBox360Controller::XBox360ControllerImpl::Update()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	buttonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	buttonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

bool XBox360Controller::XBox360ControllerImpl::IsDownThisFrame(unsigned int button) const
{
	return buttonsPressedThisFrame & button;
}

bool XBox360Controller::XBox360ControllerImpl::IsUpThisFrame(unsigned int button) const
{
	return buttonsReleasedThisFrame & button;
}

bool XBox360Controller::XBox360ControllerImpl::IsPressed(unsigned int button) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}

XBox360Controller::XBox360Controller(int controllerIdx)
{
	m_pImpl = new XBox360ControllerImpl(controllerIdx);
}
XBox360Controller::~XBox360Controller()
{
	delete m_pImpl;
}

void XBox360Controller::Update()
{
	m_pImpl->Update();
}

bool XBox360Controller::IsPressed(unsigned int controllerButton) const
{
	return m_pImpl->IsPressed(controllerButton);
}

bool XBox360Controller::IsDown(unsigned int button) const
{
	return m_pImpl->IsDownThisFrame(button);
}

bool XBox360Controller::IsUp(unsigned int button) const
{
	return m_pImpl->IsUpThisFrame(button);
}