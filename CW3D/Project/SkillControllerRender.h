#pragma once

#include "Common.h"
#include "SkillDefine.h"

#include "ResourceManager.h"

namespace ActionGame
{
	struct SkillFrame
	{
		Vector2 position;
		float   size;
		CRectangle rect;
		char* str;
	};
	/**
	 * @brief		スキル操作のUI表示とスキル枠の座標を決める
	 */
	class CSkillControllerRender
	{
	private:

		std::shared_ptr<CTexture>			m_pFrame;
		std::shared_ptr<CTexture>			m_pSkill;
		std::shared_ptr<CFont>				m_pFont;

		Vector2 m_Position;
		
		SkillFrame m_SkillFrame[SKILLMAX_COUNT];

		std::map<std::string, int> keyIndexs;

	private:
		/*		プライベート関数		*/

		void FrameSetting();

		void SetName();

	public:
		
		/**
		 * @brief		コンストラクタ
		 */
		CSkillControllerRender();
		/**
		 * @brief		デストラクタ
		 */
		~CSkillControllerRender();

		bool Load();

		/**
		 * @brief		描画
		 */
		void Render();

		void RenderDebug2D();

		void Release(void);

		const Vector2& GetPosition() noexcept
		{
			return m_Position;
		}
		const Vector2& GetSkillPosition(int id)
		{
			//配列数よりidの値が大きいなら
			assert(SKILLMAX_COUNT <= id);
			return m_SkillFrame[id].position;
		}
		const Vector2& GetSkillPosition(const std::string& key)
		{
			return m_SkillFrame[keyIndexs[key]].position;
		}

		SkillFrame GetSkillFrame(int id)
		{
			//配列数よりidの値が大きいなら
			assert(SKILLMAX_COUNT <= id);
			return m_SkillFrame[id];
		}

		void RenderKeyName();


	};

	using SkillControllerRenderPtr = std::shared_ptr<CSkillControllerRender>;
}
