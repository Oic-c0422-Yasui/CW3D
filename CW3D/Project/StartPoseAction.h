#pragma once
#include "BaseAction.h"

namespace ActionGame
{
	/**
	 * @brief		�J�n�|�[�Y�A�N�V����
	 */
	class CStartPoseAction : public CBaseAction
	{
	public:
		/**
		* @brief		�U���A�N�V�����̐ݒ�l
		*/
		struct Parameter
		{
			//�����l
			Vector3					decelerate;
			float					gravity;
			float					maxGravity;
		};
	private:
		//�p�����[�^�[
		Parameter					parameter_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CStartPoseAction(BaseParameter baseParam, Parameter param);


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
	using StartPoseActionPtr = std::shared_ptr<CStartPoseAction>;
	
}
