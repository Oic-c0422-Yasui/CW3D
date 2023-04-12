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
	//ステージメッシュの読み込み
	auto& stageMesh = os["StageMesh"];
	std::string stageMeshName;
	stageMesh.get_to(stageMeshName);
	//string→char*に変換
	const char* meshName = stageMeshName.c_str();
	
	//メッシュ読み込み
	std::shared_ptr<CMeshContainer> tempMesh = std::make_shared<CMeshContainer>();
	if (!tempMesh->Load(meshName))
	{
		return false;
	}
	ResourcePtrManager<CMeshContainer>::GetInstance().AddResource("Stage", "StageMesh", tempMesh);
	CServiceLocator<MyClass::CGiveTextureToMaterial>::GetService()->Give(tempMesh);

	//敵情報の読み込み
	auto& enemyStatusFile = os["EnemyStatusFile"];
	std::string fileName;
	enemyStatusFile.get_to(fileName);
	JsonEnemyStatusLoader statusLoader;
	auto& enemyStatusDictionary = statusLoader.Load(fileName);
	
	//区画の生成
	JsonDivisionCreator divisionCreator;
	DivisionArrayPtr divisionArray = divisionCreator.Create(os["Divisions"], enemyStatusDictionary);
	divisionArray_ = divisionArray;


	//敵のメッシュ名格納
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
				//同じタイプ名が見つからなければメッシュ名を追加
				if (i == typeNames.size() - 1)
				{
					typeNames.push_back(type);
				}
			}
			
		}
	}

	//敵のメッシュをロード
	for (auto& type : typeNames)
	{
		//敵のタイプが存在しないなら次の配列へ
		if (!enemyStatusDictionary.IsContain(type))
		{
			continue;
		}

		//敵の辞書を取得
		auto& dictionary = enemyStatusDictionary.Get(type);
		//メッシュがすでに登録されているなら次の配列へ
		if (ResourcePtrManager<CMeshContainer>::GetInstance().IsContainResource("Enemy", dictionary->MeshName))
		{
			continue;
		}

		//メッシュの名前をChar*へ変換
		const char* meshName = dictionary->MeshName.c_str();
		//メッシュのロード
		tempMesh = std::make_shared<CMeshContainer>();
		if (tempMesh->Load(meshName) != MOFMODEL_RESULT_SUCCEEDED)
		{
			return false;
		}
		CServiceLocator<MyClass::CGiveTextureToMaterial>::GetService()->Give(tempMesh);
		//メッシュをリソースに追加
		ResourcePtrManager<CMeshContainer>::GetInstance().AddResource("Enemy", dictionary->MeshName, tempMesh);
	}

	return true;
}

