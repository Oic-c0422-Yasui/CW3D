#pragma once

#include	"BaseAction.h"


namespace ActionGame {

	/**
	 * @brief		�U���A�N�V����
	 */
	class CRunJumpAttack3Action : public CBaseAction
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
		CRunJumpAttack3Action(BaseParameter baseParam, Parameter param);
			

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
		* @brief	�W�����v
		*/
		void Jump();

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override;
	};
	//�|�C���^�u������
	using RunJumpAttack3ActionPtr = std::shared_ptr<CRunJumpAttack3Action>;
}
