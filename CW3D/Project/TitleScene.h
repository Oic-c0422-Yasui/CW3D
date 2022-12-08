#pragma once
#include "SceneBase.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "GameDefine.h"
#include "SceneChanger.h"

namespace ActionGame
{
	class CTitleScene : public IScene
	{
	private:
		std::shared_ptr<CTexture> m_BackTexture;
		CFont m_TitleLogoFont;
		CFont m_TextFont;
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


