#pragma once
#include "GameDefine.h"
#include	"ParameterMap.h"
#include "ReactiveParameter.h"



namespace Sample {

	/**
	 * @brief		スキル生成
	 */
	class PlayerParameterCreator
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~PlayerParameterCreator() = default;

		/**
		 * @brief		生成
		 */
		bool Create(const AnyParameterMapPtr& param) {

			param->Add<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP, 800);
			param->Add<Sample::ReactiveParameter<int>>(PARAMETER_KEY_MAXHP, 800);
			param->Add<int>(PARAMETER_KEY_DAMAGE, 0);
			param->Add<int>(PARAMETER_KEY_ATTACK, 25);
			param->Add<float>(PARAMETER_KEY_INVINCIBLE, 0.0f);
			param->Add<Sample::ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE, 0);
			param->Add<Sample::ReactiveParameter<float>>(PARAMETER_KEY_MAXULTGAUGE, 100.0f);
			param->Add<bool>(PARAMETER_KEY_ESCAPE, false);

			return true;
		}
	};


}