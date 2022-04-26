#include "BattleScene.h"

CBattleScene::CBattleScene()
{
}

CBattleScene::~CBattleScene()
{
}

bool CBattleScene::Load()
{
	auto input = InputManagerInstance.AddInput<Sample::MofInput>();
	input->AddKeyboardKey(KEY_HORIZONTAL, MOFKEY_RIGHT, MOFKEY_LEFT);
	input->AddKeyboardKey(KEY_VERTICAL, MOFKEY_UP, MOFKEY_DOWN);
	input->AddKeyboardKey(KEY_JUMP,MOFKEY_X);


	



	if (m_PlayerMesh.Load("chara.mom") != MOFMODEL_RESULT_SUCCEEDED)
	{
		return false;
	}
	m_Player.SetInput(input);
	m_Player.Load(&m_PlayerMesh);



	return true;
}

void CBattleScene::Initialize()
{
	m_Player.Initialize();
	m_Camera.Initialize();
}

void CBattleScene::Update()
{
	//“ü—ÍXV
	InputManagerInstance.Update();
	m_Player.Update();

	m_Camera.Update(m_Player.GetPosition(), m_Player.GetPosition());
}

void CBattleScene::Render()
{
	g_pGraphics->SetDepthEnable(TRUE);

	m_Player.Render();
}

void CBattleScene::Release()
{
	m_Player.Release();
	m_PlayerMesh.Release();
	InputManagerInstance.Release();
	
}
