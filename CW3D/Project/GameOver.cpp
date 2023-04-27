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

	//デバイス変更時に実行する関数登録
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
	//終了フラグ
	if (isEnd_) { return; }

	//フェードイン
	if (!fade_.IsEnd())
	{
		fade_.Update();
		return;
	}

	//フェードエフェクト
	const float time = 0.5f;
	auto sceneEffect = std::make_shared<Scene::SceneChangeFade>(time, time, time);
	//リトライ
	if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_ENTER))
	{
		//初期化
		SceneInitializeService::GetService()->InitializeScene(sceneEffect);
		isEnd_ = true;
		return;
	}
	//遷移
	else if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_CANCEL))
	{
		//タイトルへ遷移
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

	//背景
	CGraphicsUtilities::RenderFillRect(rect, color);
	if (!fade_.IsEnd())
	{
		return;
	}

	//ゲームオーバーテキスト
	//タイトルロゴ
	textFont_->CalculateStringRect(0, 0, "GameOver", rect);
	textFont_->RenderString(width * 0.5f - (rect.GetWidth() * 0.5f), height * 0.2f, "GameOver");

	//ボタン
	buttonFont_->CalculateStringRect(width * 0.5f, height * 0.7f, "リトライ：", rect);
	rect += CRectangle(rect.GetWidth() * -0.5f, 0, rect.GetWidth() * -0.5f, 0);
	buttonFont_->RenderString(rect.Left, rect.Top, "リトライ：");
	buttonFont_->RenderString(rect.Right, rect.Top, retryButtonStr_);

	buttonFont_->CalculateStringRect(width * 0.5f, height * 0.78f, "タイトルへ戻る：", rect);
	rect += CRectangle(rect.GetWidth() * -0.5f, 0, rect.GetWidth() * -0.5f, 0);
	buttonFont_->RenderString(rect.Left, rect.Top, "タイトルへ戻る：");
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
	retryButtonStr_ = "Zキー";
	endButtonStr_ = "Xキー";
}

void ActionGame::CGameOver::ChangeControllerUI()
{
	retryButtonStr_ = "Aボタン";
	endButtonStr_ = "Bボタン";
}