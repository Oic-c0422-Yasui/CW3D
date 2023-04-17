#include "SkillUltGaugeRender.h"
#include "ResourceManager.h"

ActionGame::CSkillUltGaugeRender::CSkillUltGaugeRender()
	: gauge_(0.0f)
	, maxGauge_(0.0f)
	, position_(0, 0)
	, gaugePosition_(0, 0)
{

}

ActionGame::CSkillUltGaugeRender::~CSkillUltGaugeRender()
{
	Release();
}

bool ActionGame::CSkillUltGaugeRender::Load()
{
	availableSkillFrame_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "UltFrame");
	unavailableSKillFrame_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "UltFrameMono");
	gaugeFrame_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "UltSkillGaugeFrame");
	return true;
}

void ActionGame::CSkillUltGaugeRender::Initialize(const Vector2& pos)
{
	//���W����
	position_ = pos + Vector2(0, -25);
	gaugePosition_ = position_ + Vector2(13, 1);
}

void ActionGame::CSkillUltGaugeRender::Reset() noexcept
{
	gauge_ = 0.0f;
	maxGauge_ = 0.0f;
}

void ActionGame::CSkillUltGaugeRender::Render()
{

	float percent = gauge_ / maxGauge_;
	percent = std::clamp(percent,0.0f, 1.0f);

	//�X�L�����g�p�\�Ȃ�
	if (percent >= 1.0f)
	{
		//�g�p�\�t���[���`��
		availableSkillFrame_->Render(position_.x, position_.y, TEXALIGN_CENTERCENTER);
	}
	else
	{
		//�g�p�s�t���[���`��
		unavailableSKillFrame_->Render(position_.x, position_.y, TEXALIGN_CENTERCENTER);
	}

	//�X�L�������ɕK�v�ȕK�E�Z�Q�[�W�`��
	CRectangle rect(0, gaugeFrame_->GetHeight() * (1.0f - percent),
			gaugeFrame_->GetWidth(), gaugeFrame_->GetHeight());
	gaugeFrame_->Render(gaugePosition_.x, gaugePosition_.y, rect, TEXALIGN_BOTTOMCENTER);
}

void ActionGame::CSkillUltGaugeRender::Release()
{
	availableSkillFrame_.reset();
	unavailableSKillFrame_.reset();
	gaugeFrame_.reset();
}
