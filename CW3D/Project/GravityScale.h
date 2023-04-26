#pragma once

namespace ActionGame
{
	/*
	* @brief	重力スケールパラメータ
	* @param	isEnable	有効化
	* @param	time		有効時間
	* @param	startScale	開始重力スケール
	* @param	endScale	終了重力スケール
	*/
	struct GravityScaleParam
	{
		bool isEnable;
		float time;
		float startScale;
		float endScale;
	};
}

