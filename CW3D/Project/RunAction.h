#pragma once
#include "Action.h"


namespace ActionGame {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class RunAction : public Action
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
			Vector3					maxVelocity;

			float					maxGravity;
		};
	private:
		//�p�����[�^�[
		Parameter					m_Parameter;
		int m_NowDirection;
		enum tag_DIRECTION
		{
			DIRECTION_RIGHT,
			DIRECTION_RIGHTUP,
			DIRECTION_RIGHTDOWN,
			DIRECTION_LEFT,
			DIRECTION_LEFTUP,
			DIRECTION_LEFTDOWN,
		};
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RunAction(Parameter param);
			

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
	using RunActionPtr = std::shared_ptr<RunAction>;

}

