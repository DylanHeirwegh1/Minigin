#include "MiniginPCH.h"
#include "InputManager.h"

bool dae::InputManager::ProcessInput()
{
	if (m_controllers.size() == 0)
	{
		return true;
	}
	for (auto& controller : m_controllers)
	{
		controller->Update();
	}
	m_pKeyboard->Update();

	for (auto& kc : m_KeyCommands)
	{
		switch (kc.ks)
		{
		case KeyState::Down:
			if (IsDown(kc.ControllerID, static_cast<unsigned>(kc.Button)))
				if (!kc.Command->Execute()) return false;
			break;
		case KeyState::Up:
			if (IsReleased(kc.ControllerID, static_cast<unsigned>(kc.Button)))
				if (!kc.Command->Execute()) return false;
			break;
		case KeyState::Pressed:
			if (IsPressed(kc.ControllerID, static_cast<unsigned>(kc.Button)))
				if (!kc.Command->Execute()) return false;
			break;
		}
	}
	for (auto& kc : m_KeyboardCommands)
	{
		switch (kc.ks)
		{
		case KeyState::Down:
			if (IsKeyDown(static_cast<unsigned>(kc.Key)))
				if (!kc.Command->Execute()) return false;
			break;
		case KeyState::Up:
			if (IsKeyReleased(static_cast<unsigned>(kc.Key)))
				if (!kc.Command->Execute()) return false;
			break;
		case KeyState::Pressed:
			if (IsKeyPressed(static_cast<unsigned>(kc.Key)))
				if (!kc.Command->Execute()) return false;
			break;
		}
	}

	return true;
}

dae::InputManager::InputManager()
{
	//give button and command attached to it.
	m_controllers.push_back(std::make_unique<XBox360Controller>(1));
	m_pKeyboard = std::make_unique<KeyBoard>();
}

dae::InputManager::~InputManager()
{
}

bool dae::InputManager::IsPressed(unsigned int controllerID, unsigned int key) const
{
	return m_controllers[controllerID]->IsPressed(key);
}
bool dae::InputManager::IsReleased(unsigned int controllerID, unsigned int key) const
{
	return m_controllers[controllerID]->IsUp(key);
}

bool dae::InputManager::IsDown(unsigned int controllerID, unsigned int key) const
{
	return m_controllers[controllerID]->IsDown(key);
}

bool dae::InputManager::IsKeyPressed(unsigned int key) const
{
	return m_pKeyboard->IsPressed(key);
}

bool dae::InputManager::IsKeyReleased(unsigned int key) const
{
	return m_pKeyboard->IsReleased(key);
}

bool dae::InputManager::IsKeyDown(unsigned int key) const
{
	return m_pKeyboard->IsDown(key);
}

void dae::InputManager::AddKeyCommand(XBox360Controller::ControllerButton button, std::shared_ptr<Command> command, int controllerID, KeyState
	keyState)
{
	m_KeyCommands.push_back(XboxKeyCommand(button, command, controllerID, keyState));
}

void dae::InputManager::AddKeyCommand(int button, std::shared_ptr<Command> command, KeyState keyState)
{
	m_KeyboardCommands.push_back(KeyBoardKeyCommand(button, command, keyState));
}

void dae::InputManager::AddController(unsigned int ID, std::shared_ptr<GameObject>gameActor)
{
	m_controllers.push_back(std::make_unique<XBox360Controller>(ID));
}