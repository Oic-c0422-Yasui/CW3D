#include "PlayerUIRender.h"

ActionGame::CPlayerUIRender::CPlayerUIRender()
	: HPRender_(std::make_shared<CPlayerHPRender>())
	, skillControllerRender_(std::make_shared<CSkillControllerRender>())
	, skillsRender_(std::make_shared<CSkillRenderContainer>())
	, UltGaugeRender_(std::make_shared<CUltimateGaugeRender>())
{
}

ActionGame::CPlayerUIRender::~CPlayerUIRender()
{
	Release();
}

bool ActionGame::CPlayerUIRender::Load()

{
	auto& player = ServiceLocator< CPlayer >::GetService();
	if (player == nullptr)
	{
		return false;
	}
	if (skillControllerRender_->Load() == false)
	{
		return false;
	}
	if (HPRender_->Load() == false)
	{
		return false;
	}
	if (skillsRender_->Load() == false)
	{
		return false;
	}
	if (UltGaugeRender_->Load() == false)
	{
		return false;
	}

	CUltGaugePresenter::Present(player, UltGaugeRender_);
	return true;
}

void ActionGame::CPlayerUIRender::Initialize()
{
	auto GetPosition = [this](const std::string& key) { return skillControllerRender_->GetSkillPosition(key); };
	skillsRender_->Initialize(GetPosition);
}

void ActionGame::CPlayerUIRender::Render()
{
	skillControllerRender_->Render();
	skillsRender_->Render();
	HPRender_->Render();
	UltGaugeRender_->Render();
	skillControllerRender_->RenderKeyName();
}

void ActionGame::CPlayerUIRender::Release()
{

	skillControllerRender_.reset();
	skillsRender_.reset();
	HPRender_.reset();
	UltGaugeRender_.reset();
}
