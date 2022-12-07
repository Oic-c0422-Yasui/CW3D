/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"SceneBase.h"
#include	"BattleScene.h"
#include	"SceneManager.h"
#include	"TitleScene.h"


bool debugFlg = false;

//シーンマネージャー
ActionGame::SceneManagerPtr gSceneManager;

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
	auto input = InputManagerInstance.AddInput<ActionGame::MofInput>();
	InputManagerInstance.AddInput<ActionGame::StateInput>();
	//キーボード
	input->AddKeyboardKey(INPUT_KEY_HORIZONTAL, MOFKEY_RIGHT, MOFKEY_LEFT);
	input->AddKeyboardKey(INPUT_KEY_VERTICAL, MOFKEY_DOWN, MOFKEY_UP);
	input->AddKeyboardKey(INPUT_KEY_JUMP, MOFKEY_X);
	input->AddKeyboardKey(INPUT_KEY_ATTACK, MOFKEY_Z);
	input->AddKeyboardKey(INPUT_KEY_SKILL1, MOFKEY_D);
	input->AddKeyboardKey(INPUT_KEY_SKILL2, MOFKEY_A);
	input->AddKeyboardKey(INPUT_KEY_SKILL3, MOFKEY_S);
	input->AddKeyboardKey(INPUT_KEY_SKILL_DROPKICK, MOFKEY_F);
	input->AddKeyboardKey(INPUT_KEY_ESCAPE, MOFKEY_SPACE);
	input->AddKeyboardKey(INPUT_KEY_RETRY, MOFKEY_F2);
	//パッド
	input->AddJoyStickHorizontal(INPUT_KEY_HORIZONTAL, 0);
	input->AddJoyStickVertical(INPUT_KEY_VERTICAL, 0);
	input->AddJoypadKey(INPUT_KEY_ATTACK, 0, 0);

	//シーン登録
	auto manager = std::make_shared<ActionGame::SceneManager>();
	manager->RegistScene<ActionGame::CBattleScene>(SCENE_GAME);
	manager->RegistScene<ActionGame::CTitleScene>(SCENE_TITLE);

	//画面遷移用のサービス登録
	ActionGame::ServiceLocator<ActionGame::ISceneChanger>::SetService(manager);
	gSceneManager = manager;


	gSceneManager->ChangeScene(SCENE_TITLE);

	
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

	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		debugFlg = debugFlg ? false : true;
	}
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
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);

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
	InputManagerInstance.Release();
	gSceneManager->Release();
	gSceneManager.reset();
	ActionGame::ServiceLocator<ActionGame::ISceneChanger>::Release();
	return TRUE;
}