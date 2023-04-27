#pragma once
#include "Velocity.h"
#include "GravityScale.h"

namespace MyUtil
{
	/*
	* @brief	重力スケールを設定する
	* @param	velocity 速度ポインタ
	* @param	gravity 重力スケールパラメータ
	*/
	void SetGravityScale(const ActionGame::VelocityPtr& velocity,
						ActionGame::GravityScale gravity);
	/*
	* @brief	重力スケールを設定する
	* @param	velocity 速度ポインタ
	* @param	gravity 重力スケールパラメータ
	* @param	armor アーマーレベル
	* @param	armorBrake アーマー破壊レベル
	*/
	void SetGravityScale(const ActionGame::VelocityPtr& velocity,
						ActionGame::GravityScale gravity,
						BYTE armor,BYTE armorBrake);
}

