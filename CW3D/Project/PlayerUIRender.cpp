#include "PlayerUIRender.h"
#include "HPPresenter.h"
#include "MessengerUtilities.h"

ActionGame::CPlayerUIRender::CPlayerUIRender()
	: HPRender_(std::make_shared<CPlayerHPRender>())
	, skillInfoRender_(std::make_shared<CSkillInfoRender>())
	, skillsRender_(std::make_shared<CSkillRenderContainer>())
	, UltGaugeRender_(std::make_shared<CUltimateGaugeRender>())
	, comboRender_(std::make_shared<CComboRender>())
	, isShow_(true)
{
}

ActionGame::CPlayerUIRender::~CPlayerUIRender()
{

}

bool ActionGame::CPlayerUIRender::Load(const PlayerPtr& player, GameDevice device)
{
	if (!skillInfoRender_->Load(device))
	{
		return false;
	}
	if (!HPRender_->Load())
	{
		return false;
	}
	if (!skillsRender_->Load())
	{
		return false;
	}
	if (!UltGaugeRender_->Load())
	{
		return false;
	}
	if (!comboRender_->Load())
	{
		return false;
	}

	CUltGaugePresenter::Present(player, UltGaugeRender_);
	CHPPresenter::Present(player, HPRender_);
	CComboPresenter::Present(player, comboRender_);

	/* メッセージ登録 */
	//UIの表示・非表示
	MyUtil::CUIMessageFunc::Load("PlayerUI",
		[this]() {VisibleUI(); },
		[this]() {DisableUI(); });
	//デバイス変更時のUI変更
	MyUtil::CChangeDeviceMessageFunc::Load("PlayerUI",
		[this]() {ChangeKeyBoardUI(); },
		[this]() {ChangeControllerUI(); });



	return true;
}

void ActionGame::CPlayerUIRender::Initialize()
{
	comboRender_->Initialize();
	isShow_ = true;
}

void ActionGame::CPlayerUIRender::Render()
{
	if (!isShow_)
	{
		return;
	}
	skillInfoRender_->Render();
	skillsRender_->Render();
	HPRender_->Render();
	UltGaugeRender_->Render();
	skillInfoRender_->RenderKeyName();
	comboRender_->Render();
}

void ActionGame::CPlayerUIRender::Release()
{
	MyUtil::CUIMessageFunc::Delete("PlayerUI");
	MyUtil::CChangeDeviceMessageFunc::Delete("PlayerUI");
	skillInfoRender_.reset();
	skillsRender_.reset();
	HPRender_.reset();
	UltGaugeRender_.reset();
	comboRender_.reset();
}

void ActionGame::CPlayerUIRender::VisibleUI()
{
	isShow_ = true;
}

void ActionGame::CPlayerUIRender::DisableUI()
{
	isShow_ = false;
}

void ActionGame::CPlayerUIRender::ChangeKeyBoardUI()
{
	auto GetPosition = [&](const std::string& key) { return skillInfoRender_->GetKeyBoardSkillPosition(key); };
	skillsRender_->Initialize(GetPosition);
	skillInfoRender_->ChangeKeyBoardTexture();
}

void ActionGame::CPlayerUIRender::ChangeControllerUI()
{
	auto GetPosition = [&](const std::string& key) { return skillInfoRender_->GetControllerSkillPosition(key); };
	skillsRender_->Initialize(GetPosition);
	skillInfoRender_->ChangeControllerTexture();
}
