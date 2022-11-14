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
	//�X�e�[�W���b�V���̓ǂݍ���
	auto& stageMesh = os["StageMesh"];
	std::string stageMeshName;
	stageMesh.get_to(stageMeshName);
	std::shared_ptr<CMeshContainer> tempMesh = std::make_shared<CMeshContainer>();
	const char* meshName = stageMeshName.c_str();
	if (!tempMesh->Load(meshName))
	{
		return false;
	}
	ResourcePtrManager<CMeshContainer>::GetInstance().AddResource("Stage", "StageMesh", tempMesh);

	//�G���̓ǂݍ���
	auto& enemyStatusFile = os["EnemyStatusFile"];
	std::string fileName;
	enemyStatusFile.get_to(fileName);
	JsonEnemyStatusLoader statusLoader;
	auto& enemyStatusDictionary = statusLoader.Load(fileName);
	
	//���̐���
	JsonDivisionCreator divisionCreator;
	DivisionArrayPtr divisionArray = divisionCreator.Create(os["Divisions"], enemyStatusDictionary);
	m_DivisionArray = divisionArray;


	//�G�Ŏg�p���郁�b�V�����i�[
	std::vector<std::string> typeNames;
	for (auto& division : *divisionArray)
	{
		for (auto& enemyParam : division->GetEnemysParam())
		{
			auto& type = enemyParam.GetParam().m_Type;

			if (typeNames.size() <= 0)
			{
				typeNames.push_back(type);
			}
			for (int i = 0; i < typeNames.size(); i++)
			{
				if (type == typeNames[i])
				{
					break;
				}
				if (i == typeNames.size() - 1)
				{
					typeNames.push_back(type);
				}
			}
			
		}
	}

	//�G�Ŏg�p���郁�b�V�������[�h
	for (auto& type : typeNames)
	{
		if (!enemyStatusDictionary.IsContain(type))
		{
			continue;
		}
		//�G�̎������擾
		auto& dictionary = enemyStatusDictionary.Get(type);
		//���b�V�����쐬
		tempMesh = std::make_shared<CMeshContainer>();
		//���b�V���̖��O��Char*�֕ϊ�
		const char* str = dictionary->m_MeshName.c_str();
		if (tempMesh->Load(str) != MOFMODEL_RESULT_SUCCEEDED)
		{
			return false;
		}
		//���\�[�X��ǉ�
		ResourcePtrManager<CMeshContainer>::GetInstance().AddResource("Enemy", type, tempMesh);
	}

	return true;
}

