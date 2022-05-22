#include "pch.h"
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif
#include <SDL_filesystem.h>

#include <SDL_pixels.h>
#include <SDL_scancode.h>

#include "FPSComponent.h"
#include "ImageComponent.h"
#include "Minigin.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include <direct.h>
#include "BTScene.h"
#include "EnemyComponent.h"
#include "Renderer.h"
#include <imgui.h>

#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"

void InitGame()
{
	BTScene{};
}
int main(int, char* []) {
	dae::Minigin engine;
	engine.Initialize();

	InitGame();

	engine.Run();

	return 0;
}