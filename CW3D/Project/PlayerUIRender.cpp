#include "PlayerUIRender.h"
#include "RegistMessageServiceDefine.h"
#include "HPPresenter.h"



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
	Release();
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

	switch (device)
	{
	case GameDevice::KeyBoardAndMouse:
		ChangeKeyBoardUI();
		break;
	case GameDevice::Controller:
		ChangeControllerUI();
		break;
	default:
		break;
	}

	CUltGaugePresenter::Present(player, UltGaugeRender_);
	CHPPresenter::Present(player, HPRender_);
	CComboPresenter::Present(player, comboRender_);

	const auto& message = RegistMessageService::GetService();
	/* メッセージ登録 */
	//UI表示メッセージ
	message->Regist(UI_Visible,
		[this]() {VisibleUI(); });
	//UI非表示メッセージ
	message->Regist(UI_Disable,
		[this]() {DisableUI(); });

	//キーボード表示メッセージ
	message->Regist(ChangeDevice_KeyBoard,
		[this]() {ChangeKeyBoardUI(); });
	//コントローラー表示メッセージ
	message->Regist(ChangeDevice_Controller,
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
	auto GetPosition = [this](const std::string& key) { return skillInfoRender_->GetKeyBoardSkillPosition(key); };
	skillsRender_->Initialize(GetPosition);
	skillInfoRender_->ChangeKeyBoardTexture();
}

void ActionGame::CPlayerUIRender::ChangeControllerUI()
{
	auto GetPosition = [this](const std::string& key) { return skillInfoRender_->GetControllerSkillPosition(key); };
	skillsRender_->Initialize(GetPosition);
	skillInfoRender_->ChangeControllerTexture();
}
