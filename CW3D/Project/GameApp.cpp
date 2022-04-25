/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"SceneBase.h"
#include	"BattleScene.h"

CSceneBase* gScene = NULL;

#include <unordered_map>
//�Ȃɂ��̌^�i�����܂Ō��܂��Ă��Ȃ��j
template<typename T>
class MinResourceManager {
private:
	
	//�V�F�A�|�C���^���g���₷���悤�ɖ��O��t����
	using ResourcePtr = std::shared_ptr<T>;
	//�����̂悤�Ȃ���
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
		@brief			�A�v���P�[�V�����̏�����
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	CUtilities::SetCurrentDirectory("Resource");
	CUtilities::SetFPS(60);

	gScene = new CBattleScene;
	gScene->Initialize();

	auto ans1 = Add<double>(2, 3);
	auto ans2 = Add(2.6f, 3.0f);
	auto ans3 = Add<std::string>("������", "�V�C");

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
		@brief			�A�v���P�[�V�����̍X�V
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//�L�[�̍X�V
	g_pInput->RefreshKey();

	auto tex = MinResourceManager<CTexture>::GetInstance().GetResource("gori");
	auto mesh = MinResourceManager<CMeshContainer>::GetInstance().GetResource("gori");
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̕`��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);


	//�`��̏I��
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̉��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void){
	if (gScene)
	{
		delete gScene;
		gScene = NULL;
	}
	return TRUE;
}