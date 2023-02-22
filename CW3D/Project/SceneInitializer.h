#pragma once
#include "IScene.h"
#include "SceneChangeEffect.h"

namespace Scene
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
		virtual void InitializeScene(SceneChangeEffectPtr effect) = 0;


	};
	using SceneInitializerPtr = std::shared_ptr<ISceneInitializer>;
}
