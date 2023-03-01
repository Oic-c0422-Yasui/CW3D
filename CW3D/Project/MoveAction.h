#pragma once
#include "BaseAction.h"


namespace ActionGame {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class CMoveAction : public CBaseAction
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
			Vector3					maxVelocity;
			float					gravity;
			float					maxGravity;
		};
	protected:
		//�p�����[�^�[
		Parameter					parameter_;
		enum class DIRECTION
		{
			RIGHT,
			RIGHT_UP,
			RIGHT_DOWN,
			LEFT,
			LEFT_UP,
			LEFT_DOWN,
		};
		DIRECTION currentDirection_;

		//����������
		void InitDirection();
		//�A�N�^�[�̌�����ύX����
		void ChangeDirection();

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CMoveAction(BaseParameter baseParam, Parameter param);
			

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		virtual void Start() override;

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		virtual void Execution() override;

		/**
		 * @brief		�A�N�V�������̏I������
		 */
		virtual void End() override;

		/**
		 * @brief		����
		 * @param[in]	x		������
		 * @param[in]	z		������
		 */
		void Acceleration(float x, float z);

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		virtual const ActionKeyType GetKey() const override;
	};
	//�|�C���^�u������
	using MoveActionPtr = std::shared_ptr<CMoveAction>;

}

