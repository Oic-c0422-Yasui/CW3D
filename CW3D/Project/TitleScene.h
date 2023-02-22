#pragma once
#include "IScene.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "GameDefine.h"
#include "SceneChanger.h"

namespace Scene
{
	/*
	* @brief	タイトルシーン
	*/
	class TitleScene : public IScene
	{
	private:
		std::shared_ptr<CTexture> m_BackTexture;
		CFont m_TitleLogoFont;
		CFont m_TextFont;
	public:
		TitleScene();
		~TitleScene();
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


