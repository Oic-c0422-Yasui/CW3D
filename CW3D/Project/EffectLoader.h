#pragma once
#include "json.hpp"
#include <fstream>
#include <codecvt>

namespace ActionGame
{
	/*
	* @brief	エフェクト読み込み用クラス
	*/
	class JsonEffectLoader
	{
	public:
		JsonEffectLoader();
		~JsonEffectLoader();
		/**
		* @brief		JSonファイルからの生成
		* @return		true　なら成功
		*/
		bool Load(const std::string& name);
		/**
		 * @brief		生成
		 */
		bool Load(nlohmann::json& os);

	};
}



