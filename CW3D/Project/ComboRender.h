#pragma once

#include "Common.h"

namespace ActionGame
{
	/*
	* @brief　コンボ描画
	*/
	class CComboRender
	{
	private:
		uint32_t comboCount_;

		Vector2 position_;

		#define COMBO_MAX 999

		std::shared_ptr<CFont> font_;
	public:
		CComboRender();
		~CComboRender();
		
		/*
		* @brief	読み込み
		* @return	true　なら成功
		*/
		bool Load();
		/*
		* @brief	初期化
		*/
		void Initialize();
		/*
		* @brief	描画
		*/
		void Render();
		/*
		* @brief	解放
		*/
		void Release();
		/*
		* @brief	コンボ数設定
		*/
		void SetComboCount(uint32_t count) noexcept;
	};

	using ComboRenderPtr = std::shared_ptr<CComboRender>;
}


