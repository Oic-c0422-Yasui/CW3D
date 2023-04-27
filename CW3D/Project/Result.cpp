#include "Result.h"
#include "SceneServiceDefine.h"
#include "InputManager.h"
#include "SceneChangeFade.h"
#include "InputDefine.h"
#include "ResourceManager.h"
#include "MessengerUtilities.h"

ActionGame::CResult::CResult()
	: isEnd_(false)
	, buttonFont_(nullptr)
	, textFont_(nullptr)
	, retryButtonStr_(nullptr)
	, endButtonStr_(nullptr)
	, isShowFirstStr_(false)
	, speed_(0.0f)
	, movePosX_(0.0f)
	, secondMovePosX_(0.0f)
	, thirdMovePosX_(0.0f)
	, isInit_(false)
	, fade_()
	, str_()

{
}

ActionGame::CResult::~CResult()
{
}

bool ActionGame::CResult::Load()
{

	buttonFont_ = ResourcePtrManager<CFont>::GetInstance().GetResource("Font", "GameOverButtonFont");
	if (buttonFont_ == nullptr)
	{
		return false;
	}
	textFont_ = std::make_shared<CFont>();
	textFont_->Create(300, "ＭＳ ゴシック");

	//デバイス変更時に実行する関数登録
	MyUtil::CChangeDeviceMessageFunc::Load("Result",
		[this]() {ChangeKeyBoardUI(); },
		[this]() {ChangeControllerUI(); });

	return true;
}

void ActionGame::CResult::Initialize()
{
	speed_ = 20.0f;
	movePosX_ = g_pGraphics->GetTargetWidth();
	secondMovePosX_ = movePosX_;
	str_.clear();
	str_.push_back("全部倒した");
	str_.push_back("あああああああああ");
	
	fade_.Initialize(0,2.5f,255);
	fade_.Start();
	isInit_ = false;
	isEnd_ = false;
	isShowFirstStr_ = true;
}

void ActionGame::CResult::Update()
{
	//終了フラグ
	if (isEnd_) { return; }

	//Initialize時にはテクスチャが作成できないため、更新時に１回のみ初期化
	if (!isInit_)
	{
		CRectangle rect;
		textFont_->CalculateStringRect(0, 0, str_[0].c_str(), rect);
		secondMovePosX_ = movePosX_ + rect.GetWidth();
		textFont_->CalculateStringRect(0, 0, str_[1].c_str(), rect);
		thirdMovePosX_ = secondMovePosX_ + rect.GetWidth();

		isInit_ = true;
	}
	
	//文字移動
	movePosX_ -= speed_;
	secondMovePosX_ -= speed_;
	thirdMovePosX_ -= speed_;

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

void ActionGame::CResult::Render()
{
	float width = g_pGraphics->GetTargetWidth();
	float height = g_pGraphics->GetTargetHeight();
	CRectangle rect(0, 0, width, height);

	//ゲームクリアーテキスト
	//テキスト
	if (isShowFirstStr_)
	{
		textFont_->CalculateStringRect(0, 0, str_[0].c_str(), rect);
		textFont_->RenderString(movePosX_, height * 0.4f - (rect.GetHeight() * 0.5f), str_[0].c_str());

		if (movePosX_ + rect.GetWidth() < 0)
		{
			isShowFirstStr_ = false;
		}
	}

	//ああああああの部分が画面外に行ったら使い回す
	textFont_->CalculateStringRect(0, 0, str_[1].c_str(), rect);
	textFont_->RenderString(secondMovePosX_, height * 0.4f - (rect.GetHeight() * 0.5f), str_[1].c_str());
	if (secondMovePosX_ + rect.GetWidth() < 0)
	{
		secondMovePosX_ = thirdMovePosX_ + rect.GetWidth();
	}
	textFont_->RenderString(thirdMovePosX_, height * 0.4f - (rect.GetHeight() * 0.5f), str_[1].c_str());
	if (thirdMovePosX_ + rect.GetWidth() < 0)
	{
		thirdMovePosX_ = secondMovePosX_ + rect.GetWidth();
	}


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

void ActionGame::CResult::Release()
{
	textFont_.reset();
	buttonFont_.reset();
	str_.clear();
	MyUtil::CChangeDeviceMessageFunc::Delete("Result");
}

bool ActionGame::CResult::IsEnd() const noexcept
{
	return isEnd_;
}

void ActionGame::CResult::ChangeKeyBoardUI()
{
	retryButtonStr_ = "Zキー";
	endButtonStr_ = "Xキー";
}

void ActionGame::CResult::ChangeControllerUI()
{
	retryButtonStr_ = "Aボタン";
	endButtonStr_ = "Bボタン";
}


