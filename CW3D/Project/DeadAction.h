#pragma once
#include	"Action.h"


namespace ActionGame {

	/**
	 * @brief		�_���[�W�A�N�V����
	 */
	class DeadAction : public CAction
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
			//�I������
			float					finishTime;
		};
	private:
		//�p�����[�^�[
		Parameter					m_Parameter;

		//���ݎ���
		float						m_CurrentTime;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		DeadAction(Parameter param);
			

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
	using DeadActionPtr = std::shared_ptr<DeadAction>;
}
