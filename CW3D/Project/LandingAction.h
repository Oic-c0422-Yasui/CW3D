#pragma once
#include "BaseAction.h"


namespace ActionGame {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class CLandingAction : public CBaseAction
	{
	public:
		/**
		* @brief		�U���A�N�V�����̐ݒ�l
		*/
		struct Parameter
		{
		};
	private:
		//�p�����[�^�[
		Parameter					parameter_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CLandingAction(BaseParameter baseParam, Parameter param);
			

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
	using LandingActionPtr = std::shared_ptr<CLandingAction>;
}

