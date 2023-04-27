#pragma once

namespace ActionGame
{
	/*
	* @brief	�d�̓X�P�[���p�����[�^
	* @param	isEnable	�L����
	* @param	time		�L������
	* @param	startScale	�J�n�d�̓X�P�[��
	* @param	endScale	�I���d�̓X�P�[��
	*/
	struct GravityScale
	{
		bool isEnable;
		float time;
		float startScale;
		float endScale;

		GravityScale()
		{
			isEnable = false;
			time = 0.0f;
			startScale = 0.0f;
			endScale = 0.0f;
		}
		GravityScale(bool enable,float t,float ss,float es)
		{
			isEnable = enable;
			time = t;
			startScale = ss;
			endScale = es;
		}
	};
}

