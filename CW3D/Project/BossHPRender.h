#pragma once
#include "EnemyHPRender.h"
#include "ResourceManager.h"
#include "Quake.h"

namespace ActionGame
{
	/*
	* @brief	ボスHP描画
	*/
    class CBossHPRender : public CEnemyHPRender
    {
	private:

		std::shared_ptr<CTexture>			HPBar_;
		std::shared_ptr<CTexture>			HPFrame_;
		std::shared_ptr<CTexture>			damageBar_;

		Vector2 position_;
		Vector2 offset_;
		
		CQuake quake_;

		struct HPBarParam
		{
			const int LimitGauge = 500;
			const BYTE StartColor = 200;
			const BYTE EndColor = 100;
			uint32_t Count;
			uint32_t MaxCount;
			Vector2 CountPos;
		};
		HPBarParam HPBarParam_;

		int HPColor_;

	private:
		/* プライベート関数　*/
		//次の色を設定
		void SettingNextColor();
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CBossHPRender();

		~CBossHPRender() override;

		/*
		* @brief	読み込み
		* @return	true　なら成功
		*/
		bool Load();

		/*
		* @brief	初期化
		*/
		void Initialize() override;

		/**
		 * @brief		リセット
		 */
		void Reset() noexcept override;

		/**
		 * @brief		描画
		 */
		void Render() override;

		void SetHP(int hp) override;

		/*
		* @brief	解放
		*/
		void Release();

		

    };
	using BossHPRenderPtr = std::shared_ptr<CBossHPRender>;
}


