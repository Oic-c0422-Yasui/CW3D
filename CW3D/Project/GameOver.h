#pragma once
#include "Common.h"
#include "Fade.h"

namespace ActionGame
{
	/*
	* @brief	ゲームオーバークラス
	*/
	class CGameOver
	{
	private:
		CFade fade_;
		std::shared_ptr<CFont> buttonFont_;
		std::shared_ptr<CFont> textFont_;
		bool isEnd_;
		char* retryButtonStr_;
		char* endButtonStr_;
	private:
		void ChangeKeyBoardUI();
		void ChangeControllerUI();
	public:
		CGameOver();
		~CGameOver();
		bool Load();
		void Initialize();
		void Update();
		void Render();
		void Release();
		bool IsEnd() const noexcept;
	};
}


