#pragma once

#include	"SceneBase.h"

namespace ActionGame
{
	/**
	 * @brief		シーン変更用共通インターフェイス
	 */
	class __declspec(novtable) ISceneChangeEffect
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~ISceneChangeEffect() = default;

		/**
		 * @brief		シーン変更効果更新
		 */
		virtual void Update() = 0;

		/**
		 * @brief		シーン変更効果描画
		 */
		virtual void Render(ScenePtr& prev,
						ScenePtr& current) = 0;

		/**
		 * @brief		シーン変更効果終了判定
		 */
		virtual bool IsEnd() const noexcept = 0;
	};
	using SceneChangeEffectPtr = std::shared_ptr<ISceneChangeEffect>;
}
