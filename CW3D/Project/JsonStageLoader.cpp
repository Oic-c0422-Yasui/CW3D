#include "JsonStageLoader.h"
#include "ResourceManager.h"

using namespace ActionGame;

ActionGame::JsonStageLoader::JsonStageLoader()
	: m_DivisionArray()
{
}

bool ActionGame::JsonStageLoader::Load(const std::string& name)
{
	std::ifstream ifs(name);
	if (ifs.fail())
	{
		return false;
	}
	nlohmann::json os = nlohmann::json::parse(ifs);
	return Load(os);
}

bool ActionGame::JsonStageLoader::Load(nlohmann::json& os)
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
		for (auto& enemyParam : *division->GetEnemysParam())
		{
			auto& type = enemyParam->GetParam().m_Type;

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
		//�G�̃^�C�v�����݂��Ȃ��Ȃ玟�̔z���
		if (!enemyStatusDictionary.IsContain(type))
		{
			continue;
		}

		//�G�̎������擾
		auto& dictionary = enemyStatusDictionary.Get(type);
		//���b�V�������łɓo�^����Ă���Ȃ玟�̔z���
		if (ResourcePtrManager<CMeshContainer>::GetInstance().IsContainResource("Enemy", dictionary->m_MeshName))
		{
			continue;
		}

		//���b�V�����쐬
		tempMesh = std::make_shared<CMeshContainer>();
		//���b�V���̖��O��Char*�֕ϊ�
		const char* meshName = dictionary->m_MeshName.c_str();
		//���b�V���̃��[�h
		if (tempMesh->Load(meshName) != MOFMODEL_RESULT_SUCCEEDED)
		{
			return false;
		}
		//���b�V�������\�[�X�ɒǉ�
		ResourcePtrManager<CMeshContainer>::GetInstance().AddResource("Enemy", dictionary->m_MeshName, tempMesh);
	}

	return true;
}

