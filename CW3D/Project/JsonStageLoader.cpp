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

	//�G�Ŏg�p���郁�b�V�����i�[
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

	//�G�Ŏg�p���郁�b�V�������[�h
	for (auto& meshName : meshNames)
	{
		if (!enemyStatusDictionary.IsContain(meshName))
		{
			continue;
		}
		if (!ResourcePtrManager<CMeshContainer>::GetInstance().IsContainResource("Enemy", meshName))
		{
			//�G�̎������擾
			auto& dictionary = enemyStatusDictionary.Get(meshName);
			//���b�V�����쐬
			tempMesh = std::make_shared<CMeshContainer>();
			//���b�V���̖��O��Char*�֕ϊ�
			const char* str = dictionary->m_MeshName.c_str();
			if (tempMesh->Load(str) != MOFMODEL_RESULT_SUCCEEDED)
			{
				return false;
			}
			//���\�[�X��ǉ�
			ResourcePtrManager<CMeshContainer>::GetInstance().AddResource("Enemy",meshName, tempMesh);
		}
	}


	return true;
}

