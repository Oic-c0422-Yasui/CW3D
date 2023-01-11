#include "JsonEnemyStatusLoader.h"
#include "Utilities.h"


using namespace ActionGame;

JsonEnemyStatusLoader::JsonEnemyStatusLoader()
{
}

EnemyStatusDictionary JsonEnemyStatusLoader::Load(const std::string& name)
{
	std::ifstream ifs(name);
	if (ifs.fail())
	{
		return EnemyStatusDictionary();
	}
	nlohmann::json os = nlohmann::json::parse(ifs);
	return Load(os);
}

EnemyStatusDictionary JsonEnemyStatusLoader::Load(nlohmann::json& os)
{
	auto& Status = os["Status"];
	EnemyStatusDictionary dictionary;
	
	for (auto& state : Status)
	{
		
		//�^�C�v��
		std::string typeName;
		state["Type"].get_to(typeName);
		
		//�L�����̖��O
		std::string name;
		state["Name"].get_to(name);
		//���{��̕\�����s���̂� utf-8 => ShiftJIS�֕ϊ� 
		auto JISname = MyUtilities::UTF8toShiftJIS(name);

		//HP
		int hp;
		state["HP"].get_to(hp);
		
		//�K�E�Z�Q�[�W
		float ultGauge;
		state["UltGauge"].get_to(ultGauge);
		
		//�K�E�Z�Q�[�W�u�[�X�g�{��
		float ultGaugeBoostMag;
		state["UltGaugeBoostMag"].get_to(ultGaugeBoostMag);
		
		//�U����
		int atk;
		state["ATK"].get_to(atk);
		
		//���b�V����
		std::string meshName;
		state["Mesh"].get_to(meshName);

		//�傫��
		Vector3 scaleSize;
		auto& scale = state["Scale"];
		{
			scale["SizeX"].get_to(scaleSize.x);
			scale["SizeY"].get_to(scaleSize.y);
			scale["SizeZ"].get_to(scaleSize.z);
		}

		//�����蔻��
		Vector3 colliderSize;
		float colliderHeight;
		auto& collider = state["Collider"];
		{
			collider["SizeX"].get_to(colliderSize.x);
			collider["SizeY"].get_to(colliderSize.y);
			collider["SizeZ"].get_to(colliderSize.z);
			collider["Height"].get_to(colliderHeight);
		}

		EnemyStatusPtr enemyStateus = 
			std::make_shared<EnemyStatus>(EnemyStatus(hp,ultGauge, ultGaugeBoostMag,atk,meshName, JISname,scaleSize,colliderSize,colliderHeight));
		dictionary.Add(typeName,enemyStateus);
	}
	

	return dictionary;
}
