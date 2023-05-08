#pragma once

#include "Common.h"

namespace MyUtil
{
	/*
	* @brief	���Ԃ��Ƃ̒l��Ԃ�
	* @return	���ݎ��Ԃ̂ł̒l
	*/
	float Timer(float startValue, float currentTime, float endValue, float endTime);
	/*
	* @brief	���Ԃ��Ƃ̒l��Ԃ�
	* @return	���ݎ��Ԃ̂ł̒l
	*/
	Vector3 Timer(const Vector3& startValue, float currentTime, const Vector3& endValue, float endTime);

	/*
	* @brief	���Ԃ��Ƃ̒l��Ԃ�(��]�p)
	* @return	���ݎ��Ԃł̉�]�l
	*/
	float RotateTimer(float startValue, float currentTime, float endValue, float endTime);

	//�C�[�W���O�̎��
	enum class EASING_TYPE {
		LINER,
		IN_SINE,
		OUT_SINE,
		INOUT_SINE,
	};

	//�A�j���[�V�����p�\����
	typedef struct tag_ANIM_DATA
	{
		float	Time;
		float	Value;
		EASING_TYPE EasingType;
	}ANIM_DATA;
	using ANIM_DATA_ARRAY = std::vector< ANIM_DATA>;

	// �A�j���[�V�����p�\����
	typedef struct tag_ANIM_V3_DATA
	{
		float	Time;
		Vector3	Value;
		EASING_TYPE EasingType;

	}ANIM_V3_DATA;
	using ANIM_V3_DATA_ARRAY = std::vector< ANIM_V3_DATA>;


	/*
	* @brief	��ԃA�j���[�V����
	* @param	animTime	���݂̃A�j���[�V��������
	* @param	animData	�A�j���[�V�����\����
	*/
	float InterpolationAnim(float animTime, const ANIM_DATA_ARRAY& animData);

	/*
	* @brief	��ԃA�j���[�V����
	* @param	animTime	���݂̃A�j���[�V��������
	* @param	animData	�A�j���[�V�����\����
	* @param	count		�A�j���[�V������
	*/
	float InterpolationAnim(float animTime, ANIM_DATA* animData, int count);

	/*
	* @brief	��ԃA�j���[�V����
	* @param	animTime	���݂̃A�j���[�V��������
	* @param	animData	�A�j���[�V�����\����
	* @param	count		�A�j���[�V������
	*/
	Vector3 InterpolationAnim(float animTime, ANIM_V3_DATA* animData, int count);

	/*
	* @brief	��ԃA�j���[�V����
	* @param	animTime	���݂̃A�j���[�V��������
	* @param	animData	�A�j���[�V�����\����
	*/
	Vector3 InterpolationAnim(float animTime, const ANIM_V3_DATA_ARRAY& animData);



	void RenderMousePos(Vector2& pos);
}

