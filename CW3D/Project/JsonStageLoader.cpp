#include "JsonStageLoader.h"
#include "ResourceManager.h"

using namespace Sample;

Sample::JsonStageLoader::JsonStageLoader()
	: m_DivisionArray()
{
}

bool Sample::JsonStageLoader::Load(const std::string& name)
{
	std::ifstream ifs(name);
	if (ifs.fail())
	{
		return false;
	}
	nlohmann::json os = nlohmann::json::parse(ifs);
	return Load(os);
}

bool Sample::JsonStageLoader::Load(nlohmann::json& os)
{
	auto& stageMesh = os["StageMesh"];
	std::shared_ptr<CMeshContainer> tempMesh = std::make_shared<CMeshContainer>();
	
	ResourcePtrManager<CMeshContainer>::GetInstance().AddResource("Stage", "StageMesh", tempMesh);

	auto& enemyStatusFile = os["EnemyStatusFile"];
	JsonEnemyStatusLoader statusLoader;
	auto& enemyStatusDictionary = statusLoader.Load(enemyStatusFile);


	JsonDivisionCreator jsonCreator;
	DivisionArrayPtr divisionArray = jsonCreator.Create(os["Divisions"], enemyStatusDictionary);
	m_DivisionArray = divisionArray;

	//敵で使用するメッシュ名格納
	std::vector<std::string> meshNames;
	for (auto& division : *divisionArray)
	{
		for (auto& enemyParam : division->GetEnemysParam())
		{
			auto& typeName = enemyParam.GetParam().m_Type;

			if (meshNames.size() <= 0)
			{
				meshNames.push_back(typeName);
			}
			for (int i = 0; i < meshNames.size(); i++)
			{
				if (typeName == meshNames[i])
				{
					break;
				}
				if (i == meshNames.size())
				{
					meshNames.push_back(typeName);
				}
			}
			
		}
	}

	//敵で使用するメッシュをロード
	for (auto& meshName : meshNames)
	{
		if (!enemyStatusDictionary.IsContain(meshName))
		{
			continue;
		}
		if (!ResourcePtrManager<CMeshContainer>::GetInstance().IsContainResource("Enemy", meshName))
		{
			//敵の辞書を取得
			auto& dictionary = enemyStatusDictionary.Get(meshName);
			//メッシュを作成
			tempMesh = std::make_shared<CMeshContainer>();
			//メッシュの名前をChar*へ変換
			const char* str = dictionary->m_MeshName.c_str();
			if (tempMesh->Load(str) != MOFMODEL_RESULT_SUCCEEDED)
			{
				return false;
			}
			//リソースを追加
			ResourcePtrManager<CMeshContainer>::GetInstance().AddResource("Enemy",meshName, tempMesh);
		}
	}


	return true;
}

