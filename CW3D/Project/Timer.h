#pragma once
#include "Common.h"
#include "TimeScaleController.h"

namespace Sample
{

	class CTimer
	{
	private:
		float	m_CurrentTime;
		float	m_TargetTime;
		bool	m_AchieveFlg;
		bool	m_StopFlg;
	public:
		CTimer();
		~CTimer();

		/**
		 * @brief		�^�C�}�[�J�n
		 */
		void Start();
		/**
		 * @brief		�^�C�}�[�J�n
		 * @param		�ڕW����
		 */
		void Start(float targetTime);



		void Stop();

		void Update();

		void Update(CHARACTER_TYPE timeScaleType);

		/**
		 * @brief		�ڕW���Ԃ�B�����Ă��邩�H
		 * @return		�ڕW���ԒB������
		 */
		bool IsAchieve() const noexcept
		{
			return m_AchieveFlg;
		}

		bool IsTimerStop() const noexcept
		{
			return m_StopFlg;
		}

		/**
		 * @brief		���ݎ��Ԏ擾
		 * @return		���ݎ���
		 */
		float GetTime() const noexcept
		{
			return m_CurrentTime;
		}

		/**
		 * @brief		�ڕW���Ԏ擾
		 * @return		�ڕW����
		 */
		float GetTargetTime() const noexcept
		{
			return m_TargetTime;
		}

		/**
		 * @brief		�ڕW���Ԑݒ�
		 * @param		�ڕW����
		 */
		void SetTargetTime(float time) noexcept
		{
			m_TargetTime = time;
		}
	};

}

