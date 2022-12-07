#pragma once
#include	"SceneRegister.h"
#include	"SceneChanger.h"
#include	"SceneInitializer.h"


namespace ActionGame
{

	class  ISceneManager : public ISceneChanger, public ISceneRegister, public ISceneInitializer
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~ISceneManager() = default;

		/**
		 * @brief		読み込み
		 */
		virtual bool Load() = 0;

		/**
		 * @brief		初期化
		 */
		virtual void Initialize() = 0;

		/**
		 * @brief		更新
		 */
		virtual void Update() = 0;

		/**
		 * @brief		描画
		 */
		virtual void Render() = 0;

		/**
		 * @brief		解放
		 */
		virtual void Release() = 0;
	};

	using SceneManagerPtr = std::shared_ptr<ISceneManager>;
}


