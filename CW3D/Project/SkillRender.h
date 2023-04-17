#pragma once

#include "Common.h"


namespace ActionGame
{
	/**
	 * @brief		�X�L��UI
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
		 * @brief		�R���X�g���N�^
		 */
		CSkillRender();
			

		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~CSkillRender();

		/*
		* @brief	�ǂݍ���
		* @param	skillName�@���\�[�X�}�l�[�W���[�ɓo�^����Ă���X�L���̖��O
		*/
		virtual bool Load(const std::string& skillName);

		/*
		* @brief	������
		* @param	pos�@UI�̍��W
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
		 * @brief		�`��
		 */
		virtual void Render();

		/*
		* @brief		�N�[���^�C�������`��
		*/
		void RenderCT(float ct);
		
		/*
		* @brief		���
		*/
		virtual void Release();
	};
	
	using SkillRenderPtr = std::shared_ptr<CSkillRender>;
	using SkillRenderArray = std::vector<SkillRenderPtr>;
}
