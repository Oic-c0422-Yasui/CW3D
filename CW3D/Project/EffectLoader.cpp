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
