#pragma once
#include "EnemyHPRender.h"
#include "ResourceManager.h"

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

		struct HPBarParam
		{
			const int Limit = 100;
			uint32_t Count;
			Vector2 CountPos;
			
			uint32_t CurrentColorId;
			uint32_t NextColorId;
		};
		HPBarParam HPBarParam_;

		MofU32 HPColors_[3];

	private:
		/* プライベート関数　*/
		//次の色を設定
		void SettingNextColor();
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CBossHPRender();

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

		/*
		* @brief	解放
		*/
		void Release();

    };
	using BossHPRenderPtr = std::shared_ptr<CBossHPRender>;
}


