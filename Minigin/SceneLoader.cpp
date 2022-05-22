#include "MiniginPCH.h"
#include "SceneLoader.h"
#include "filereadstream.h"
#include <document.h>

#include "GameObject.h"
#include "ImageComponent.h"
#include "IngredientComponent.h"
#include "RigidBody.h"

void SceneLoader::LoadLevelFromFile(const wchar_t* path, dae::Scene& scene)
{
	ParseFile(path);
	if (m_Objects.size() == 0) return;

	for (auto obj : m_Objects)
	{
		if (obj.type == "block")
		{
			std::shared_ptr<dae::GameObject> currBlock = std::make_shared<dae::GameObject>();

			currBlock->SetWorldPosition({ obj.pos[0],obj.pos[1],0 });
			currBlock->AddComponent<RigidBody>()->SetSize({ obj.size[0],obj.size[1] });
			//currBlock->GetComponent<RigidBody>()->SetVisible(true);
			scene.Add(currBlock);
			std::cout << "pos: " << obj.pos[0] << ", " << obj.pos[1]
				<< " size: " << obj.size[0] << ", " << obj.size[1] << std::endl;
		}
		else if (obj.type == "image")
		{
			auto img = std::make_shared<dae::GameObject>();
			img->AddComponent<ImageComponent>()->SetTexture(obj.path);
			img->SetWorldPosition({ obj.pos[0],obj.pos[1],0 });
			img->GetComponent<ImageComponent>()->SetDimensions(static_cast<float>(obj.size[0]), static_cast<float>(obj.size[1]));
			scene.Add(img);
		}
		else if (obj.type == "ingredient")
		{
			auto ingr = std::make_shared<dae::GameObject>();
			ingr->SetWorldPosition({ obj.pos[0],obj.pos[1],0 });
			ingr->AddComponent<ImageComponent>()->SetTexture(obj.path);

			ingr->GetComponent<ImageComponent>()->MakeAnimated(6, 1, obj.startEndFrame[1]);
			ingr->GetComponent<ImageComponent>()->SetStartFrame(obj.startEndFrame[0]);

			ingr->GetComponent<ImageComponent>()->SetDimensions(static_cast<float>(obj.size[0]), static_cast<float>(obj.size[1]));

			ingr->AddComponent<RigidBody>()->SetSize({ static_cast<float>(obj.size[0]), static_cast<float>(obj.size[1]) });
			ingr->GetComponent<RigidBody>()->SetVisible(true);
			ingr->GetComponent<RigidBody>()->SetTag("Ingredient");
			ingr->GetComponent<RigidBody>()->OverlapWithTag({ "Player","Enemy" });

			ingr->AddComponent<IngredientComponent>();
			scene.Add(ingr);
		}
	}
}

void SceneLoader::ParseFile(const wchar_t* path)
{
	Object temp{};
	FILE* file = nullptr;
	_wfopen_s(&file, path, L"r");

	if (!file)return;
	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* buffer = new char[size];

	rapidjson::FileReadStream stream(file, buffer, size);

	rapidjson::Document doc;
	doc.ParseStream(stream);
	for (rapidjson::Value::ConstValueIterator typeIt = doc.Begin(); typeIt != doc.End(); ++typeIt)
	{
		//get type
		const rapidjson::Value& type = *typeIt;
		const rapidjson::Value& typeName = type["type"];
		temp.type = typeName.GetString();

		//get pos
		const rapidjson::Value& positionValue = type["pos"];

		temp.pos[0] = positionValue[0].GetInt();
		temp.pos[1] = positionValue[1].GetInt();

		//get size
		const rapidjson::Value& sizeValue = type["size"];

		temp.size[0] = sizeValue[0].GetInt();
		temp.size[1] = sizeValue[1].GetInt();

		if (temp.type == "image")
		{
			const rapidjson::Value& pathName = type["path"];

			temp.path = pathName.GetString();
		}
		else if (temp.type == "ingredient")
		{
			const rapidjson::Value& pathName = type["path"];

			temp.path = pathName.GetString();

			const rapidjson::Value& frameVal = type["frames"];

			temp.startEndFrame[0] = frameVal[0].GetInt();
			temp.startEndFrame[1] = frameVal[1].GetInt();
		}

		m_Objects.push_back(temp);
	}

	delete[] buffer;
	fclose(file);
}