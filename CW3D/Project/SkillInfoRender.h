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
	 * @brief		�X�L������UI�\���ƃX�L���g�̍��W�����߂�
	 */
	class CSkillInfoRender
	{
	private:
		
		//�f�o�C�X�ɂ���ĉ摜��ς���
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
		/*		�v���C�x�[�g�֐�		*/

		void KeyBoardFrameSetting();
		void ControllerFrameSetting();

		void SetKeyBoardName();
		void SetControllerName();

	public:
		
		/**
		 * @brief		�R���X�g���N�^
		 */
		CSkillInfoRender();
		/**
		 * @brief		�f�X�g���N�^
		 */
		~CSkillInfoRender();

		/*
		* @brief	�ǂݍ���
		* @return	true�@�Ȃ琬��
		*/
		bool Load(GameDevice device);

		/**
		 * @brief		�`��
		 */
		void Render();

		/*
		* @brief		�f�o�b�O�`��
		*/
		void RenderDebug2D();

		/*
		* @brief		���
		*/
		void Release();

		/*
		* @brief	�L�[�{�[�h�z��̖��O�`��
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
