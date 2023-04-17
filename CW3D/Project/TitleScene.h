#pragma once
#include "IScene.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "GameDefine.h"
#include "SceneChanger.h"
#include "SceneChangeFade.h"

namespace Scene
{
	/*
	* @brief	タイトルシーン
	*/
	class CTitleScene : public IScene
	{
	private:
		std::shared_ptr<CTexture> backTexture_;
		CFont		titleLogoFont_;
		CFont		textFont_;
		char*		startButtonStr_;
		char*		endButtonStr_;
	private:
		void ChangeKeyBoardUI();
		void ChangeControllerUI();

	public:
		CTitleScene();
		~CTitleScene();
		bool Load() override;
		void Initialize() override;
		void Update() override;
		void Render() override;
		void RenderDebug() override;
		void Render2D() override;
		void Render2DDebug() override;
		void Release() override;
	};
	
}


