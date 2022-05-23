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
	input->AddJoypadKey(INPUT_KEY_ATTACK, 0,0);

	std::shared_ptr<CMeshContainer> tempMesh = std::make_shared<CMeshContainer>();
	if (tempMesh->Load("chara.mom") != MOFMODEL_RESULT_SUCCEEDED)
	{
		return false;
	}
	Sample::ResourceManager<CMeshContainer>::GetInstance().AddResource("Player", tempMesh);

	tempMesh = std::make_shared<CMeshContainer>();
	if (tempMesh->Load("Enemy/Zombie/Zombie.mom") != MOFMODEL_RESULT_SUCCEEDED)
	{
		return false;
	}
	Sample::ResourceManager<CMeshContainer>::GetInstance().AddResource("Zombie", tempMesh);

	

	m_Player.SetInput(input);
	if (!m_Player.Load())
	{
		return false;
	}
	

	if (m_Stage.Load("Stage/stage.mom") != MOFMODEL_RESULT_SUCCEEDED)
	{
		return false;
	}

	
	

	tempMesh.reset();

	return true;
}

void CBattleScene::Initialize()
{
	m_Player.Initialize();
	m_Camera.Initialize();

	for (int i = 0; i < m_Enemys.size(); i++)
	{
		delete m_Enemys[i];
	}
	m_Enemys.clear();

	CEnemyBuilder zb;
	m_Enemys.push_back(zb.Create(Vector3(2, 0, 5)));
	m_Enemys.push_back(zb.Create(Vector3(2, 0, 1)));
	m_Enemys.push_back(zb.Create(Vector3(5, 0, 5)));
	m_Enemys.push_back(zb.Create(Vector3(6, 0, 1)));

	m_Light.SetDirection(Vector3(0.0f, -1.0f, 1.0f));
	CGraphicsUtilities::SetDirectionalLight(&m_Light);
}

void CBattleScene::Update()
{
	//入力更新
	InputManagerInstance.Update();
	m_Player.Update();
	for (int i = 0; i < m_Enemys.size(); i++)
	{
		m_Enemys[i]->Update();
	}
	ShotManagerInstance.Update();
	for (int i = 0; i < m_Enemys.size(); i++)
	{
		for (size_t j = 0; j < ShotManagerInstance.GetShotSize(); j++)
		{
			if (!ShotManagerInstance.GetShot(j)->IsShow() || ShotManagerInstance.GetShot(j)->IsHide())
			{
				continue;
			}
			if (m_Enemys[i]->GetCollider().CollisionSphere(ShotManagerInstance.GetShot(j)->GetCollider()))
			{
				m_Enemys[i]->Damage();
			}
		}
	}

	m_Camera.Update(m_Player.GetPosition(), m_Player.GetPosition());
}

void CBattleScene::Render()
{
	

	CMatrix44 stgMat;
	m_Stage.Render(stgMat);
	m_Player.Render();

	for (int i = 0; i < m_Enemys.size(); i++)
	{
		m_Enemys[i]->Render();
	}
	ShotManagerInstance.Render();
	
	


	
}

void CBattleScene::RenderDebug()
{
	
	for (int i = 0; i < ShotManagerInstance.GetShotSize(); i++)
	{
		if (!ShotManagerInstance.GetShot(i)->IsShow() || ShotManagerInstance.GetShot(i)->IsHide())
		{
			continue;
		}
		CGraphicsUtilities::RenderSphere(ShotManagerInstance.GetShot(i)->GetCollider(), Vector4(1, 0, 0, 0.2f));
	}
	
}

void CBattleScene::Render2D()
{
}

void CBattleScene::Render2DDebug()
{
	CGraphicsUtilities::RenderString(0, 0, "POS X:%.2f,Z:%.2f", m_Player.GetPosition().x, m_Player.GetPosition().z);
	CGraphicsUtilities::RenderString(0, 30, "VEL X:%.2f,Z:%.2f", m_Player.GetVelocity().x, m_Player.GetVelocity().z);

	CGraphicsUtilities::RenderString(0, 60, "%.2f", MOF_ToDegree(m_Player.GetRotate().y));
	CGraphicsUtilities::RenderString(0, 90, "%d", m_Player.IsReverse());
}

void CBattleScene::Release()
{
	m_Player.Release();
	m_Stage.Release();
	for (int i = 0; i < m_Enemys.size(); i++)
	{
		delete m_Enemys[i];
	}
	m_Enemys.clear();

	InputManagerInstance.Release();
	Sample::ResourceManager<CMeshContainer>::GetInstance().Release();
	ShotManagerInstance.Release();
}
