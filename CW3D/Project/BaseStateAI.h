#pragma once
#include "StateAI.h"


namespace ActionGame
{

    class CBaseStateAI : public CStateAI
    {
    protected:
		/*
		* @brief	�͈͓��ɂ��邩
		*/
		bool IsInRange(const Vector3& size, const CAABB& target);
		/*
		* @brief	�͈͓��ɂ��邩
		*/
		bool IsInRange(float distance, const Vector3& target);

		/*
		* @brief	�ړ�����
		*/
		void InputMove(float distance,const Vector3& target);

		float GetDistance(const Vector3& target);

    public:
        CBaseStateAI();

		/**
		 * @brief		���p�L�[�̓o�^
		 */
		virtual void RegisterKey() override = 0;

		/**
		 * @brief		�J�n
		 */
		virtual void Start() override = 0;

		/**
		 * @brief		�X�V
		 */
		virtual void Update() override = 0;

		/**
		 * @brief		�I��
		 */
		virtual void End() override = 0;
    };
}
