#pragma once

#include	"Action.h"


namespace ActionGame {

	/**
	 * @brief		�U���A�N�V����
	 */
	class JumpBeamSkillAction : public CAction
	{
	public:
		/**
				 * @brief		�U���A�N�V�����̐ݒ�l
				 */
		struct Parameter
		{
			//�A�j���[�V�����p�����[�^�[
			AnimParam				anim;
			//�����l
			Vector3					decelerate;
		};
	private:
		//�p�����[�^�[
		Parameter					m_Parameter;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		JumpBeamSkillAction(Parameter param);
			

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

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override;
	};
	//�|�C���^�u������
	using JumpBeamSkillActionPtr = std::shared_ptr<JumpBeamSkillAction>;
}
