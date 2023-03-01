#pragma once
#include	"BaseAction.h"


namespace ActionGame {

	/**
	 * @brief		�_���[�W�A�N�V����
	 */
	class CDownAction : public CBaseAction
	{
	public:
		/**
		 * @brief		�U���A�N�V�����̐ݒ�l
		 */
		struct Parameter
		{

			//�����l
			Vector3					decelerate;
		};
	private:
		//�p�����[�^�[
		Parameter					parameter_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CDownAction(BaseParameter baseParam, Parameter param);
			

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
	using DownActionPtr = std::shared_ptr<CDownAction>;
}
