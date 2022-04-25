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

#include <unordered_map>
//なにかの型（入れるまで決まっていない）
template<typename T>
class MinResourceManager {
private:
	
	//シェアポインタを使いやすいように名前を付ける
	using ResourcePtr = std::shared_ptr<T>;
	//辞書のようなもの
	std::unordered_map<std::string, ResourcePtr> resources;

	MinResourceManager()
		: resources()
	{
	}
public:
	//
	void AddResource(const std::string& key, const ResourcePtr& ptr)
	{
		resources[key] = ptr;
	}

	ResourcePtr& GetResource(const std::string& key)
	{
		return resources[key];
	}

	static MinResourceManager& GetInstance() {
		static MinResourceManager obj;
		return obj;
	}
};

template<typename T>
T Add(T a, T b) {
	return a + b;
}
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
	gScene->Initialize();

	auto ans1 = Add<double>(2, 3);
	auto ans2 = Add(2.6f, 3.0f);
	auto ans3 = Add<std::string>("あした", "天気");

	using CTexturePtr = std::shared_ptr<CTexture>;
	CTexturePtr ap = std::make_shared<CTexture>();
	ap->Load("test.png");
	CTexturePtr bp = ap;
	CTexturePtr cp = ap;

	MinResourceManager<CTexture>::GetInstance().AddResource("gori", ap);

	MinResourceManager<CMeshContainer>::GetInstance().AddResource("gori", std::make_shared<CMeshContainer>());
	ap.reset();
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

	auto tex = MinResourceManager<CTexture>::GetInstance().GetResource("gori");
	auto mesh = MinResourceManager<CMeshContainer>::GetInstance().GetResource("gori");
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
		delete gScene;
		gScene = NULL;
	}
	return TRUE;
}