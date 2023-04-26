/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
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

//�V�[���}�l�[�W���[
Scene::SceneManagerPtr gSceneManager;

//�O���t�H���g
LPCSTR fontPath = "Font/Mplus1-Regular.ttf";


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
	auto input = InputManagerInstance.AddInput<Input::CMofInput>();
	InputManagerInstance.AddInput<Input::CStateInput>();
	//�L�[�{�[�h���͓o�^
	input->AddKeyboardKey(INPUT_KEY_HORIZONTAL, MOFKEY_RIGHT, MOFKEY_LEFT);
	input->AddKeyboardKey(INPUT_KEY_VERTICAL, MOFKEY_DOWN, MOFKEY_UP);
	input->AddKeyboardKey(INPUT_KEY_ENTER, MOFKEY_Z);
	input->AddKeyboardKey(INPUT_KEY_ATTACK, MOFKEY_Z);
	input->AddKeyboardKey(INPUT_KEY_CANCEL, MOFKEY_X);
	input->AddKeyboardKey(INPUT_KEY_JUMP, MOFKEY_X);
	input->AddKeyboardKey(INPUT_KEY_SKILL1, MOFKEY_D);
	input->AddKeyboardKey(INPUT_KEY_SKILL2, MOFKEY_A);
	input->AddKeyboardKey(INPUT_KEY_SKILL3, MOFKEY_S);
	input->AddKeyboardKey(INPUT_KEY_SKILL4, MOFKEY_F);
	input->AddKeyboardKey(INPUT_KEY_SKILL5, MOFKEY_Q);
	input->AddKeyboardKey(INPUT_KEY_ESCAPE, MOFKEY_SPACE);
	input->AddKeyboardKey(INPUT_KEY_RETRY, MOFKEY_F2);
	input->AddKeyboardKey(INPUT_KEY_BACK, MOFKEY_F3);
	//�p�b�h���͓o�^
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
	input->AddJoypadKey(INPUT_KEY_ESCAPE, 0, JOYPAD_B);
	input->AddJoypadKey(INPUT_KEY_RETRY, 0, JOYPAD_START);
	input->AddJoypadKey(INPUT_KEY_BACK, 0, JOYPAD_BACK);


	//�O���t�H���g�ǂݍ���
	if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) <= 0)
	{
		MessageBox(NULL, "�ǂݍ��ݎ��s", "", MB_OK);
	}

	//�V�[���o�^
	auto manager = std::make_shared<Scene::CSceneManager>();
	manager->RegistScene<Scene::CBattleScene>(SCENENO::GAME);
	manager->RegistScene<Scene::CTitleScene>(SCENENO::TITLE);

	//��ʑJ�ڗp�̃T�[�r�X�o�^
	SceneChangeService::SetService(manager);
	SceneInitializeService::SetService(manager);
	gSceneManager = manager;

	//���b�Z���W���[�o�^
	auto messenger = std::make_shared < Messenger::CMessenger>();
	RegistMessageService::SetService(messenger);
	SendMessageService::SetService(messenger);


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
	g_pGraphics->ClearTarget(0.0f,0.0f,0.0f,0.0f,1.0f,0);

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
	SceneChangeService::Release();
	SceneInitializeService::Release();
	SendMessageService::Release();
	RegistMessageService::Release();
	gSceneManager->Release();
	//�O���t�H���g���
	RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL);
	return TRUE;
}