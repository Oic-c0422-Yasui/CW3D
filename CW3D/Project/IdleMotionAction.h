#pragma once
#include "Action.h"


namespace ActionGame {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class IdleMotionAction : public CAction
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
			Vector3					velocity;
		};
	private:
		//�p�����[�^�[
		Parameter					m_Parameter;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		IdleMotionAction(Parameter param);
			

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
		 * @brief		����
		 * @param[in]	x		������
		 * @param[in]	z		������
		 */
		void Acceleration(float x, float z);

		/**
		 * @brief		���x���Z�b�g
		 */
		void Reset();



		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override;

	};
	//�|�C���^�u������
	using IdleMotionActionPtr = std::shared_ptr<IdleMotionAction>;

}
