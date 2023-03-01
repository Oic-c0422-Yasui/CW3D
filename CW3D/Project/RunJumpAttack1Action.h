#pragma once

#include	"BaseAction.h"


namespace ActionGame {

	/**
	 * @brief		�U���A�N�V����
	 */
	class CRunJumpAttack1Action : public CBaseAction
	{
	public:
		/**
		* @brief		�U���A�N�V�����̐ݒ�l
		*/
		struct Parameter
		{
			//�����l
			Vector3					velocity;
			float					jumpPower;
			float					gravity;
			float					defaultGravity;
		};
	private:
		//�p�����[�^�[
		Parameter					parameter_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CRunJumpAttack1Action(BaseParameter baseParam, Parameter param);
			

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
	using RunJumpAttack1ActionPtr = std::shared_ptr<CRunJumpAttack1Action>;
}
