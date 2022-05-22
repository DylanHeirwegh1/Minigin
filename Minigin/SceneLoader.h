#include "Scene.h"
#include "Singleton.h"
#pragma once
class SceneLoader : public dae::Singleton<SceneLoader>
{
public:
	void LoadLevelFromFile(const wchar_t* path, dae::Scene& scene);
private:
	void ParseFile(const wchar_t* path);

	struct Object
	{
		std::string type;
		int size[2];
		int pos[2];
		int startEndFrame[2];
		std::string path;
	};
	std::vector<Object> m_Objects;
};
