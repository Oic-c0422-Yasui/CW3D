#pragma once
#include "ISceneManager.h"
#include "SceneCreator.h"
#include <unordered_map>
#include "ThreadCreator.h"
#include "TaskManager.h"

namespace ActionGame
{
	/**
	 * シーンマネージャー
	 */
	class SceneManager : public ISceneManager
	{
	private:

		ScenePtr m_Scene;

		std::unordered_map<tag_SCENENO, SceneCreatorPtr> m_SceneMap;

		TaskManager m_UpdateTask;

		bool m_DebugFlg;

	private:
		/* //プライベート関数 */
		
		//タスク登録
		void RegisterTask();
		//更新タスク登録
		void RegisterUpdateTask();
		//デバッグタスク登録
		void RegisterDebugTask();
		//デバッグタスク削除
		void DeleteDebugTask();

	public:
		SceneManager();
		~SceneManager();

		/*
		 * @brief		シーンの登録
		 */
		void RegistScene(tag_SCENENO sceneNo, SceneCreatorPtr creator) override;

		/*
		 * @brief		シーンの登録
		 */
		template < class T >
		void RegistScene(tag_SCENENO sceneNo) 
		{
			RegistScene(sceneNo, std::make_unique<SceneCreator<T>>());
		}


		/*
		 * @brief		シーンの変更
		 */
		bool ChangeScene(tag_SCENENO sceneNo) override;
		/**
		 * @brief		シーン変更(ロード画面を挟む)
		 * @param		sceneNo シーン番号
		 * @param		isLoading ロード画面を挟むか？
		 */
		bool ChangeScene(tag_SCENENO sceneNo,bool isLoading) override;
		/*
		 * @brief		シーンの変更
		 */
		bool ChangeScene(const ScenePtr& scene) override;
		

		/*
		* @brief		現在のシーンを初期化
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


