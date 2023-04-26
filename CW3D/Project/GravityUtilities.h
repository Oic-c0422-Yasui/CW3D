#pragma once
#include "Velocity.h"
#include "GravityScale.h"

namespace MyUtil
{
	/*
	* @brief	�d�̓X�P�[����ݒ肷��
	* @param	velocity ���x�|�C���^
	* @param	gravity �d�̓X�P�[���p�����[�^
	*/
	void SetGravityScale(const ActionGame::VelocityPtr& velocity,
						ActionGame::GravityScaleParam gravity);
	/*
	* @brief	�d�̓X�P�[����ݒ肷��
	* @param	velocity ���x�|�C���^
	* @param	gravity �d�̓X�P�[���p�����[�^
	* @param	armor �A�[�}�[���x��
	* @param	armorBrake �A�[�}�[�j�󃌃x��
	*/
	void SetGravityScale(const ActionGame::VelocityPtr& velocity,
						ActionGame::GravityScaleParam gravity,
						BYTE armor,BYTE armorBrake);
}

