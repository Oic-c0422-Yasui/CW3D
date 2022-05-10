#pragma once
#include "Action.h"


namespace Sample {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class MoveAction : public Action
	{
	private:
		/** ���ړ��t���O */
		bool			m_XMoveFlg;
		/** �c�ړ��t���O */
		bool			m_ZMoveFlg;

		/** �ړ��� */
		CVector3 m_Move;

		/** ���]�t���O */
		bool			m_ReverseFlg;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		MoveAction()
			: Action()
			, m_XMoveFlg(false)
			, m_ZMoveFlg(false)
			, m_Move(0,0,0)
			, m_ReverseFlg(false) {
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {
		}

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		void Exection() override {
			//�ړ����Ȃ��ꍇ����
			if (!m_XMoveFlg)
			{
				DecelerateX(PLAYER_SPEED);
			}
			if (!m_ZMoveFlg)
			{
				DecelerateZ(PLAYER_SPEED);
			}
			//�d��
			Gravity(GRAVITY);
			//���ۂɍ��W���ړ�������
			Transform()->MovePosition(m_Move);
			//�ړ��t���OOFF
			m_XMoveFlg = false;
			m_ZMoveFlg = false;
		}

		/**
		 * @brief		�A�N�V�������̏I������
		 */
		void End() override {
		}

		/**
		 * @brief		���x���Z�b�g
		 */
		void Reset() {
			m_XMoveFlg = false;
			m_ZMoveFlg = false;
			m_Move = Vector3(0, 0, 0);
			m_ReverseFlg = false;
		}

		/**
		 * @brief		�d�͉���
		 * @param[in]	val		������
		 */
		void Gravity(float val) {
			m_Move.y += val;
			if (m_Move.y >= GRAVITYMAX)
			{
				m_Move.y = GRAVITYMAX;
			}
		}

		/**
		 * @brief		����
		 * @param[in]	val		������
		 * @param[in]	rev		���]�t���O
		 */
		void AccelerationX(float val, float maxspeed, bool reverse) {
			m_XMoveFlg  = true;
			m_Move.x += val;
			m_Move.x = ((m_Move.x > maxspeed) ? maxspeed : ((m_Move.x < -maxspeed) ? -maxspeed : m_Move.x));
			m_ReverseFlg = reverse;
		}

		/**
		 * @brief		����
		 * @param[in]	val		������
		 */
		void Acceleration(float x, float maxspeed) {
			m_ZMoveFlg = true;
			m_Move.z += x;
			m_Move.z = ((m_Move.z > maxspeed) ? maxspeed : ((m_Move.z < -maxspeed) ? -maxspeed : m_Move.z));
		}

		/**
		 * @brief		����
		 * @param[in]	dec		������
		 */
		void DecelerateX(float dec) {
			if (m_Move.x > 0)
			{
				m_Move.x -= dec;
				if (m_Move.x <= 0)
				{
					m_Move.x = 0;
				}
			}
			else if (m_Move.x < 0)
			{
				m_Move.x += dec;
				if (m_Move.x >= 0)
				{
					m_Move.x = 0;
				}
			}
		}

		/**
		 * @brief		����
		 * @param[in]	dec		������
		 */
		void DecelerateZ(float dec) {
			if (m_Move.z > 0)
			{
				m_Move.z -= dec;
				if (m_Move.z <= 0)
				{
					m_Move.z = 0;
				}
			}
			else if (m_Move.z < 0)
			{
				m_Move.z += dec;
				if (m_Move.z >= 0)
				{
					m_Move.z = 0;
				}
			}
		}

		/**
		 * @brief		���x�ݒ�
		 * @param[in]	val		���x
		 */
		void SetSpeed(float val) {
			m_Move.x = val;
			m_Move.z = val;
		}

		/**
		 * @brief		���x�ݒ�
		 * @param[in]	val		���x
		 */
		void SetSpeedX(float val) {
			m_Move.x = val;
		}

		/**
		 * @brief		���x�ݒ�
		 * @param[in]	val		���x
		 */
		void SetSpeedY(float val) {
			m_Move.y = val;
		}

		/**
		 * @brief		���x�ݒ�
		 * @param[in]	val		���x
		 */
		void SetSpeedZ(float val) {
			m_Move.y = val;
		}

		void SetReverseFlg(bool isReverse)
		{
			m_ReverseFlg = isReverse;
		}

		/**
		 * @brief		���x�擾
		 */
		float GetSpeedX() {
			return m_Move.x;
		}

		/**
		 * @brief		���x�擾
		 */
		float GetSpeedY() {
			return m_Move.y;
		}

		/**
		 * @brief		���x�擾
		 */
		 float GetSpeedZ() {
			return m_Move.z;
		}

		/**
		 * @brief		���]�t���O
		 */
		bool IsReverse() const {
			return m_ReverseFlg;
		}

		/**
		 * @brief		�ړ����f
		 *				���̈ړ����x�����ȉ��Ȃ��~�Ƃ݂Ȃ�
		 */
		bool IsMove() const {
			return std::abs(m_Move.x) > 0.01f;
		}

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_MOVE;
		}
	};
	//�|�C���^�u������
	using MoveActionPtr = std::shared_ptr<MoveAction>;

}

