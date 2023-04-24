#pragma once
#include "Common.h"

namespace ActionGame
{
	class CResult
	{
	private:
		std::shared_ptr<CFont> buttonFont_;
		std::shared_ptr<CFont> textFont_;
		bool isEnd_;
		char* retryButtonStr_;
		char* endButtonStr_;
		float movePosX_;
		float secondMovePosX_;
		float thirdMovePosX_;
		float speed_;
		bool  isShowFirstStr_;
		bool isInit_;

		std::vector<std::string> str_;
	private:
		void ChangeKeyBoardUI();
		void ChangeControllerUI();
	public:
		CResult();
		~CResult();
		bool Load();
		void Initialize();
		void Update();
		void Render();
		void Release();
		bool IsEnd() const noexcept;
	};

}


