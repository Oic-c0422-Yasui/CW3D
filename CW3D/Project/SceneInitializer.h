#pragma once
#include "SceneBase.h"
#include "SceneChangeEffect.h"

namespace ActionGame
{
	/**
	 * @brief		シーン初期化用インターフェイス
	 */
	class __declspec(novtable) ISceneInitializer
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~ISceneInitializer() = default;

		/**
		 * @brief		現在のシーンを初期化する
		 */
		virtual bool InitializeScene(SceneChangeEffectPtr effect) = 0;


	};
	using SceneInitializerPtr = std::shared_ptr<ISceneInitializer>;
}
