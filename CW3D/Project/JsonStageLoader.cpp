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
		if (ResourceManager<CMeshContainer>::GetInstance().IsContain(enemyStatus.first))
		{
			tempMesh = std::make_shared<CMeshContainer>();
			if (tempMesh->Load(enemyStatus.second->m_MeshName) != MOFMODEL_RESULT_SUCCEEDED)
			{
				return false;
			}
		}
	}


	return true;
}
