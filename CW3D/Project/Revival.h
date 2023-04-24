#pragma once
#include "RevivalCount.h"

namespace ActionGame
{

	/*
	* @brief	復活用クラス
	*/
	class CRevival
	{
	private:
		RevivalCountPtr count_;
	public:
		CRevival();
		~CRevival();
		/*
		* @brief	読み込み
		* @param	revivalCount 復活可能回数
		*/
		bool Load(uint32_t revivalCount);
		/*
		* @brief	初期化
		*/
		void Initialize();

		void SubCount() noexcept;
		uint32_t GetCount() const noexcept;

	};

	using RevivalPtr = std::shared_ptr<CRevival>;
}


