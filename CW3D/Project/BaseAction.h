#pragma once
#include "Action.h"

namespace ActionGame
{

	/**
	 * @brief		�x�[�X�̃A�N�V����
	 */
	class CBaseAction : public CAction
	{
	public:
		/**
		 * @brief		�x�[�X�A�N�V�����̐ݒ�l
		 */
		struct BaseParameter
		{
			//�A�j���[�V�����p�����[�^�[
			AnimParam				anim;
		};
	protected:

		BaseParameter baseParam_;
	protected:
		/* �v���C�x�[�g�֐� */

		//���]�����ɉ�]������
		void SetRotation(float rotateTime = 0.18f);

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CBaseAction(BaseParameter baseParam);

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		virtual void Start() override;

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		virtual void Execution() override;

		/**
		 * @brief		�A�N�V�������̏I������
		 */
		virtual  void End() override;

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		virtual  const ActionKeyType GetKey() const override = 0;

		/*
		* @brief		�A�j���[�V�����̍Đ�
		*/
		void PlayAnimation();
		/*
		* @brief		�C�ӂ̃A�j���[�V�����̍Đ�
		* @param	name		�A�j���[�V������
		* @param	startTime	�J�n����
		* @param	speed		�A�j���[�V�������x
		* @param	tTime		��Ԏ���
		* @param	isLoop		���[�v���邩�H
		*/
		void PlayAnimation(char* name,float startTime,float speed,
							float tTime, bool isLoop);
	};

}

