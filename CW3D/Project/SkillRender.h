#pragma once

#include "Common.h"


namespace ActionGame
{
	/**
	 * @brief		スキルUI
	 */
	class CSkillRender
	{
	protected:

		std::shared_ptr<CTexture>			sKillTexture_;
		std::shared_ptr<CTexture>			usedSKillTexture_;
		std::shared_ptr<CFont>				font_;

		float								CT_;
		float								maxCT_;
		bool								canUse_;

		Vector2								offset_;
		Vector2								size_;
		Vector2								position_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CSkillRender();
			

		/**
		 * @brief		デストラクタ
		 */
		virtual ~CSkillRender();

		/*
		* @brief	読み込み
		* @param	skillName　リソースマネージャーに登録されているスキルの名前
		*/
		virtual bool Load(const std::string& skillName);

		/*
		* @brief	初期化
		* @param	pos　UIの座標
		*/
		virtual void Initialize(const Vector2& pos);


		const Vector2& GetPosition()
		{
			return position_;
		}

		void SetCT(float  ct)
		{
			CT_ = ct;
		}

		void SetMaxCT(float ct)
		{
			maxCT_ = ct;
		}

		void SetCanUse(bool canUse)
		{
			canUse_ = canUse;
		}

		/**
		 * @brief		描画
		 */
		virtual void Render();

		/*
		* @brief		クールタイム文字描画
		*/
		void RenderCT(float ct);
		
		/*
		* @brief		解放
		*/
		virtual void Release();
	};
	
	using SkillRenderPtr = std::shared_ptr<CSkillRender>;
	using SkillRenderArray = std::vector<SkillRenderPtr>;
}
