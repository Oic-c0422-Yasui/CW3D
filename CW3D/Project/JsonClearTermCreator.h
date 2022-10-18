#pragma once


#include	"json.hpp"

#include	"ClearTermEnemysAllDead.h"


namespace Sample {
	class IClearTermBuilder
	{
	public:
		virtual ClearTermPtr Create(nlohmann::json& os) = 0;
	};
	using ClearTermBuilderPtr = std::shared_ptr< IClearTermBuilder>;
	class ClearTermDictionary
	{
	private:
		std::map<std::string, ClearTermBuilderPtr> dictionary;
	public:
		ClearTermDictionary() {
			dictionary["AllDead"] = std::make_shared<ClearTermEnemysAllDead>();
		}

		const ClearTermBuilderPtr& GetDictionary(std::string name)
		{
			assert(dictionary.find(name) != dictionary.end());
			return dictionary[name];
		}
	};

	class JsonClearTermCreator
	{
	private:

	public:
		/**
		 * @brief		コンストラクタ
		 */
		JsonClearTermCreator();
		/**
		 * @brief		JSonファイルからの生成
		 */
		std::vector<ClearTermPtr> Create(const std::string& name);
		/**
		 * @brief		生成
		 */
		std::vector<ClearTermPtr> Create(nlohmann::json& os);
	};
}
