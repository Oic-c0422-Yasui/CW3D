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
		ParameterHandle< CReactiveParameter<float>>	currentTime_;
		float	targetTime_;
		bool	isAchieve_;
		bool	isStop_;
	public:
		CTimer();
		~CTimer();

		/**
		 * @brief		�^�C�}�[�J�n�i�ڕW���ԂȂ��j
		 */
		void Start();
		/**
		 * @brief		�^�C�}�[�J�n�i�ڕW���Ԃ���j
		 * @param		�ڕW����
		 */
		void Start(float targetTime);
		/*
		* @brief	�^�C�}�[��~
		*/
		void Stop();
		/*
		* @brief	�X�V
		*/
		void Update();
		/*
		* @brief	�L�����̃^�C���X�P�[���ɍ��킹���X�V
		* @param	�L�����̃^�C�v
		*/
		void Update(CHARA_TYPE timeScaleType);
		/*
		* @brief	���Z�b�g
		*/
		void Reset();

		/**
		 * @brief		�ڕW���Ԃ�B�����Ă��邩�H
		 * @return		�ڕW���ԒB������
		 */
		bool IsAchieve() const noexcept
		{
			return isAchieve_;
		}

		bool IsTimerStop() const noexcept
		{
			return isStop_;
		}

		/**
		 * @brief		���ݎ��Ԃ̃T�u�X�N���C�u
		 */
		IObservable<float>& GetTimeSubject()
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
			return targetTime_;
		}

		/**
		 * @brief		�ڕW���Ԑݒ�
		 * @param		�ڕW����
		 */
		void SetTargetTime(float time) noexcept
		{
			targetTime_ = time;
		}
	};

}

