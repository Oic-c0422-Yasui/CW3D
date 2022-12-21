#pragma once

#include "Common.h"

namespace MyUtilities
{

	//���Ԃ��Ƃ̒l��Ԃ�
	//�߂�l:���ݎ��Ԃł̒l
	float Timer(float startValue, float currentTime, float endValue, float endTime);

	//���Ԃ��Ƃ̒l��Ԃ�(��]�p)
	//�߂�l:���ݎ��Ԃł̉�]�l
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

	/*
	* @brief		UTF-8��ShiftJIS�ɕϊ�
	* @param[in]	utf8�̕���
	* @return		shiftJIS�ɕϊ����ꂽ����
	*/
	std::string UTF8toShiftJIS(const std::string& utf8);
}


