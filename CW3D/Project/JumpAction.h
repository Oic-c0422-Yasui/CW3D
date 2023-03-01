#pragma once
#include "BaseAction.h"


namespace ActionGame {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class CJumpAction : public CBaseAction
	{
	public:
		/**
		* @brief		�U���A�N�V�����̐ݒ�l
		*/
		struct Parameter
		{


			//�����l
			Vector3					velocity;
			Vector3					maxVelocity;

			float					gravity;
			float					maxGravity;
			float					jumpPower;
		};
	private:
		//�p�����[�^�[
		Parameter					parameter_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CJumpAction(BaseParameter baseParam, Parameter param);
			

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
	using JumpActionPtr = std::shared_ptr<CJumpAction>;
}

