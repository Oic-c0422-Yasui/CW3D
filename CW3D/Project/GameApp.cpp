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

CSceneBase* gScene = NULL;

bool debugFlg = false;

float gameSpeed = 1.0f;
/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	CUtilities::SetCurrentDirectory("Resource");
	CUtilities::SetFPS(60);

	gScene = new CBattleScene;
	gScene->Load();
	gScene->Initialize();

	
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

	gScene->Update();

	if (g_pInput->IsKeyPush(MOFKEY_F2))
	{
		gameSpeed = 0.1f;
	}
	if (g_pInput->IsKeyPush(MOFKEY_F3))
	{
		gameSpeed = 1.0f;
	}
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

	gScene->Render();

	if (debugFlg)
	{
		gScene->RenderDebug();
	}

	g_pGraphics->SetDepthEnable(FALSE);

	gScene->Render2D();

	if (debugFlg)
	{
		gScene->Render2DDebug();
	}


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
	if (gScene)
	{
		gScene->Release();
		delete gScene;
		gScene = NULL;
	}
	return TRUE;
}