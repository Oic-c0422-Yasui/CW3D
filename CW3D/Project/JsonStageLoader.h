#pragma once

#include	"JsonDivisionCreator.h"


namespace ActionGame
{
	class JsonStageLoader
	{
	private:
		DivisionArrayPtr divisionArray_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		JsonStageLoader();
		/*
		* @brief		デストラクタ
		*/
		~JsonStageLoader();
		/**
		 * @brief		JSonファイルからの生成
		 */
		bool Load(const std::string& name);
		/**
		 * @brief		生成
		 */
		bool Load(nlohmann::json& os);

		const DivisionArrayPtr& GetDivisionArray() const noexcept
		{
			return divisionArray_;
		}
	};

}


