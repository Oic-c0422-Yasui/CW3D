#pragma once

#include <memory>
#include <stdint.h>


namespace ActionGame
{
	/*
	* @brief�@�R���{�C���^�t�F�[�X
	*/
	class __declspec(novtable) ICombo
	{
	public:
		virtual ~ICombo() = default;

		/*
		* @brief	�R���{���擾
		*/
		virtual uint32_t GetCount() const noexcept = 0;

		/*
		* @brief	�R���{���ǉ�
		*/
		virtual void AddCount() noexcept = 0;
	};

	using ComboPtr = std::shared_ptr<ICombo>;
}
