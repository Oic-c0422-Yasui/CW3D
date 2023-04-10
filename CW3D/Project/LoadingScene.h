#pragma once
#include "IScene.h"
#include "ResourceManager.h"
#include "ThreadCreator.h"
#include "SceneChanger.h"
#include "Timer.h"

namespace Scene
{
	class CLoadingScene : public IScene
	{
	private:
		ScenePtr loadingScene_;

		ThreadCreator loadThread_;

		std::shared_ptr<CTexture> backTexture_;

		std::shared_ptr<CFont> font_;

		std::string loadingStr_;
		BYTE currentAnimCount_;
		ActionGame::CTimer timer_;
	public:
		CLoadingScene(ScenePtr loadingScene);
		~CLoadingScene();
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


