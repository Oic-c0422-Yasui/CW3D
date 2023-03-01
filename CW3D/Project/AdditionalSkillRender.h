#pragma once

#include "Common.h"
#include "ResourceManager.h"
#include "SkillRender.h"

namespace ActionGame
{
	/**
	 * @brief		�v���C���[CTUI
	 */
	class CAdditionalSkillRender : public CSkillRender
	{
	private:
		float addCT_;
		float addMaxCT_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CAdditionalSkillRender();
			

		/**
		 * @brief		�f�X�g���N�^
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
		 * @brief		�ǂݍ���
		 */
		bool Load(const std::string& key) override;
		
		/**
		 * @brief		������
		 */
		void Initialize(const Vector2& pos)  override;


		/**
		 * @brief		�`��
		 */
		void Render() override;

		void Release() override;
	};

	using AdditionalSkillRenderPtr = std::shared_ptr<CAdditionalSkillRender>;
}
