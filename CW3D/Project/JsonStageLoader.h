#pragma once
#include	"json.hpp"
#include	"JsonDivisionCreator.h"


namespace Sample
{
	class JsonStageLoader
	{
	private:
		DivisionArrayPtr m_DivisionArray;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		JsonStageLoader();
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
			return m_DivisionArray;
		}
	};

}


