#pragma once
#include "IScene.h"
#include	"Common.h"
#include	"Player.h"


namespace Scene
{
	/*
	* @brief	�퓬���
	*/
	class CHomeScene : public IScene
	{
	private:
		//�v���C���[
		ActionGame::PlayerPtr player_;

	public:
		CHomeScene();
		~CHomeScene();
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


