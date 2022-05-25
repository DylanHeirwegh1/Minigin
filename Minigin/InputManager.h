#pragma once

#include <memory>
#include <vector>

#include "Command.h"
#include "GameObject.h"
#include "Singleton.h"
#include "XBox360Controller.h"

#include "KeyBoard.h"
class XBox360Controller;

namespace dae
{
	enum class KeyState
	{
		Down,
		Pressed,
		Up
	};

	class InputManager : public dae::Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		InputManager();
		~InputManager();
		bool IsPressed(unsigned int controllerID, unsigned int key) const;
		bool IsReleased(unsigned int controllerID, unsigned int key) const;
		bool IsDown(unsigned int controllerID, unsigned int key) const;

		bool IsKeyPressed(unsigned int key) const;
		bool IsKeyReleased(unsigned int key) const;
		bool IsKeyDown(unsigned int key) const;

		void AddKeyCommand(XBox360Controller::ControllerButton button, std::shared_ptr<Command> command, int controllerID, KeyState keyState);
		void RemoveKeyCommand(XBox360Controller::ControllerButton button);
		void AddKeyCommand(int key, std::shared_ptr<Command> command, KeyState keyState);

		void ClearCommands();

		void AddController(unsigned int ID, std::shared_ptr<GameObject>gameActor);
	private:
		struct XboxKeyCommand
		{
			XboxKeyCommand(XBox360Controller::ControllerButton button, std::shared_ptr<Command> command, int controllerID, KeyState keyState)
				: Button{ button }
				, Command{ command }
				, ControllerID{ controllerID }
				, ks{ keyState }
			{
			}
			XBox360Controller::ControllerButton Button;
			std::shared_ptr<Command> Command;
			int ControllerID;
			std::shared_ptr<GameObject> GameObject;
			KeyState ks;
		};
		struct KeyBoardKeyCommand
		{
			KeyBoardKeyCommand(int key, std::shared_ptr<Command> command, KeyState keyState)
				: Key{ key }
				, Command{ command }
				, ks{ keyState }
			{
			}
			int Key;
			std::shared_ptr<Command> Command;
			KeyState ks;
		};

		std::vector<XboxKeyCommand> m_KeyCommands;
		std::vector<KeyBoardKeyCommand> m_KeyboardCommands;

		std::vector <std::unique_ptr<XBox360Controller>> m_controllers{};
		std::unique_ptr<KeyBoard> m_pKeyboard{};
	};
}
