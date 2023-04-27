#include "GameOver.h"
#include "SceneServiceDefine.h"
#include "InputManager.h"
#include "SceneChangeFade.h"
#include "InputDefine.h"
#include "ResourceManager.h"
#include "MessengerUtilities.h"

ActionGame::CGameOver::CGameOver()
	: fade_()
	, isEnd_()
	, buttonFont_(nullptr)
	, textFont_(nullptr)
	, retryButtonStr_(nullptr)
	, endButtonStr_(nullptr)
{
}

ActionGame::CGameOver::~CGameOver()
{
}

bool ActionGame::CGameOver::Load()
{

	textFont_ = ResourcePtrManager<CFont>::GetInstance().GetResource("Font", "GameOverFont");
	if (textFont_ == nullptr)
	{
		return false;
	}
	buttonFont_ = ResourcePtrManager<CFont>::GetInstance().GetResource("Font", "GameOverButtonFont");
	if (buttonFont_ == nullptr)
	{
		return false;
	}

	//�f�o�C�X�ύX���Ɏ��s����֐��o�^
	MyUtil::CChangeDeviceMessageFunc::Load("GameOver",
		[this]() {ChangeKeyBoardUI(); },
		[this]() {ChangeControllerUI(); });


	return true;
}

void ActionGame::CGameOver::Initialize()
{
	isEnd_ = false;
	fade_.Initialize(0,0.2f,200);
	fade_.Start();
}

void ActionGame::CGameOver::Update()
{
	//�I���t���O
	if (isEnd_) { return; }

	//�t�F�[�h�C��
	if (!fade_.IsEnd())
	{
		fade_.Update();
		return;
	}

	//�t�F�[�h�G�t�F�N�g
	const float time = 0.5f;
	auto sceneEffect = std::make_shared<Scene::SceneChangeFade>(time, time, time);
	//���g���C
	if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_ENTER))
	{
		//������
		SceneInitializeService::GetService()->InitializeScene(sceneEffect);
		isEnd_ = true;
		return;
	}
	//�J��
	else if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_CANCEL))
	{
		//�^�C�g���֑J��
		SceneChangeService::GetService()->ChangeScene(SCENENO::TITLE, sceneEffect);
		isEnd_ = true;
		return;
	}

}

void ActionGame::CGameOver::Render()
{
	float width = g_pGraphics->GetTargetWidth();
	float height = g_pGraphics->GetTargetHeight();
	CRectangle rect(0, 0, width, height);
	auto alpha = fade_.GetFadeValue();
	auto color = MOF_ARGB(alpha, 0, 0, 0);

	//�w�i
	CGraphicsUtilities::RenderFillRect(rect, color);
	if (!fade_.IsEnd())
	{
		return;
	}

	//�Q�[���I�[�o�[�e�L�X�g
	//�^�C�g�����S
	textFont_->CalculateStringRect(0, 0, "GameOver", rect);
	textFont_->RenderString(width * 0.5f - (rect.GetWidth() * 0.5f), height * 0.2f, "GameOver");

	//�{�^��
	buttonFont_->CalculateStringRect(width * 0.5f, height * 0.7f, "���g���C�F", rect);
	rect += CRectangle(rect.GetWidth() * -0.5f, 0, rect.GetWidth() * -0.5f, 0);
	buttonFont_->RenderString(rect.Left, rect.Top, "���g���C�F");
	buttonFont_->RenderString(rect.Right, rect.Top, retryButtonStr_);

	buttonFont_->CalculateStringRect(width * 0.5f, height * 0.78f, "�^�C�g���֖߂�F", rect);
	rect += CRectangle(rect.GetWidth() * -0.5f, 0, rect.GetWidth() * -0.5f, 0);
	buttonFont_->RenderString(rect.Left, rect.Top, "�^�C�g���֖߂�F");
	buttonFont_->RenderString(rect.Right, rect.Top, endButtonStr_);


}

void ActionGame::CGameOver::Release()
{
	textFont_.reset();
	buttonFont_.reset();
	MyUtil::CChangeDeviceMessageFunc::Delete("GameOver");
}

bool ActionGame::CGameOver::IsEnd() const noexcept
{
	return isEnd_;
}

void ActionGame::CGameOver::ChangeKeyBoardUI()
{
	retryButtonStr_ = "Z�L�[";
	endButtonStr_ = "X�L�[";
}

void ActionGame::CGameOver::ChangeControllerUI()
{
	retryButtonStr_ = "A�{�^��";
	endButtonStr_ = "B�{�^��";
}