#include "JsonClearTermCreator.h"


ClearTerm::JsonClearTermCreator::JsonClearTermCreator()
	:dictionary_()
{
}

ClearTerm::ClearTermArray ClearTerm::JsonClearTermCreator::Create(const std::string& name)
{
	std::ifstream ifs(name);
	if (ifs.fail())
	{
		return ClearTermArray();
	}
	nlohmann::json os = nlohmann::json::parse(ifs);
	return Create(os);
}

ClearTerm::ClearTermArray ClearTerm::JsonClearTermCreator::Create(nlohmann::json& os)
{
	ClearTermArray	ClearTerms;
	for (auto& str : os)
	{
		auto& type = str["Type"];

		std::string typeName;
		type["Name"].get_to(typeName);

		//辞書からクリア条件のビルダーを取得
		auto& builder = dictionary_.Get(typeName);

		//クリア条件を生成
		auto clearTerm = builder->Create(type);
		ClearTerms.push_back(clearTerm);
	}
	return ClearTerms;
}
