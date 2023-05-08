#pragma once

#include	"IScene.h"
#include	"SceneChangeEffect.h"

namespace Scene
{
	/**
	 * @brief		シーン変更用インターフェイス
	 */
	class __declspec(novtable) ISceneChanger
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~ISceneChanger() = default;

		/**
		 * @brief		シーン変更
		 * @param		シーン番号
		 */
		virtual bool ChangeScene(SCENE_NO sceneNo) = 0;

		/**
		 * @brief		シーン変更
		 * @param		シーン番号
		 * @param		シーン遷移エフェクト
		 */
		virtual bool ChangeScene(SCENE_NO sceneNo,SceneChangeEffectPtr effect) = 0;

		/**
		 * @brief		シーン変更(ロード画面を挟む)
		 * @param		sceneNo シーン番号
		 * @param		シーン遷移エフェクト
		 * @param		isLoading ロード画面を挟むか？
		 */
		virtual bool ChangeScene(SCENE_NO sceneNo,SceneChangeEffectPtr effect,bool isLoading) = 0;
		
		/**
		 * @brief		シーン変更（読み込み、初期化は行わない）
		 * @param		scene ロード済みシーン
		 */
		virtual bool ChangeScene(const ScenePtr& scene, SceneChangeEffectPtr effect) = 0;

	};
	using SceneChangerPtr = std::shared_ptr<ISceneChanger>;
}


