#pragma once
#include "Common.h"
#include "ResourceManager.h"

namespace ActionGame
{
	class BattleUICreater
	{
	private:

	public:
		BattleUICreater() {};
		~BattleUICreater() {};

		bool Create()
		{
			//スプライト３D用テクスチャ読み込み
			std::shared_ptr<CSprite3D> tempTex = std::make_shared<CSprite3D>();
			if (!tempTex->CreateSprite("UI/HP.png"))
			{
				return false;
			}
			ResourcePtrManager<CSprite3D>::GetInstance().AddResource("UI", "HPBar", tempTex);
			tempTex = std::make_shared<CSprite3D>();
			if (!tempTex->CreateSprite("UI/HPFrame.png"))
			{
				return false;
			}
			ResourcePtrManager<CSprite3D>::GetInstance().AddResource("UI", "HPFrame", tempTex);
			tempTex = std::make_shared<CSprite3D>();
			if (!tempTex->CreateSprite("UI/Damage.png"))
			{
				return false;
			}
			ResourcePtrManager<CSprite3D>::GetInstance().AddResource("UI", "DamageBar", tempTex);


			//テクスチャ読み込み
			std::shared_ptr<CTexture> tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/Skill1.png"))
			{
				return false;
			}
			ResourcePtrManager<CTexture>::GetInstance().AddResource("UI", "Skill1", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/Skill1Mono.png"))
			{
				return false;
			}
			ResourcePtrManager<CTexture>::GetInstance().AddResource("UI", "Skill1Mono", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/Skill2.png"))
			{
				return false;
			}
			ResourcePtrManager<CTexture>::GetInstance().AddResource("UI", "Skill2", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/Skill2Mono.png"))
			{
				return false;
			}
			ResourcePtrManager<CTexture>::GetInstance().AddResource("UI", "Skill2Mono", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/Skill3.png"))
			{
				return false;
			}
			ResourcePtrManager<CTexture>::GetInstance().AddResource("UI", "Skill3", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/Skill3Mono.png"))
			{
				return false;
			}
			ResourcePtrManager<CTexture>::GetInstance().AddResource("UI", "Skill3Mono", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/DropKick.png"))
			{
				return false;
			}
			ResourcePtrManager<CTexture>::GetInstance().AddResource("UI", "DropKick", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/DropKickMono.png"))
			{
				return false;
			}
			ResourcePtrManager<CTexture>::GetInstance().AddResource("UI", "DropKickMono", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/Escape.png"))
			{
				return false;
			}
			ResourcePtrManager<CTexture>::GetInstance().AddResource("UI", "Escape", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/EscapeMono.png"))
			{
				return false;
			}
			ResourcePtrManager<CTexture>::GetInstance().AddResource("UI", "EscapeMono", tempTex2D);


			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/UltFrame.png"))
			{
				return false;
			}
			ResourcePtrManager<CTexture>::GetInstance().AddResource("UI", "UltFrame", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/UltFrameMono.png"))
			{
				return false;
			}
			ResourcePtrManager<CTexture>::GetInstance().AddResource("UI", "UltFrameMono", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/SkillUI.png"))
			{
				return false;
			}
			ResourcePtrManager<CTexture>::GetInstance().AddResource("UI", "SkillUI", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/UltSkillGaugeFrame.png"))
			{
				return false;
			}
			ResourcePtrManager<CTexture>::GetInstance().AddResource("UI", "UltSkillGaugeFrame", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/UltGauge.png"))
			{
				return false;
			}
			ResourcePtrManager<CTexture>::GetInstance().AddResource("UI", "UltGauge", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/PlayerHPBar.png"))
			{
				return false;
			}
			ResourcePtrManager<CTexture>::GetInstance().AddResource("UI", "PlayerHPBar", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/PlayerHPFrame.png."))
			{
				return false;
			}
			ResourcePtrManager<CTexture>::GetInstance().AddResource("UI", "PlayerHPFrame", tempTex2D);

			//フォント読み込み
			std::shared_ptr<CFont> tempFont = std::make_shared<CFont>();
			if (!tempFont->Create(20, "ＭＳ ゴシック"))
			{
				return false;
			}
			ResourcePtrManager<CFont>::GetInstance().AddResource("Font", "CTFont", tempFont);
			tempFont = std::make_shared<CFont>();
			if (!tempFont->Create(15, "ＭＳ ゴシック"))
			{
				return false;
			}
			ResourcePtrManager<CFont>::GetInstance().AddResource("Font", "SkillFont", tempFont);

			tempFont.reset();
			tempTex.reset();
			tempTex2D.reset();

			return true;
		}
	};



}

