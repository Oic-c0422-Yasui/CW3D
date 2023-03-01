#pragma once

#include "ClearTermProvider.h"
#include <vector>
#include <string>

namespace ClearTerm
{
	/*
	* @brief	�N���A�����̃C���^�t�F�[�X
	*/
	class __declspec(novtable) IClearTerm
	{
	public:
		virtual ~IClearTerm() = default;
		/*
		* @brief	�N���A�����𖞂����Ă��邩�H
		* @param	provider �N���A����ɕK�v�ȏ��̃v���o�C�_
		*/
		virtual bool IsClear(const ProviderPtr& provider) = 0;
		/*
		* @brief	�N���A�����̎��
		*/
		virtual const std::string& GetType() const noexcept = 0;
	};
	using ClearTermPtr = std::shared_ptr<IClearTerm>;
	using ClearTermArray = std::vector<ClearTermPtr>;
}

