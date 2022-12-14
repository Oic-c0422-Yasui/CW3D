#pragma once

/* 
*	@brief	アニメーションパラメータ
* 
*	@param	name		アニメーションの名前
*
*	@param startTime	アニメーション開始時間
*
*	@param speed		アニメーション速度
*
*	@param tTime		アニメーション補間時間
*
*	@param loopFlg		アニメーションループフラグ
*/
struct AnimParam
{
	//利用するアニメーションの名前
	char*					name;
	//アニメーション開始時間
	float					startTime;
	//アニメーション速度
	float					speed;
	//アニメーション補間時間
	float					tTime;
	//アニメーションループフラグ
	bool					loopFlg;
};