#pragma once

#include	"Action.h"


namespace ActionGame {

	/**
	 * @brief		�U���A�N�V����
	 */
	class DropKickSkillAction : public Action
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

			float					gravity;
			float					maxGravity;
			float					jumpPower;
		};
	private:
		//�p�����[�^�[
		Parameter					m_Parameter;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		DropKickSkillAction(Parameter param);
			

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override;

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		void Execution() override;

		/**
		 * @brief		����
		 * @param[in]	x		������
		 */
		void Move(float x);

		/**
		 * @brief		�A�N�V�������̏I������
		 */
		void End() override;

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override ;
	};
	//�|�C���^�u������
	using DropKickSkillActionPtr = std::shared_ptr<DropKickSkillAction>;
}
