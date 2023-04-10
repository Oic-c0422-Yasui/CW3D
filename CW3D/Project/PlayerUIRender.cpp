#include "PlayerUIRender.h"
#include "RegistMessageServiceDefine.h"
#include "HPPresenter.h"



ActionGame::CPlayerUIRender::CPlayerUIRender()
	: HPRender_(std::make_shared<CPlayerHPRender>())
	, skillControllerRender_(std::make_shared<CSkillInfoRender>())
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

bool ActionGame::CPlayerUIRender::Load(const PlayerPtr& player)
{
	if (!skillControllerRender_->Load())
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

	const auto& message = RegistMessageService::GetService();
	//メッセージ登録
	//UI表示メッセージ
	message->Regist(UI_Visible,
		[&]() {VisibleUI(); });
	//UI非表示メッセージ
	message->Regist(UI_Disable,
		[&]() {DisableUI(); });

	return true;
}

void ActionGame::CPlayerUIRender::Initialize()
{
	auto GetPosition = [this](const std::string& key) { return skillControllerRender_->GetSkillPosition(key); };
	skillsRender_->Initialize(GetPosition);
	comboRender_->Initialize();
	isShow_ = true;
}

void ActionGame::CPlayerUIRender::Render()
{
	if (!isShow_)
	{
		return;
	}
	skillControllerRender_->Render();
	skillsRender_->Render();
	HPRender_->Render();
	UltGaugeRender_->Render();
	skillControllerRender_->RenderKeyName();
	comboRender_->Render();
}

void ActionGame::CPlayerUIRender::Release()
{

	skillControllerRender_.reset();
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