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
	 * @brief		�X�L�������UI�\���ƃX�L���g�̍��W�����߂�
	 */
	class CSkillControllerRender
	{
	private:

		std::shared_ptr<CTexture>			frame_;
		std::shared_ptr<CFont>				font_;

		Vector2 position_;
		
		SkillFrame skillFrame_[SKILLMAX_COUNT];

		std::map<std::string, int> keyIndexs;

	private:
		/*		�v���C�x�[�g�֐�		*/

		void FrameSetting();

		void SetName();

	public:
		
		/**
		 * @brief		�R���X�g���N�^
		 */
		CSkillControllerRender();
		/**
		 * @brief		�f�X�g���N�^
		 */
		~CSkillControllerRender();

		bool Load();

		/**
		 * @brief		�`��
		 */
		void Render();

		void RenderDebug2D();

		void Release(void);

		const Vector2& GetPosition() noexcept
		{
			return position_;
		}
		const Vector2& GetSkillPosition(int id)
		{
			//�z�񐔂��id�̒l���傫���Ȃ�
			assert(SKILLMAX_COUNT <= id);
			return skillFrame_[id].position;
		}
		const Vector2& GetSkillPosition(const std::string& key)
		{
			return skillFrame_[keyIndexs[key]].position;
		}

		SkillFrame GetSkillFrame(int id)
		{
			//�z�񐔂��id�̒l���傫���Ȃ�
			assert(SKILLMAX_COUNT <= id);
			return skillFrame_[id];
		}

		void RenderKeyName();


	};

	using SkillControllerRenderPtr = std::shared_ptr<CSkillControllerRender>;
}
