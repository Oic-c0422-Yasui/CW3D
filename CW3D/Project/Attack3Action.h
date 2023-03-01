#pragma once

#include	"BaseAction.h"


namespace ActionGame {

	/**
	 * @brief		�U���A�N�V����
	 */
	class CAttack3Action : public CBaseAction
	{
	public:
		/**
		 * @brief		�U���A�N�V�����̐ݒ�l
		 */
		struct Parameter
		{
			//�����l
			Vector3					decelerate;
			//�����l
			Vector3					firstVelocity;
			//�����l
			Vector3					secondVelocity;
		};
	private:
		//�p�����[�^�[
		Parameter					parameter_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CAttack3Action(BaseParameter baseParam, Parameter param);
			

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
	using Attack3ActionPtr = std::shared_ptr<CAttack3Action>;
}
