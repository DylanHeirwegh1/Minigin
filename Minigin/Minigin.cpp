#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "Scene.h"
#include <chrono>

#include "Achievements.h"
#include "BurgerTimeScene.h"
#include "TextComponent.h"

#include "Timer.h"
#include "FPSComponent.h"
#include "HealthComponent.h"
#include "ObserverScene.h"
#include "ScoreComponent.h"
#include "SoundScene.h"

using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		640,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
	ResourceManager::GetInstance().Init("../Data/");
	LoadGame();
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	//create scene
	//ObserverScene scene{};
	//BurgerTimeScene scene{};
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();

	//GAME LOOP
	bool doContinue = true;
	Timer::GetInstance().Start();
	float lag = 0.0f;
	Timer::GetInstance().SetFixedTimeStep(0.02f);
	float fixedTimeStep{ Timer::GetInstance().GetFixedTimeStep() };
	while (doContinue)
	{
		Timer::GetInstance().Update();
		float dT = Timer::GetInstance().GetElapsedSeconds();

		lag += dT;
		doContinue = InputManager::GetInstance().ProcessInput();

		while (lag >= fixedTimeStep)
		{
			//add fixed update
			sceneManager.FixedUpdate();
			lag -= fixedTimeStep;
		}
		sceneManager.Update(dT);
		renderer.Render();
	}

	Cleanup();
}