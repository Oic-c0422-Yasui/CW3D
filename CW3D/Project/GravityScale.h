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

