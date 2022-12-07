#pragma once
#include "SceneCreator.h"
#include "GameDefine.h"

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
		 */
		virtual void RegistScene(tag_SCENENO sceneNo, SceneCreatorPtr creator) = 0;
	};
	using SceneRegisterPtr = std::shared_ptr<ISceneRegister>;
}
