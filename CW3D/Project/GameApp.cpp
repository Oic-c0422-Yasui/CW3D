/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"IScene.h"
#include	"BattleScene.h"
#include	"SceneManager.h"
#include	"TitleScene.h"
#include	"MofInput.h"
#include	"StateInput.h"
#include	"Messenger.h"
#include	"SendMessageServiceDefine.h"
#include	"RegistMessageServiceDefine.h"
#include	"JoyPadDefine.h"
#include	"SoundPlayer.h"
#include	"SoundPlayerServiceDefine.h"

//シーンマネージャー
Scene::SceneManagerPtr gSceneManager;

//サウンド再生
std::shared_ptr<CSoundPlayer> gSoundPlayer;

//外部フォント
LPCSTR fontPath = "Font/Mplus1-Regular.ttf";


/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	CUtilities::SetCurrentDirectory("Resource");
	CUtilities::SetFPS(60);

	//インプット読み込み
	auto input = InputManagerInstance.AddInput<Input::CMofInput>();
	InputManagerInstance.AddInput<Input::CStateInput>();
	//キーボード入力登録
	input->AddKeyboardKey(INPUT_KEY_HORIZONTAL, MOFKEY_RIGHT, MOFKEY_LEFT);
	input->AddKeyboardKey(INPUT_KEY_VERTICAL, MOFKEY_DOWN, MOFKEY_UP);
	input->AddKeyboardKey(INPUT_KEY_ENTER, MOFKEY_Z);
	input->AddKeyboardKey(INPUT_KEY_ATTACK, MOFKEY_Z);
	input->AddKeyboardKey(INPUT_KEY_CANCEL, MOFKEY_X);
	input->AddKeyboardKey(INPUT_KEY_JUMP, MOFKEY_X);
	input->AddKeyboardKey(INPUT_KEY_SKILL1, MOFKEY_F);
	input->AddKeyboardKey(INPUT_KEY_SKILL2, MOFKEY_A);
	input->AddKeyboardKey(INPUT_KEY_SKILL3, MOFKEY_S);
	input->AddKeyboardKey(INPUT_KEY_SKILL4, MOFKEY_D);
	input->AddKeyboardKey(INPUT_KEY_SKILL5, MOFKEY_Q);
	input->AddKeyboardKey(INPUT_KEY_SKILL6, MOFKEY_W);
	input->AddKeyboardKey(INPUT_KEY_SKILL7, MOFKEY_E);
	input->AddKeyboardKey(INPUT_KEY_SKILL8, MOFKEY_R);
	input->AddKeyboardKey(INPUT_KEY_ESCAPE, MOFKEY_SPACE);
	input->AddKeyboardKey(INPUT_KEY_RETRY, MOFKEY_F2);
	input->AddKeyboardKey(INPUT_KEY_BACK, MOFKEY_F3);
	//パッド入力登録
	input->AddLeftJoyStickHorizontal(INPUT_KEY_HORIZONTAL, 0);
	input->AddLeftJoyStickVertical(INPUT_KEY_VERTICAL, 0);
	input->AddJoypadKey(INPUT_KEY_ATTACK, 0, JOYPAD_X);
	input->AddJoypadKey(INPUT_KEY_ENTER, 0, JOYPAD_A);
	input->AddJoypadKey(INPUT_KEY_CANCEL, 0, JOYPAD_B);
	input->AddJoypadKey(INPUT_KEY_JUMP, 0, JOYPAD_A);
	input->AddJoypadKey(INPUT_KEY_SKILL1, 0, JOYPAD_B,
		std::vector<int>{JOYPAD_RB});
	input->AddJoypadKey(INPUT_KEY_SKILL2, 0, JOYPAD_Y, 
		std::vector<int>{JOYPAD_RB});
	input->AddJoypadKey(INPUT_KEY_SKILL3, 0, JOYPAD_X,
		std::vector<int>{JOYPAD_RB}, std::vector<std::string>{INPUT_KEY_ATTACK});
	input->AddJoypadKey(INPUT_KEY_SKILL4, 0, JOYPAD_A,
		std::vector<int>{JOYPAD_RB}, std::vector<std::string>{INPUT_KEY_JUMP});
	input->AddJoypadKey(INPUT_KEY_SKILL5, 0, JOYPAD_A,
		std::vector<int>{JOYPAD_LB}, std::vector<std::string>{INPUT_KEY_JUMP});
	input->AddJoypadKey(INPUT_KEY_SKILL6, 0, JOYPAD_Y,
		std::vector<int>{JOYPAD_LB});
	input->AddJoypadKey(INPUT_KEY_SKILL7, 0, JOYPAD_X,
		std::vector<int>{JOYPAD_LB}, std::vector<std::string>{INPUT_KEY_ATTACK});
	input->AddJoypadKey(INPUT_KEY_SKILL8, 0, JOYPAD_B,
		std::vector<int>{JOYPAD_LB}, std::vector<std::string>{INPUT_KEY_ESCAPE});
	input->AddJoypadKey(INPUT_KEY_ESCAPE, 0, JOYPAD_B);
	input->AddJoypadKey(INPUT_KEY_RETRY, 0, JOYPAD_START);
	input->AddJoypadKey(INPUT_KEY_BACK, 0, JOYPAD_BACK);


	//外部フォント読み込み
	if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) <= 0)
	{
		MessageBox(NULL, "読み込み失敗", "", MB_OK);
	}

	//音再生登録
	gSoundPlayer = std::make_shared<CSoundPlayer>();
	SoundPlayerService::SetService(gSoundPlayer);

	//シーン登録
	auto manager = std::make_shared<Scene::CSceneManager>();
	manager->RegistScene<Scene::CBattleScene>(SCENE_NO::GAME);
	manager->RegistScene<Scene::CTitleScene>(SCENE_NO::TITLE);

	//画面遷移用のサービス登録
	SceneChangeService::SetService(manager);
	SceneInitializeService::SetService(manager);
	gSceneManager = manager;

	//メッセンジャー登録
	auto messenger = std::make_shared < Messenger::CMessenger>();
	RegistMessageService::SetService(messenger);
	SendMessageService::SetService(messenger);


	gSceneManager->Initialize();
	//タイトルへ遷移
	gSceneManager->ChangeScene(SCENE_NO::TITLE);
	
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//キーの更新
	g_pInput->RefreshKey();

	//入力更新
	InputManagerInstance.Update();
	gSceneManager->Update();
	
	//再生し終わったサウンドを消す
	gSoundPlayer->DeleteFinishSound();

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f,0.0f,0.0f,0.0f,1.0f,0);

	g_pGraphics->SetDepthEnable(TRUE);

	gSceneManager->Render();

	//描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void){
	gSceneManager->Release();
	SceneChangeService::Release();
	SceneInitializeService::Release();
	SendMessageService::Release();
	RegistMessageService::Release();
	gSoundPlayer.reset();
	SoundPlayerService::Release();
	InputManagerInstance.Release();
	//外部フォント解放
	RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL);
	return TRUE;
}