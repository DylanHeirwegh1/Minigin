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
	PhysicsManager::GetInstance().ClearRigidBodys();
	ParseFile(path);
	if (m_Objects.size() == 0) return;

	for (auto obj : m_Objects)
	{
		if (obj.type == "block")
		{
			std::shared_ptr<dae::GameObject> currBlock = std::make_shared<dae::GameObject>();

			currBlock->SetWorldPosition({ obj.pos[0],obj.pos[1],0 });
			auto rb = currBlock->AddComponent<RigidBody>();
			rb->SetTag("Block");
			rb->SetSize({ obj.size[0],obj.size[1] });
			//rb->SetVisible(true);

			scene.Add(currBlock);
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
			auto img = ingr->AddComponent<ImageComponent>();
			img->SetTexture(obj.path);
			img->MakeAnimated(6, 1, obj.startEndFrame[1]);
			img->SetStartFrame(obj.startEndFrame[0]);
			img->SetDimensions(static_cast<float>(obj.size[0]), static_cast<float>(obj.size[1]));

			auto rb = ingr->AddComponent<RigidBody>();
			rb->SetSize({ static_cast<float>(obj.size[0]), static_cast<float>(obj.size[1]) });
			rb->SetTag("Ingredient");
			rb->OverlapWithTag({ "Player","Enemy","Ingredient","Plate","Ladder" });
			//rb->SetVisible(true);
			ingr->AddComponent<IngredientComponent>();
			ingr->AddComponent<MovementComponent>()->SetMovementSpeed({ 0,60 });
			scene.Add(ingr);
		}
		else if (obj.type == "plate")
		{
			std::shared_ptr<dae::GameObject> plate = std::make_shared<dae::GameObject>();

			plate->SetWorldPosition({ obj.pos[0],obj.pos[1],0 });
			plate->AddComponent<RigidBody>()->SetSize({ obj.size[0],obj.size[1] });

			plate->GetComponent<RigidBody>()->SetTag("Plate");
			plate->GetComponent<RigidBody>()->OverlapWithTag({ "Ingredient" });
			//plate->GetComponent<RigidBody>()->SetVisible(true);
			scene.Add(plate);
		}
		else if (obj.type == "ladder")
		{
			std::shared_ptr<dae::GameObject>ladder = std::make_shared<dae::GameObject>();

			ladder->SetWorldPosition({ obj.pos[0],obj.pos[1],0 });
			auto rb = ladder->AddComponent<RigidBody>();
			rb->SetTag("Ladder");
			rb->SetSize({ obj.size[0],obj.size[1] });
			//rb->SetVisible(true);
			rb->OverlapWithTag({ "Player, Enemy, Ingredient" });
			scene.Add(ladder);
		}
	}
}

void SceneLoader::ParseFile(const wchar_t* path)
{
	m_Objects.clear();
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