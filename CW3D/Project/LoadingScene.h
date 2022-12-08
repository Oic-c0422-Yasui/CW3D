#pragma once
#include "SceneBase.h"
#include "ResourceManager.h"
#include "ThreadCreator.h"
#include "SceneChanger.h"

namespace ActionGame
{
	class LoadingScene : public IScene
	{
	private:
		ScenePtr m_LoadingScene;

		ThreadCreator m_LoadThread;

		std::shared_ptr<CTexture> m_BackTex;

		std::shared_ptr<CFont> m_Font;
	public:
		LoadingScene(ScenePtr loadingScene);
		~LoadingScene();
		bool Load()override;
		void Initialize()override;
		void Update()override;
		void Render()override;
		void RenderDebug()override;
		void Render2D()override;
		void Render2DDebug()override;
		void Release() override;

	};
	
}


