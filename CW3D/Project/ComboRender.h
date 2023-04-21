#pragma once

#include "Common.h"
#include "Quake.h"
#include "Fade.h"

namespace ActionGame
{
	/*
	* @brief　コンボ描画
	*/
	class CComboRender
	{
	private:
		uint32_t comboCount_;
		uint32_t prevComboCount_;

		Vector2 position_;

		#define COMBO_MAX 999

		std::shared_ptr<CFont> font_;

		CQuake quake_;
		CFade fade_;
		bool isFade_;
		bool isShow_;
		float showTime_;
		float showEndTime_;

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

		/*
		* @brief	コンボ表示時間設定
		*/
		void SetCurrentShowTime(float time) noexcept;

		void SetEndShowTime(float time) noexcept;
	};

	using ComboRenderPtr = std::shared_ptr<CComboRender>;
}


