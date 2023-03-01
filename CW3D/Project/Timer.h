#pragma once
#include "Common.h"
#include "TimeScaleController.h"
#include "ReactiveParameter.h"
#include "ParameterHandle.h"
#include "Observer.h"

namespace ActionGame
{

	class CTimer
	{
	private:
		ActionGame::ParameterHandle< ActionGame::CReactiveParameter<float>>	currentTime_;
		float	m_TargetTime;
		bool	m_AchieveFlg;
		bool	isStop_;
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

		void Update(CHARA_TYPE timeScaleType);

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
			return isStop_;
		}

		/**
		 * @brief		���ݎ��Ԃ̃T�u�X�N���C�u
		 */
		ActionGame::IObservable<float>& GetTimeSubject()
		{
			return currentTime_.Get();
		}

		/**
		 * @brief		���ݎ��Ԏ擾
		 * @return		���ݎ���
		 */
		float GetTime() const noexcept
		{
			return currentTime_.Get();
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

