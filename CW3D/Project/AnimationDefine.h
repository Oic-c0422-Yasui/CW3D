#pragma once

/* 
*	@brief	�A�j���[�V�����p�����[�^
* 
*	@param	name		�A�j���[�V�����̖��O
*
*	@param startTime	�A�j���[�V�����J�n����
*
*	@param speed		�A�j���[�V�������x
*
*	@param tTime		�A�j���[�V������Ԏ���
*
*	@param loopFlg		�A�j���[�V�������[�v�t���O
*/
struct AnimParam
{
	//���p����A�j���[�V�����̖��O
	char*					name;
	//�A�j���[�V�����J�n����
	float					startTime;
	//�A�j���[�V�������x
	float					speed;
	//�A�j���[�V������Ԏ���
	float					tTime;
	//�A�j���[�V�������[�v�t���O
	bool					loopFlg;
};