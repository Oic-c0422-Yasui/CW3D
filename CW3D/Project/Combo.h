#pragma once
#include "ICombo.h"
#include "Timer.h"
#include "CharaTypeDefine.h"
#include "ReactiveParameter.h"

namespace ActionGame
{
	/*
	* @brief	コンボクラス
	*/
	class CCombo : public ICombo
	{
	private:
		CReactiveParameter<uint32_t> count_;
		float resetTime_;
		CTimer timer_;
	public:
		CCombo(float resetTime);

		/*
		* @brief	初期化
		*/
		void Initialize();
		/*
		* @brief	更新
		* @param	type　キャラのタイプ
		*/
		void Update(CHARA_TYPE type);

		/*
		* @brief	コンボ数取得
		*/
		uint32_t GetCount() const noexcept override;

		/*
		* @brief	コンボ数パラメータ取得
		*/
		CReactiveParameter<uint32_t>& GetCountParam() noexcept;

		/*
		* @brief	コンボ数追加
		*/
		void AddCount() noexcept override;
		
	};


}



