#pragma once

#include	"Action.h"


namespace ActionGame {

	/**
	 * @brief		�U���A�N�V����
	 */
	class Attack3Action : public CAction
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
			//�����l
			Vector3					velocity;
			//�����l
			Vector3					velocity2;
		};
	private:
		//�p�����[�^�[
		Parameter					m_Parameter;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Attack3Action(Parameter param);
			

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
	using Attack3ActionPtr = std::shared_ptr<Attack3Action>;
}
