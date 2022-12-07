#pragma once

#include	"SceneBase.h"
#include "GameDefine.h"

namespace ActionGame
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
		 */
		virtual bool ChangeScene(tag_SCENENO sceneNo) = 0;


		/**
		 * @brief		シーン変更(ロード画面を挟む)
		 * @param		sceneNo シーン番号
		 * @param		isLoading ロード画面を挟むか？
		 */
		virtual bool ChangeScene(tag_SCENENO sceneNo,bool isLoading) = 0;
		
		/**
		 * @brief		シーン変更
		 */
		virtual bool ChangeScene(const ScenePtr& scene) = 0;

	};
	using SceneChangerPtr = std::shared_ptr<ISceneChanger>;
}


