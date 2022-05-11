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
	
	//キーボード
	input->AddKeyboardKey(INPUT_KEY_HORIZONTAL, MOFKEY_RIGHT, MOFKEY_LEFT);
	input->AddKeyboardKey(INPUT_KEY_VERTICAL, MOFKEY_DOWN, MOFKEY_UP);
	input->AddKeyboardKey(INPUT_KEY_JUMP,MOFKEY_X);
	input->AddKeyboardKey(INPUT_KEY_ATTACK, MOFKEY_Z);
	//パッド
	input->AddJoyStickHorizontal(INPUT_KEY_HORIZONTAL, 0);
	input->AddJoyStickVertical(INPUT_KEY_VERTICAL, 0);
	input->AddJoypadKey(INPUT_KEY_ATTACK, 0,9);

	
	



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

	m_Light.SetDirection(Vector3(0.0f, -1.0f, 1.0f));
	CGraphicsUtilities::SetDirectionalLight(&m_Light);
}

void CBattleScene::Update()
{
	//入力更新
	InputManagerInstance.Update();
	m_Player.Update();

	m_Camera.Update(m_Player.GetPosition(), m_Player.GetPosition());
}

void CBattleScene::Render()
{
	g_pGraphics->SetDepthEnable(TRUE);

	m_Player.Render();
}

void CBattleScene::RenderDebug()
{
	CGraphicsUtilities::RenderString(0, 0, "%.2f", m_Player.GetPosition().z);
}

void CBattleScene::Release()
{
	m_Player.Release();
	m_PlayerMesh.Release();
	InputManagerInstance.Release();
	
}
