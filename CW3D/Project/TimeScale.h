#pragma once
#include "AnimationUtilities.h"



namespace ActionGame
{

	/*
	* @brief	�^�C���X�P�[���N���X
	*/
	class CTimeScale
	{
	private:
		float	timeScale_;
		MyUtil::ANIM_DATA_ARRAY animDataArray_;
		float	changeTime_;
		bool	isChange_;
		float	currentTime_;

	public:
		CTimeScale();
		~CTimeScale() {
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
			return timeScale_;
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