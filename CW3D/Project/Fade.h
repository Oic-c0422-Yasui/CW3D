#pragma once
#include "Common.h"
#include "AnimationUtilities.h"
#include "Timer.h"

namespace ActionGame
{
	class CFade
	{
	private:

		BYTE currentValue_;
		BYTE endValue_;
		BYTE startValue_;
		bool isStart_;
		float endTime_;
		CTimer timer_;

	public:
		CFade();
		~CFade();

		/*
		* @brief	������
		* @param	startValue�@�J�n�A���t�@�l
		* @param	endTime		�I������
		* @param	endValue	�I���A���t�@�l
		*/
		void Initialize(BYTE startValue,float endTime, BYTE endValue);
		/*
		* @brief	�t�F�[�h�J�n
		*/
		void Start();
		/*
		* @brief	�X�V
		*/
		void Update();
		/*
		* @brief	���Z�b�g
		*/
		void Reset();
		/*
		* @brief	���݂̃t�F�[�h�l�擾
		*/
		BYTE GetFadeValue() const noexcept;
		/*
		* @brief	�t�F�[�h���I�����Ă��邩�H
		*/
		bool IsEnd() const noexcept;
	};
	
}


