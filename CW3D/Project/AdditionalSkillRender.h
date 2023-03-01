#pragma once

#include "Common.h"
#include "ResourceManager.h"
#include "SkillRender.h"

namespace ActionGame
{
	/**
	 * @brief		プレイヤーCTUI
	 */
	class CAdditionalSkillRender : public CSkillRender
	{
	private:
		float addCT_;
		float addMaxCT_;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CAdditionalSkillRender();
			

		/**
		 * @brief		デストラクタ
		 */
		~CAdditionalSkillRender();

		void SetAddCT(float ct)
		{
			addCT_ = ct;
		}

		void SetAddMaxCT(float ct)
		{
			addMaxCT_ = ct;
		}

		/**
		 * @brief		読み込み
		 */
		bool Load(const std::string& key) override;
		
		/**
		 * @brief		初期化
		 */
		void Initialize(const Vector2& pos)  override;


		/**
		 * @brief		描画
		 */
		void Render() override;

		void Release() override;
	};

	using AdditionalSkillRenderPtr = std::shared_ptr<CAdditionalSkillRender>;
}
