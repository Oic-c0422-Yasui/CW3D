#pragma once

#include	"Action.h"


namespace ActionGame {

	/**
	 * @brief		�U���A�N�V����
	 */
	class Attack2Action : public Action
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
		};
	private:
		//�p�����[�^�[
		Parameter					m_Parameter;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Attack2Action(Parameter param);
			

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
	using Attack2ActionPtr = std::shared_ptr<Attack2Action>;
}
