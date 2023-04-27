#include "BattleUILoader.h"
#include "ResourceManager.h"

bool ActionGame::CBattleUILoader::Load()
{
	///////////////////////////////////////////////
	// スプライト３Dテクスチャ読み込み
	///////////////////////////////////////////////
	
	constexpr auto tagUI = "UI";

	//３DHPバー
	std::shared_ptr<CSprite3D> tempTex = std::make_shared<CSprite3D>();
	if (!tempTex->CreateSprite("UI/HP.png"))
	{
		return false;
	}
	ResourcePtrManager<CSprite3D>::GetInstance().AddResource(tagUI, "HPBar", tempTex);
	tempTex = std::make_shared<CSprite3D>();
	if (!tempTex->CreateSprite("UI/HPFrame.png"))
	{
		return false;
	}
	ResourcePtrManager<CSprite3D>::GetInstance().AddResource(tagUI, "HPFrame", tempTex);
	tempTex = std::make_shared<CSprite3D>();
	if (!tempTex->CreateSprite("UI/Damage.png"))
	{
		return false;
	}
	ResourcePtrManager<CSprite3D>::GetInstance().AddResource(tagUI, "DamageBar", tempTex);

	///////////////////////////////////////////////
	// テクスチャ読み込み
	///////////////////////////////////////////////
	
	//スキル
	std::shared_ptr<CTexture> tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/Skill1.png")) 
	{ 
		return false; 
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "Skill1", tempTex2D);

	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/Skill1Mono.png"))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "Skill1Mono", tempTex2D);

	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/Skill2.png"))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "Skill2", tempTex2D);

	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/Skill2Mono.png"))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "Skill2Mono", tempTex2D);

	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/Skill3.png"))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "Skill3", tempTex2D);

	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/Skill3Mono.png"))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "Skill3Mono", tempTex2D);

	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/Skill4.png"))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "Skill4", tempTex2D);

	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/Skill4Mono.png"))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "Skill4Mono", tempTex2D);

	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/Escape.png"))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "Escape", tempTex2D);

	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/EscapeMono.png"))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "EscapeMono", tempTex2D);

	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/UltFrame.png"))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "UltFrame", tempTex2D);

	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/UltFrameMono.png"))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "UltFrameMono", tempTex2D);

	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/SkillUI_PC.png"))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "SkillUI_PC", tempTex2D);

	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/SkillUI_Pad.png"))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "SkillUI_Pad", tempTex2D);

	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/UltSkillGaugeFrame.png"))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "UltSkillGaugeFrame", tempTex2D);

	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/PlayerSPBar.png"))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "UltGauge", tempTex2D);

	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/PlayerSPFrame.png"))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "UltGaugeFrame", tempTex2D);


	//HPバー
	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/PlayerHPBar.png"))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "PlayerHPBar", tempTex2D);
	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/PlayerHPFrame.png."))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "PlayerHPFrame", tempTex2D);

	//ボスHPバー
	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/BossHPBar.png"))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "BossHPBar", tempTex2D);
	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/BossHPFrame.png."))
	{
		return false;
	}
	ResourcePtrManager<CTexture>::GetInstance().AddResource(tagUI, "BossHPFrame", tempTex2D);

	///////////////////////////////////////////////
	// フォント読み込み
	///////////////////////////////////////////////

	constexpr auto tagFont = "Font";

	std::shared_ptr<CFont> tempFont = std::make_shared<CFont>();
	if (!tempFont->Create(25, "M PLUS 1"))
	{
		return false;
	}
	ResourcePtrManager<CFont>::GetInstance().AddResource(tagFont, "CTFont", tempFont);

	tempFont = std::make_shared<CFont>();
	if (!tempFont->Create(17, "M PLUS 1"))
	{
		return false;
	}
	ResourcePtrManager<CFont>::GetInstance().AddResource(tagFont, "SkillFont", tempFont);

	tempFont = std::make_shared<CFont>();
	if (!tempFont->Create(25, "M PLUS 1"))
	{
		return false;
	}
	ResourcePtrManager<CFont>::GetInstance().AddResource(tagFont, "PadButtonFont", tempFont);

	tempFont = std::make_shared<CFont>();
	if (!tempFont->Create(60, "M PLUS 1"))
	{
		return false;
	}
	ResourcePtrManager<CFont>::GetInstance().AddResource(tagFont, "ComboFont", tempFont);
	
	tempFont = std::make_shared<CFont>();
	if (!tempFont->Create(200, "M PLUS 1"))
	{
		return false;
	}
	tempFont->SetBold(60);
	ResourcePtrManager<CFont>::GetInstance().AddResource(tagFont, "GameOverFont", tempFont);

	tempFont = std::make_shared<CFont>();
	if (!tempFont->Create(50, "M PLUS 1"))
	{
		return false;
	}
	ResourcePtrManager<CFont>::GetInstance().AddResource(tagFont, "GameOverButtonFont", tempFont);


	return true;
}
