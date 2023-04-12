#include "JsonStageLoader.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "GiveTextureToMaterial.h"

using namespace ActionGame;

ActionGame::JsonStageLoader::JsonStageLoader()
	: divisionArray_()
{
}

ActionGame::JsonStageLoader::~JsonStageLoader()
{
	divisionArray_.reset();
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
	//string��char*�ɕϊ�
	const char* meshName = stageMeshName.c_str();
	
	//���b�V���ǂݍ���
	std::shared_ptr<CMeshContainer> tempMesh = std::make_shared<CMeshContainer>();
	if (!tempMesh->Load(meshName))
	{
		return false;
	}
	ResourcePtrManager<CMeshContainer>::GetInstance().AddResource("Stage", "StageMesh", tempMesh);
	CServiceLocator<MyClass::CGiveTextureToMaterial>::GetService()->Give(tempMesh);

	//�G���̓ǂݍ���
	auto& enemyStatusFile = os["EnemyStatusFile"];
	std::string fileName;
	enemyStatusFile.get_to(fileName);
	JsonEnemyStatusLoader statusLoader;
	auto& enemyStatusDictionary = statusLoader.Load(fileName);
	
	//���̐���
	JsonDivisionCreator divisionCreator;
	DivisionArrayPtr divisionArray = divisionCreator.Create(os["Divisions"], enemyStatusDictionary);
	divisionArray_ = divisionArray;


	//�G�̃��b�V�����i�[
	std::vector<std::string> typeNames;
	for (auto& division : *divisionArray)
	{
		for (auto& enemyParam : *division->GetEnemysParam())
		{
			auto& type = enemyParam->GetParam().type_;

			if (typeNames.size() <= 0)
			{
				typeNames.push_back(type);
			}
			for (size_t i = 0; i < typeNames.size(); i++)
			{
				if (type == typeNames[i])
				{
					break;
				}
				//�����^�C�v����������Ȃ���΃��b�V������ǉ�
				if (i == typeNames.size() - 1)
				{
					typeNames.push_back(type);
				}
			}
			
		}
	}

	//�G�̃��b�V�������[�h
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
		if (ResourcePtrManager<CMeshContainer>::GetInstance().IsContainResource("Enemy", dictionary->MeshName))
		{
			continue;
		}

		//���b�V���̖��O��Char*�֕ϊ�
		const char* meshName = dictionary->MeshName.c_str();
		//���b�V���̃��[�h
		tempMesh = std::make_shared<CMeshContainer>();
		if (tempMesh->Load(meshName) != MOFMODEL_RESULT_SUCCEEDED)
		{
			return false;
		}
		CServiceLocator<MyClass::CGiveTextureToMaterial>::GetService()->Give(tempMesh);
		//���b�V�������\�[�X�ɒǉ�
		ResourcePtrManager<CMeshContainer>::GetInstance().AddResource("Enemy", dictionary->MeshName, tempMesh);
	}

	return true;
}

