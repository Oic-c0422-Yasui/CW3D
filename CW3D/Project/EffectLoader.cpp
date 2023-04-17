#include "EffectLoader.h"
#include "ResourceManager.h"
#include "EffectRenderer.h"
#include "ConvertUtilities.h"

ActionGame::JsonEffectLoader::JsonEffectLoader()
{
}

ActionGame::JsonEffectLoader::~JsonEffectLoader()
{
}

bool ActionGame::JsonEffectLoader::Load(const std::string& name)
{
	std::ifstream ifs(name);
	if (ifs.fail())
	{
		return false;
	}
	nlohmann::json os = nlohmann::json::parse(ifs);
	return Load(os);
}

bool ActionGame::JsonEffectLoader::Load(nlohmann::json& os)
{

	//�f�B���N�g�����擾
	std::string dirName;
	os["Directory"].get_to(dirName);
	//u16string�ɕϊ�
	auto u16DirName = MyUtil::ConvertUTF8ToUTF16(dirName);

	//�G�t�F�N�g�}�l�[�W���[
	const auto& manager = EffectRendererInstance.GetManager();
	Effekseer::EffectRef effectRef;
	//���\�[�X�Ǘ��̃C���X�^���X
	auto& instance = ResourceManager<Effekseer::EffectRef>::GetInstance();
	//���\�[�X�̃^�O
	constexpr auto tag = "Effect";

	auto& effects = os["Effects"];
	for (auto effect : effects)
	{
		//�L�[��
		std::string name;
		effect["Name"].get_to(name);

		//�t�@�C����
		std::string fn;
		effect["File"].get_to(fn);
		
		//�ǂݍ��ރt�@�C���Ƀf�B���N�g�����܂߂�
		auto fileName = u16DirName + MyUtil::ConvertUTF8ToUTF16(fn);
		auto fileNameStr = fileName.c_str();

		//�ǂݍ���
		effectRef = Effekseer::Effect::Create(manager, fileNameStr);
		if (effectRef == nullptr)
		{
			return false;
		}

		//���\�[�X��o�^
		instance.AddResource(tag, name, effectRef);
	}


	return true;
}

////�G�t�F�N�g�}�l�[�W���[
	//const auto& manager = EffectRendererInstance.GetManager();
	////���\�[�X�Ǘ��̃C���X�^���X
	//auto& instance = ResourceManager<Effekseer::EffectRef>::GetInstance();
	////���\�[�X�̃^�O
	//constexpr auto tag = "Effect";

	//Effekseer::EffectRef effect = Effekseer::Effect::Create(manager, u"Effect/Laser01.efk");
	//if (effect == nullptr)
	//{
	//	return false;
	//}
	//instance.AddResource(tag, "AttackEffect1", effect);

	//effect = Effekseer::Effect::Create(manager, u"Effect/sword.efk");
	//if (effect == nullptr)
	//{
	//	return false;
	//}
	//instance.AddResource(tag, "DamageEffect1", effect);

	//effect = Effekseer::Effect::Create(manager, u"Effect/tuki.efk");
	//if (effect == nullptr)
	//{
	//	return false;
	//}
	//instance.AddResource(tag, "AttackEffect2", effect);

	//effect = Effekseer::Effect::Create(manager, u"Effect/sandStome.efk");
	//if (effect == nullptr)
	//{
	//	return false;
	//}
	//instance.AddResource(tag, "SkillEffect1", effect);

	//effect = Effekseer::Effect::Create(manager, u"Effect/Laser01.efk");
	//if (effect == nullptr)
	//{
	//	return false;
	//}
	//instance.AddResource(tag, "SkillEffect2", effect);

	//effect = Effekseer::Effect::Create(manager, u"Effect/tornade.efk");
	//if (effect == nullptr)
	//{
	//	return false;
	//}
	//instance.AddResource(tag, "SkillEffect3", effect);

	//effect = Effekseer::Effect::Create(manager, u"Effect/fire.efk");
	//if (effect == nullptr)
	//{
	//	return false;
	//}
	//instance.AddResource(tag, "SkillEffect4", effect);

	//effect = Effekseer::Effect::Create(manager, u"Effect/drill.efk");
	//if (effect == nullptr)
	//{
	//	return false;
	//}
	//instance.AddResource(tag, "SkillEffect5", effect);

	//effect = Effekseer::Effect::Create(manager, u"Effect/Track1.efk");
	//if (effect == nullptr)
	//{
	//	return false;
	//}
	//instance.AddResource(tag, "ClosedEffect", effect);

	//effect = Effekseer::Effect::Create(manager, u"Effect/Clow1.efk");
	//if (effect == nullptr)
	//{
	//	return false;
	//}
	//instance.AddResource(tag, "AttackEffect3", effect);

	//effect = Effekseer::Effect::Create(manager, u"Effect/A_Sylph2.efk");
	//if (effect == nullptr)
	//{
	//	return false;
	//}
	//instance.AddResource(tag, "EscapeEffect", effect);

	//effect = Effekseer::Effect::Create(manager, u"Effect/MonsterRoar.efk");
	//if (effect == nullptr)
	//{
	//	return false;
	//}
	//instance.AddResource(tag, "RoarEffect", effect);

 //   return true;