#include "NormalEnemyHPRender.h"


ActionGame::CNormalEnemyHPRender::CNormalEnemyHPRender()
	: ActionGame::CEnemyHPRender()
	, position_(0, 0, 0)
	, offset_(0, 0, 0)
	, size_(0, 0, 0)
{

}

ActionGame::CNormalEnemyHPRender::~CNormalEnemyHPRender()
{
	Release();
}

bool ActionGame::CNormalEnemyHPRender::Load()
{
	HPBar_ = ResourcePtrManager<CSprite3D>::GetInstance().GetResource("UI", "DamageBar");
	HPFrame_ = ResourcePtrManager<CSprite3D>::GetInstance().GetResource("UI", "HPFrame");
	damageBar_ = ResourcePtrManager<CSprite3D>::GetInstance().GetResource("UI", "HPBar");
	return true;
}

void ActionGame::CNormalEnemyHPRender::Initialize()
{
	Load();


	offset_ = Vector3(0, 2, 0);
	size_ = Vector3(1, 0.85f, 1);
	HPBar_->m_Angle.z = MOF_ToRadian(180);
	HPFrame_->m_Angle.z = MOF_ToRadian(180);
	damageBar_->m_Angle.z = MOF_ToRadian(180);
	HPBar_->m_Angle.x = MOF_ToRadian(0);
	HPFrame_->m_Angle.x = MOF_ToRadian(0);
	damageBar_->m_Angle.x = MOF_ToRadian(0);
	HPFrame_->m_Scale = size_;
	HPBar_->m_Scale = size_;
	damageBar_->m_Scale = size_;
	HPFrame_->m_Color = CVector4(1.0f, 1.0f, 1.0f, 0.75f);

}

void ActionGame::CNormalEnemyHPRender::Reset() noexcept
{
	currentHPPercent_ = 1.0f;
	currentHPGaugePercent_ = 1.0f;
}

void ActionGame::CNormalEnemyHPRender::Render()
{

	if (!isShow_)
	{
		return;
	}

	HPFrame_->m_Position = position_ + offset_;
	HPBar_->m_Position = position_ + offset_;
	damageBar_->m_Position = position_ + offset_;

	float parcent = (float)HP_ / (float)maxHP_;
	parcent = min(parcent, 1.0f);
	currentHPPercent_ = parcent;
	//ŽlŠp‚ÅHPƒQ[ƒW•`‰æ
	LPCamera cam = CGraphicsUtilities::GetCamera();
	HPFrame_->Update();
	HPFrame_->m_World.Multiply3x3(cam->GetBillBoardMatrix());

	HPFrame_->Render();
	//•\Ž¦ƒQ[ƒW‚ð™X‚É•Ï‰»‚³‚¹‚é
	if (fabsf(currentHPGaugePercent_ - currentHPPercent_) > 0.01f)
	{
		currentHPGaugePercent_ += (currentHPPercent_ - currentHPGaugePercent_) * 0.02f;
		damageBar_->m_Scale.x = size_.x * currentHPGaugePercent_;
		float offset = (size_.x - damageBar_->m_Scale.x) * 0.5f;
		damageBar_->m_Position.x = (position_.x + offset_.x) - offset;
		damageBar_->Update();
		damageBar_->m_World.Multiply3x3(cam->GetBillBoardMatrix());
		damageBar_->Render();
	}
	else
	{
		currentHPGaugePercent_ = currentHPPercent_;
	}

	HPBar_->m_Scale.x = size_.x * currentHPPercent_;
	float offset = (size_.x - HPBar_->m_Scale.x) * 0.5f;
	HPBar_->m_Position.x = (position_.x + offset_.x) - offset;
	HPBar_->Update();
	HPBar_->m_World.Multiply3x3(cam->GetBillBoardMatrix());
	HPBar_->Render();

}

void ActionGame::CNormalEnemyHPRender::Release(void)
{
	HPBar_.reset();
	HPFrame_.reset();
	damageBar_.reset();
}
