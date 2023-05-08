#pragma once
#include "ISceneManager.h"
#include "SceneCreator.h"
#include <unordered_map>
#include "ThreadCreator.h"
#include "TaskManager.h"

namespace Scene
{
	/**
	 * シーンマネージャー
	 */
	class CSceneManager : public ISceneManager
	{
	private:
		//現在のシーン
		ScenePtr currentScene_;
		//遷移前のシーン
		ScenePtr prevScene_;
		//登録されているシーン
		std::unordered_map<SCENE_NO, SceneCreatorPtr> sceneMap_;
		
		//更新タスク
		Task::CTaskManager updateTask_;
		//描画タスク
		Task::CTaskManager renderTask_;
		//２D描画タスク
		Task::CTaskManager render2DTask_;

		//遷移エフェクト
		SceneChangeEffectPtr changeEffect_;

		//デバッグフラグ
		bool isDebug_;

		//現在のシーン初期化フラグ
		bool isSceneInit_;

	private:
		/* プライベート関数 */
		
		//タスク登録
		void RegisterTask();
		//更新タスク登録
		void RegisterUpdateTask();
		//描画タスク登録
		void RegisterRenderTask();
		void RegisterRender2DTask();
		//タスク削除
		void DeleteTask();
		//デバッグタスク登録
		void RegisterDebugTask();
		//デバッグタスク削除
		void DeleteDebugTask();
		//遷移エフェクトタスク登録
		void RegisterSceneChangeEffectTask();
		//遷移エフェクトタスク削除
		void DeleteSceneChangeEffectTask();
	public:
		CSceneManager();
		~CSceneManager();

		/*
		 * @brief		シーンの登録
		 * @param		sceneNo	シーン番号
		 * @param		creator	シーン生成クラス
		 */
		void RegistScene(SCENE_NO sceneNo, SceneCreatorPtr creator) override;

		/*
		 * @brief		シーンの登録
		 * @param		sceneNo	シーン番号
		 */
		template < class T >
		void RegistScene(SCENE_NO sceneNo) 
		{
			RegistScene(sceneNo, std::make_unique<SceneCreator<T>>());
		}


		/*
		 * @brief		シーンの変更
		 * @param		sceneNo	シーン番号
		 */
		bool ChangeScene(SCENE_NO sceneNo) override;

		/*
		 * @brief		シーンの変更
		 * @param		sceneNo	シーン番号
		 * @param		sceneNo	シーン遷移エフェクト
		 */
		bool ChangeScene(SCENE_NO sceneNo, SceneChangeEffectPtr effect) override;

		/**
		 * @brief		シーン変更(ロード画面を挟む)
		 * @param		sceneNo シーン番号
		 * @param		sceneNo	シーン遷移エフェクト
		 * @param		isLoading ロード画面を挟むか？
		 */
		bool ChangeScene(SCENE_NO sceneNo, SceneChangeEffectPtr effect, bool isLoading) override;
		/*
		 * @brief		シーンの変更（ロード、初期化は行わない）
		 * @param		scene	ロード済みのシーン
		 */
		bool ChangeScene(const ScenePtr& scene, SceneChangeEffectPtr effect) override;
		

		/*
		* @brief		現在のシーンを初期化
		* @param		effect	シーン変更中のエフェクト
		*/
		void InitializeScene(SceneChangeEffectPtr effect) override;

		/*
		* @brief　読み込み
		*/
		bool Load() override;
		/*
		* @brief　初期化
		*/
		void Initialize() override;
		/*
		* @brief　更新
		*/
		void Update() override;
		/*
		* @brief　描画
		*/
		void Render() override;
		/*
		* @brief　解放
		*/
		void Release() override;

	};

}


