#pragma once
#include	"json.hpp"
#include	"JsonDivisionCreator.h"


namespace ActionGame
{
	class JsonStageLoader
	{
	private:
		DivisionArrayPtr divisionArray_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		JsonStageLoader();
		/**
		 * @brief		JSon�t�@�C������̐���
		 */
		bool Load(const std::string& name);
		/**
		 * @brief		����
		 */
		bool Load(nlohmann::json& os);

		const DivisionArrayPtr& GetDivisionArray() const noexcept
		{
			return divisionArray_;
		}
	};

}


