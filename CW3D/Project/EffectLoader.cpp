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

	//ディレクトリ名取得
	std::string dirName;
	os["Directory"].get_to(dirName);
	//u16stringに変換
	auto u16DirName = MyUtil::ConvertUTF8ToUTF16(dirName);

	//エフェクトマネージャー
	const auto& manager = EffectRendererInstance.GetManager();
	Effekseer::EffectRef effectRef;
	//リソース管理のインスタンス
	auto& instance = ResourceManager<Effekseer::EffectRef>::GetInstance();
	//リソースのタグ
	constexpr auto tag = "Effect";

	auto& effects = os["Effects"];
	for (auto effect : effects)
	{
		//キー名
		std::string name;
		effect["Name"].get_to(name);

		//ファイル名
		std::string fn;
		effect["File"].get_to(fn);
		
		//読み込むファイルにディレクトリを含める
		auto fileName = u16DirName + MyUtil::ConvertUTF8ToUTF16(fn);
		auto fileNameStr = fileName.c_str();

		//読み込み
		effectRef = Effekseer::Effect::Create(manager, fileNameStr);
		if (effectRef == nullptr)
		{
			return false;
		}

		//リソースを登録
		instance.AddResource(tag, name, effectRef);
	}


	return true;
}
