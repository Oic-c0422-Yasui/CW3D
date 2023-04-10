#pragma once

#include <memory>
#include <stdint.h>


namespace ActionGame
{
	/*
	* @brief　コンボインタフェース
	*/
	class __declspec(novtable) ICombo
	{
	public:
		virtual ~ICombo() = default;

		/*
		* @brief	コンボ数取得
		*/
		virtual uint32_t GetCount() const noexcept = 0;

		/*
		* @brief	コンボ数追加
		*/
		virtual void AddCount() noexcept = 0;
	};

	using ComboPtr = std::shared_ptr<ICombo>;
}
