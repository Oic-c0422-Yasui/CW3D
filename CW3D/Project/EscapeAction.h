#pragma once

#include	"BaseAction.h"


namespace ActionGame {

	/**
	 * @brief		�U���A�N�V����
	 */
	class CEscapeAction : public CBaseAction
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
			Vector3					velocity;
		};
	private:
		//�p�����[�^�[
		Parameter					parameter_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CEscapeAction(BaseParameter baseParam, Parameter param);
			

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
		void Move(float x, float z);
		
		/*
		* @brief	����J�n
		*/
		void StartThrough();
		
		/*
		* @brief	����I��
		*/
		void EndThrough();

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override;
	};
	//�|�C���^�u������
	using EscapeActionPtr = std::shared_ptr<CEscapeAction>;
}
