#pragma once

#include "Common.h"
#include "SkillDefine.h"
#include "DeviceDefine.h"

namespace ActionGame
{
	struct SkillFrame
	{
		Vector2		position;
		float		size;
		CRectangle	rect;
		char*		str;
	};
	/**
	 * @brief		スキル情報のUI表示とスキル枠の座標を決める
	 */
	class CSkillInfoRender
	{
	private:
		
		//デバイスによって画像を変える
		enum OperateDevice
		{
			Device_Keyboard,
			Device_Controller,

			Device_Count,
		};
		OperateDevice currentDevice_;

		std::shared_ptr<CTexture>			uiFrame_[Device_Count];

		std::shared_ptr<CFont>				font_;
		std::shared_ptr<CFont>				padButtonFont_;

		Vector2 position_;
		
		SkillFrame skillFrame_[Device_Count][SKILLMAX_COUNT];


		std::map<std::string, int> keyIndexs_[Device_Count];

	private:
		/*		プライベート関数		*/

		void KeyBoardFrameSetting();
		void ControllerFrameSetting();

		void SetKeyBoardName();
		void SetControllerName();

	public:
		
		/**
		 * @brief		コンストラクタ
		 */
		CSkillInfoRender();
		/**
		 * @brief		デストラクタ
		 */
		~CSkillInfoRender();

		/*
		* @brief	読み込み
		* @return	true　なら成功
		*/
		bool Load(GameDevice device);

		/**
		 * @brief		描画
		 */
		void Render();

		/*
		* @brief		デバッグ描画
		*/
		void RenderDebug2D();

		/*
		* @brief		解放
		*/
		void Release();

		/*
		* @brief	キーボード配列の名前描画
		*/
		void RenderKeyName();

		const Vector2& GetPosition() noexcept
		{
			return position_;
		}
		const Vector2& GetKeyBoardSkillPosition(const std::string& key)
		{
			return skillFrame_[Device_Keyboard][keyIndexs_[Device_Keyboard][key]].position;
		}
		const Vector2& GetControllerSkillPosition(const std::string& key)
		{
			return skillFrame_[Device_Controller][keyIndexs_[Device_Controller][key]].position;
		}

		void ChangeKeyBoardTexture();

		void ChangeControllerTexture();



	};

	using SkillInfoRenderPtr = std::shared_ptr<CSkillInfoRender>;
}
