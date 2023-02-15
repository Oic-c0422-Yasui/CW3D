#pragma once

#include	"Action.h"

namespace ActionGame {

	/**
	 * @brief		�N���A�|�[�Y�A�N�V����
	 */
	class ClearPoseAction : public CAction
	{
	public:
		/**
		* @brief		�U���A�N�V�����̐ݒ�l
		*/
		struct Parameter
		{
			//�A�j���[�V�����p�����[�^�[
			AnimParam				anim;
			AnimParam				fallAnim;
			//�����l
			Vector3					decelerate;
			float					gravity;
			float					maxGravity;
		};
	private:
		//�p�����[�^�[
		Parameter					m_Parameter;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		ClearPoseAction(Parameter param);
			

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override;

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		void Execution() override;

		/**
		 * @brief		�A�N�V�������̏I������
		 */
		void End() override;

		/*
		* @brief		�A�j���[�V�����J�n
		*/
		void StartAnim();

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override;
	};
	//�|�C���^�u������
	using ClearPoseActionPtr = std::shared_ptr<ClearPoseAction>;
}
