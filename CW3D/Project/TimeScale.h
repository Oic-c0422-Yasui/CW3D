#pragma once
#include "Utilities.h"



namespace ActionGame
{

	/*
	* @brief	�^�C���X�P�[���N���X
	*/
	class TimeScale
	{
	private:
		float	time_;
		MyUtil::ANIM_DATA_ARRAY m_AnimDataArray;
		float	m_ChangeTime;
		bool	m_ChangeFlg;
		float	currentTime_;
		int		m_Count;

	public:
		TimeScale();
		~TimeScale() {
		}
		/*
		* @brief	�X�V
		*/
		void Update();
		/*
		* @brief	�^�C���X�P�[���擾
		* @return	�^�C���X�P�[��
		*/
		float GetScale() const noexcept
		{
			return time_;
		}
		/*
		* @brief	�^�C���X�P�[���ݒ�
		* @param	scale		�^�C���X�P�[��
		* @param	changeTime	�ω��ɂ����鎞��
		* @param	easeType	�C�[�W���O�^�C�v
		*/
		void SetScale(float scale, float changeTime, MyUtil::EASING_TYPE easeType) noexcept;


		void SetScale(const MyUtil::ANIM_DATA_ARRAY& anim);

		void Reset() noexcept;

	};
}