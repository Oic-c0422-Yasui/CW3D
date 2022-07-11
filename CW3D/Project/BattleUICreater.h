#pragma once
#include "GameDefine.h"
#include "ResourceManager.h"

namespace Sample
{
	class CBattleUICreater
	{
	private:

	public:
		CBattleUICreater() {};
		~CBattleUICreater() {};

		bool Create()
		{
			//スプライト３D用テクスチャ読み込み
			std::shared_ptr<CSprite3D> tempTex = std::make_shared<CSprite3D>();
			if (!tempTex->CreateSprite("UI/HP.png"))
			{
				return false;
			}
			ResourceManager<CSprite3D>::GetInstance().AddResource("HPBar", tempTex);
			tempTex = std::make_shared<CSprite3D>();
			if (!tempTex->CreateSprite("UI/HPFrame.png"))
			{
				return false;
			}
			ResourceManager<CSprite3D>::GetInstance().AddResource("HPFrame", tempTex);
			tempTex = std::make_shared<CSprite3D>();
			if (!tempTex->CreateSprite("UI/Damage.png"))
			{
				return false;
			}
			ResourceManager<CSprite3D>::GetInstance().AddResource("DamageBar", tempTex);


			//テクスチャ読み込み
			std::shared_ptr<CTexture> tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/Skill1.png"))
			{
				return false;
			}
			ResourceManager<CTexture>::GetInstance().AddResource("Skill1", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/Skill1Mono.png"))
			{
				return false;
			}
			ResourceManager<CTexture>::GetInstance().AddResource("Skill1Mono", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/Skill2.png"))
			{
				return false;
			}
			ResourceManager<CTexture>::GetInstance().AddResource("Skill2", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/Skill2Mono.png"))
			{
				return false;
			}
			ResourceManager<CTexture>::GetInstance().AddResource("Skill2Mono", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/Skill3.png"))
			{
				return false;
			}
			ResourceManager<CTexture>::GetInstance().AddResource("Skill3", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/Skill3Mono.png"))
			{
				return false;
			}
			ResourceManager<CTexture>::GetInstance().AddResource("Skill3Mono", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/DropKick.png"))
			{
				return false;
			}
			ResourceManager<CTexture>::GetInstance().AddResource("DropKick", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/DropKickMono.png"))
			{
				return false;
			}
			ResourceManager<CTexture>::GetInstance().AddResource("DropKickMono", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/Escape.png"))
			{
				return false;
			}
			ResourceManager<CTexture>::GetInstance().AddResource("Escape", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/EscapeMono.png"))
			{
				return false;
			}
			ResourceManager<CTexture>::GetInstance().AddResource("EscapeMono", tempTex2D);


			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/UltFrame.png"))
			{
				return false;
			}
			ResourceManager<CTexture>::GetInstance().AddResource("UltFrame", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/UltFrameMono.png"))
			{
				return false;
			}
			ResourceManager<CTexture>::GetInstance().AddResource("UltFrameMono", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/SkillUI.png"))
			{
				return false;
			}
			ResourceManager<CTexture>::GetInstance().AddResource("SkillUI", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/UltSkillGaugeFrame.png"))
			{
				return false;
			}
			ResourceManager<CTexture>::GetInstance().AddResource("UltSkillGaugeFrame", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/UltGauge.png"))
			{
				return false;
			}
			ResourceManager<CTexture>::GetInstance().AddResource("UltGauge", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/PlayerHPBar.png"))
			{
				return false;
			}
			ResourceManager<CTexture>::GetInstance().AddResource("PlayerHPBar", tempTex2D);
			tempTex2D = std::make_shared<CTexture>();
			if (!tempTex2D->Load("UI/PlayerHPFrame.png."))
			{
				return false;
			}
			ResourceManager<CTexture>::GetInstance().AddResource("PlayerHPFrame", tempTex2D);

			//フォント読み込み
			std::shared_ptr<CFont> tempFont = std::make_shared<CFont>();
			if (!tempFont->Create(20, "ＭＳ ゴシック"))
			{
				return false;
			}
			ResourceManager<CFont>::GetInstance().AddResource("CTFont", tempFont);
			tempFont = std::make_shared<CFont>();
			if (!tempFont->Create(15, "ＭＳ ゴシック"))
			{
				return false;
			}
			ResourceManager<CFont>::GetInstance().AddResource("SkillFont", tempFont);

			tempFont.reset();
			tempTex.reset();
			tempTex2D.reset();

			return true;
		}
	};



}

