#pragma once
#include "SceneCreator.h"

namespace ActionGame
{
	/**
	 * @brief		シーン登録用共通インターフェイス
	 */
	class __declspec(novtable) ISceneRegister
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~ISceneRegister() = default;

		/**
		 * @brief		シーン登録
		 * @param		sceneNo	シーン番号
		 * @param		creator	シーン生成クラス
		 */
		virtual void RegistScene(tag_SCENENO sceneNo, SceneCreatorPtr creator) = 0;
	};
	using SceneRegisterPtr = std::shared_ptr<ISceneRegister>;
}
