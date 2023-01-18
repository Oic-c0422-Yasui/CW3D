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
#include	"SceneManager.h"
#include	"TitleScene.h"
#include	"MofInput.h"
#include	"StateInput.h"
#include	"Messenger.h"

//�V�[���}�l�[�W���[
ActionGame::SceneManagerPtr gSceneManager;

/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	CUtilities::SetCurrentDirectory("Resource");
	CUtilities::SetFPS(60);

	//�C���v�b�g�ǂݍ���
	auto input = InputManagerInstance.AddInput<ActionGame::MofInput>();
	InputManagerInstance.AddInput<ActionGame::StateInput>();
	//�L�[�{�[�h���͓o�^
	input->AddKeyboardKey(INPUT_KEY_HORIZONTAL, MOFKEY_RIGHT, MOFKEY_LEFT);
	input->AddKeyboardKey(INPUT_KEY_VERTICAL, MOFKEY_DOWN, MOFKEY_UP);
	input->AddKeyboardKey(INPUT_KEY_ENTER, MOFKEY_Z);
	input->AddKeyboardKey(INPUT_KEY_CANCEL, MOFKEY_X);
	input->AddKeyboardKey(INPUT_KEY_SKILL1, MOFKEY_D);
	input->AddKeyboardKey(INPUT_KEY_SKILL2, MOFKEY_A);
	input->AddKeyboardKey(INPUT_KEY_SKILL3, MOFKEY_S);
	input->AddKeyboardKey(INPUT_KEY_SKILL4, MOFKEY_F);
	input->AddKeyboardKey(INPUT_KEY_ESCAPE, MOFKEY_SPACE);
	input->AddKeyboardKey(INPUT_KEY_RETRY, MOFKEY_F2);
	input->AddKeyboardKey(INPUT_KEY_BACK, MOFKEY_F3);
	//�p�b�h���͓o�^
	input->AddJoyStickHorizontal(INPUT_KEY_HORIZONTAL, 0);
	input->AddJoyStickVertical(INPUT_KEY_VERTICAL, 0);
	input->AddJoypadKey(INPUT_KEY_ENTER, 0, 0);

	//�V�[���o�^
	auto manager = std::make_shared<ActionGame::SceneManager>();
	manager->RegistScene<ActionGame::CBattleScene>(SCENENO::GAME);
	manager->RegistScene<ActionGame::TitleScene>(SCENENO::TITLE);

	//��ʑJ�ڗp�̃T�[�r�X�o�^
	SceneChangeService::SetService(manager);
	SceneInitializeService::SetService(manager);
	gSceneManager = manager;

	//���b�Z���W���[�o�^
	auto messenger = std::make_shared < ActionGame::Messenger>();
	ActionGame::ServiceLocator<ActionGame::IMessenger>::SetService(messenger);


	gSceneManager->Initialize();
	//�^�C�g���֑J��
	gSceneManager->ChangeScene(SCENENO::TITLE);

	
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

	//���͍X�V
	InputManagerInstance.Update();

	gSceneManager->Update();

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

	g_pGraphics->SetDepthEnable(TRUE);

	gSceneManager->Render();


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
	InputManagerInstance.Release();
	gSceneManager->Release();
	gSceneManager.reset();
	ActionGame::ServiceLocator<ActionGame::ISceneChanger>::Release();
	ActionGame::ServiceLocator<ActionGame::ISceneInitializer>::Release();
	ActionGame::ServiceLocator<ActionGame::IMessenger>::Release();
	return TRUE;
}