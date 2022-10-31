#include "JsonStageLoader.h"
#include "ResourceManager.h"

using namespace Sample;

Sample::JsonStageLoader::JsonStageLoader()
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
	
	ResourceManager<CMeshContainer>::GetInstance().AddResource("StageMesh", tempMesh);

	auto& enemyStatusFile = os["EnemyStatusFile"];
	JsonEnemyStatusLoader statusLoader;
	auto& enemyStatusDictionary = statusLoader.Load(enemyStatusFile);

	for (auto& enemyStatus : enemyStatusDictionary.GetMap())
	{
		if (!ResourceManager<CMeshContainer>::GetInstance().IsContain(enemyStatus.first))
		{
			//メッシュを作成
			tempMesh = std::make_shared<CMeshContainer>();
			//メッシュの名前をChar*へ変換
			const char* str = enemyStatus.second->m_MeshName.c_str();
			if (tempMesh->Load(str) != MOFMODEL_RESULT_SUCCEEDED)
			{
				return false;
			}
			//リソースを追加
			ResourceManager<CMeshContainer>::GetInstance().AddResource(enemyStatus.first, tempMesh);
		}
	}


	return true;
}
