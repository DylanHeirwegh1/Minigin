#include "pch.h"
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif
#include <SDL_filesystem.h>

#include <SDL_pixels.h>

#include "ImageComponent.h"
#include "Minigin.h"

#include "BTScene.h"

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