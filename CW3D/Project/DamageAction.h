#pragma once
#include	"BaseAction.h"


namespace ActionGame {

	/**
	 * @brief		�_���[�W�A�N�V����
	 */
	class CDamageAction : public CBaseAction
	{
	public:
		/**
		* @brief		�U���A�N�V�����̐ݒ�l
		*/
		struct Parameter
		{
			//�����l
			Vector3					decelerate;
			//�d��
			float					gravity;
			//�ő�d��
			float					maxGravity;
		};
	private:
		//�p�����[�^�[
		Parameter					parameter_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CDamageAction(BaseParameter baseParam, Parameter param);
			

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
	using DamageActionPtr = std::shared_ptr<CDamageAction>;
}
