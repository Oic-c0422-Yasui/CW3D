#pragma once
#include "BaseAction.h"


namespace ActionGame
{
    /**
     * @brief		�J�n�|�[�Y�A�N�V����
     */
    class CNPCStartPoseAction : public CBaseAction
    {
	public:
		/**
		* @brief		�U���A�N�V�����̐ݒ�l
		*/
		struct Parameter
		{
			//�I�t�Z�b�g�ʒu
			Vector3					offsetPos;
			//�I������
			float					finishTime;
		};
	private:
		//�p�����[�^�[
		Parameter					parameter_;

		Vector3						tmpOffsetPos_;

		float						currentTime_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CNPCStartPoseAction(BaseParameter baseParam, Parameter param);


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

		/*
		* @brief		�A�j���[�V�������I�����Ă��邩
		*/
		bool IsEndAnimation() const noexcept;
	};
	//�|�C���^�u������
    using NPCStartPoseActionPtr = std::shared_ptr<CNPCStartPoseAction>;
}


