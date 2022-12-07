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
		std::shared_ptr<CFont> m_Font;
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


