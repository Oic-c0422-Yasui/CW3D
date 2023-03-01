#pragma once
#include "BaseAction.h"


namespace ActionGame {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class IdleMotionAction : public CBaseAction
	{
	public:
		/**
		* @brief		�U���A�N�V�����̐ݒ�l
		*/
		struct Parameter
		{

			//�����l
			Vector3					velocity;
		};
	private:
		//�p�����[�^�[
		Parameter					parameter_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		IdleMotionAction(BaseParameter baseParam, Parameter param);
			

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
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override;

	};
	//�|�C���^�u������
	using IdleMotionActionPtr = std::shared_ptr<IdleMotionAction>;

}
