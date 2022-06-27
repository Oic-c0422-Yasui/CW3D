#include "BattleScene.h"
#include "HPPresenter.h"
#include	"SkillPresenter.h"

#include	"CollisionEnemyEnemy.h"
#include	"CollisionPlayerEnemy.h"
#include	"CollisionShotEnemy.h"
#include	"CollisionShotPlayer.h"
#include	"NomalCamera.h"
#include	"StateInput.h"


using namespace Sample;

CBattleScene::CBattleScene()
	: m_Player(std::make_shared<CPlayer>())
{
}

CBattleScene::~CBattleScene()
{
}

bool CBattleScene::Load()
{
	auto input = InputManagerInstance.AddInput<Sample::MofInput>();
	InputManagerInstance.AddInput<Sample::StateInput>();
	
	//キーボード
	input->AddKeyboardKey(INPUT_KEY_HORIZONTAL, MOFKEY_RIGHT, MOFKEY_LEFT);
	input->AddKeyboardKey(INPUT_KEY_VERTICAL, MOFKEY_DOWN, MOFKEY_UP);
	input->AddKeyboardKey(INPUT_KEY_JUMP,MOFKEY_X);
	input->AddKeyboardKey(INPUT_KEY_ATTACK, MOFKEY_Z);
	input->AddKeyboardKey(INPUT_KEY_SKILL1, MOFKEY_D);
	input->AddKeyboardKey(INPUT_KEY_SKILL2, MOFKEY_A);
	input->AddKeyboardKey(INPUT_KEY_SKILL3, MOFKEY_S);
	input->AddKeyboardKey(INPUT_KEY_ESCAPE, MOFKEY_SPACE);
	//パッド
	input->AddJoyStickHorizontal(INPUT_KEY_HORIZONTAL, 0);
	input->AddJoyStickVertical(INPUT_KEY_VERTICAL, 0);
	input->AddJoypadKey(INPUT_KEY_ATTACK, 0,0);

	//メッシュ読み込み
	std::shared_ptr<CMeshContainer> tempMesh = std::make_shared<CMeshContainer>();
	if (tempMesh->Load("chara.mom") != MOFMODEL_RESULT_SUCCEEDED)
	{
		return false;
	}
	ResourceManager<CMeshContainer>::GetInstance().AddResource("Player", tempMesh);

	tempMesh = std::make_shared<CMeshContainer>();
	if (tempMesh->Load("Enemy/Zombie/Zombie.mom") != MOFMODEL_RESULT_SUCCEEDED)
	{
		return false;
	}
	ResourceManager<CMeshContainer>::GetInstance().AddResource("Zombie", tempMesh);


	//テクスチャ読み込み
	std::shared_ptr<CSprite3D> tempTex = std::make_shared<CSprite3D>();
	if (!tempTex->CreateSprite("UI/HP.png"))
	{
		return false;
	}
	ResourceManager<CSprite3D>::GetInstance().AddResource("HPBar", tempTex);
	tempTex = std::make_shared<CSprite3D>();
	if (!tempTex->CreateSprite("UI/HPFrame.png"))
	{
		return false;
	}
	ResourceManager<CSprite3D>::GetInstance().AddResource("HPFrame", tempTex);
	tempTex = std::make_shared<CSprite3D>();
	if (!tempTex->CreateSprite("UI/Damage.png"))
	{
		return false;
	}
	ResourceManager<CSprite3D>::GetInstance().AddResource("DamageBar", tempTex);
	
	std::shared_ptr<CTexture> tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/Skill1.png"))
	{
		return false;
	}
	ResourceManager<CTexture>::GetInstance().AddResource("Skill1", tempTex2D);
	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/Skill2.png"))
	{
		return false;
	}
	ResourceManager<CTexture>::GetInstance().AddResource("Skill2", tempTex2D);
	tempTex2D = std::make_shared<CTexture>();
	if (!tempTex2D->Load("UI/Skill3.png"))
	{
		return false;
	}
	ResourceManager<CTexture>::GetInstance().AddResource("Skill3", tempTex2D);

	//エフェクト読み込み
	EffectManagerInstance.Set();
	Effekseer::EffectRef effect = Effekseer::Effect::Create(EffectManagerInstance.GetManager(), u"Effect/Laser01.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResourceT("Effect1", effect);
	effect = Effekseer::Effect::Create(EffectManagerInstance.GetManager(), u"Effect/sword.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResourceT("DamageEffect1", effect);
	effect = Effekseer::Effect::Create(EffectManagerInstance.GetManager(), u"Effect/tuki.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResourceT("Effect2", effect);
	effect = Effekseer::Effect::Create(EffectManagerInstance.GetManager(), u"Effect/sandStome.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResourceT("Effect3", effect);
	effect = Effekseer::Effect::Create(EffectManagerInstance.GetManager(), u"Effect/Laser01.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResourceT("Effect4", effect);
	effect = Effekseer::Effect::Create(EffectManagerInstance.GetManager(), u"Effect/tornade.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResourceT("Effect5", effect);
	effect = Effekseer::Effect::Create(EffectManagerInstance.GetManager(), u"Effect/fire.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResourceT("Effect6", effect);




	//プレイヤー読み込み
	m_Player->SetInput(input);
	if (!m_Player->Load())
	{
		return false;
	}
	for (int i = 0; i < 3; i++)
	{
		m_SkillCTRender.push_back(std::make_shared<SkillUIRender>());
		CSkillPresenter::Present(m_Player, m_SkillCTRender[i], i);
	}
	m_SkillCTRender[0]->Initialize("Skill1");
	m_SkillCTRender[1]->Initialize("Skill2");
	m_SkillCTRender[2]->Initialize("Skill3");



	
	//ステージ読み込み
	if (m_Stage.Load("Stage/stage.mom") != MOFMODEL_RESULT_SUCCEEDED)
	{
		return false;
	}

	
	CameraPtr camera = std::make_shared<CNomalCamera>(m_Player->GetPosition(), m_Player->GetPosition(),Vector3(0,0,0), Vector3(0, 0, 0));

	CameraControllerInstance.Load(camera);

	ServiceLocator<CPlayer>::SetService(m_Player);

	tempTex.reset();
	tempMesh.reset();
	tempTex2D.reset();

	return true;
}

void CBattleScene::Initialize()
{
	m_Player->Initialize();

	for (int i = 0; i < m_Enemys.size(); i++)
	{
		m_Enemys[i].reset();
	}
	m_Enemys.clear();

	CEnemyBuilder zb;
	m_Enemys.push_back(zb.Create(Vector3(2, 0, 5)));
	m_Enemys.push_back(zb.Create(Vector3(2, 0, 1)));
	m_Enemys.push_back(zb.Create(Vector3(5, 0, 5)));
	m_Enemys.push_back(zb.Create(Vector3(6, 0, 1)));
	m_Enemys.push_back(zb.Create(Vector3(7, 0, 2)));
	m_Enemys.push_back(zb.Create(Vector3(1, 0, 3)));
	m_Enemys.push_back(zb.Create(Vector3(-2, 0, 4)));

	//敵のHPバー生成＆オブザーバーに登録
	for (int i = 0; i < m_Enemys.size(); i++)
	{
		m_EnemysHPRender.push_back(std::make_shared<Sample::EnemyHPRender>());

		CHPPresenter::Present(m_Enemys[i], m_EnemysHPRender[i]);
		m_EnemysHPRender[i]->Initialize();
	}

	m_Light.SetDirection(Vector3(0.0f, -1.0f, 1.0f));
	CGraphicsUtilities::SetDirectionalLight(&m_Light);
	m_Light.SetAmbient(MOF_XRGB(255, 255, 255));
	m_Light.SetDiffuse(MOF_XRGB(220, 220, 220));
	m_Light.SetSpeculer(MOF_XRGB(255, 255, 255));

	m_Font.Create(225, "MS gosikku");
}

void CBattleScene::Update()
{
	//入力更新
	InputManagerInstance.Update();
	m_Player->Update();
	for (int i = 0; i < m_Enemys.size(); i++)
	{
		m_Enemys[i]->Update();
	}
	ShotManagerInstance.Update();

	for (int i = 0; i < m_Enemys.size(); i++)
	{
		CCollision::CollisionObj(m_Player, m_Enemys[i]);
		/*for (int j = i + 1; j < m_Enemys.size(); j++)
		{
			CCollision::CollisionObj(m_Enemys[i], m_Enemys[j]);
		}*/
		if (m_Enemys[i]->IsInvincible())
		{
			continue;
		}
		for (size_t j = 0; j < ShotManagerInstance.GetShotSize(); j++)
		{
			auto& shot = ShotManagerInstance.GetShot(j);
			CCollision::CollisionObj(shot, m_Enemys[i]);
		}
	}
	for (size_t i = 0; i < ShotManagerInstance.GetShotSize(); i++)
	{
		auto& shot = ShotManagerInstance.GetShot(i);
		CCollision::CollisionObj(shot, m_Player);
	}
	EffectManagerInstance.Update();
	EffectControllerInstance.Update();
	TimeControllerInstance.Update();
	CameraControllerInstance.Update(m_Player->GetPosition(), m_Player->GetPosition());

	ShotManagerInstance.Delete();
	EffectControllerInstance.Delete();

}

void CBattleScene::Render()
{
	

	CMatrix44 stgMat;
	m_Stage.Render(stgMat);
	m_Player->Render();
	for (auto& enemy : m_Enemys)
	{
		enemy->Render();
	}
	ShotManagerInstance.Render();
	EffectManagerInstance.Render();
	
}

void CBattleScene::RenderDebug()
{
	
	for (size_t i = 0; i < ShotManagerInstance.GetShotSize(); i++)
	{
		if (!ShotManagerInstance.GetShot(i)->IsShow() || !ShotManagerInstance.GetShot(i)->GetCollideFlg())
		{
			continue;
		}
		switch (ShotManagerInstance.GetShot(i)->GetColliderType())
		{
		case COLLITION_SPHERE:
		{
			CGraphicsUtilities::RenderSphere(ShotManagerInstance.GetShot(i)->GetColliderSphere(), Vector4(1, 0, 0, 0.2f));
			break;
		}
		case COLLITION_AABB:
		{
			CGraphicsUtilities::RenderBox(ShotManagerInstance.GetShot(i)->GetColliderAABB(), Vector4(1, 0, 0, 0.2f));
			break;
		}
		default:
			break;
		}
	}

	CGraphicsUtilities::RenderBox(m_Player->GetCollider(), Vector4(0, 1, 0, 0.2f));

	for (int i = 0; i < m_Enemys.size(); i++)
	{
		CGraphicsUtilities::RenderBox(m_Enemys[i]->GetCollider(), Vector4(0, 1, 0, 0.2f));
	}
	
}

void CBattleScene::Render2D()
{
	for (int i = 0; i < m_Enemys.size(); i++)
	{
		m_Enemys[i]->Render2D();
	}
	float count = 0;
	for (int i = 0; i < m_Enemys.size(); i++)
	{
		if (!m_Enemys[i]->IsShow())
		{
			count++;
		}
	}

	//HPバーの描画入れ替え
	std::sort(m_EnemysHPRender.begin(), m_EnemysHPRender.end(),
		[](Sample::EnemyHPRenderPtr& obj1,Sample::EnemyHPRenderPtr& obj2)
	{
		return obj1->GetPosition().z > obj2->GetPosition().z;
	});
	for (auto& enemyHP : m_EnemysHPRender)
	{
		enemyHP->Render();
	}
	for (int i = 0;i < m_SkillCTRender.size();i++)
	{
		m_SkillCTRender[i]->Render(i * 150);
	}

	

	if (count >= m_Enemys.size())
	{
		CRectangle rect;
		m_Font.CalculateStringRect(0, 0, "全部倒したあああああ", rect);
		m_Font.RenderString(g_pGraphics->GetTargetWidth() * 0.5f - (rect.GetWidth() * 0.5f), g_pGraphics->GetTargetHeight() * 0.5f - (rect.GetHeight() * 0.5f), "全部倒したあああああ");
	}
}

void CBattleScene::Render2DDebug()
{
	CGraphicsUtilities::RenderString(0, 0, "POS X:%.2f,Z:%.2f", m_Player->GetPosition().x, m_Player->GetPosition().z);
	CGraphicsUtilities::RenderString(0, 30, "VEL X:%.2f,Z:%.2f", m_Player->GetVelocity().x, m_Player->GetVelocity().z);

	CGraphicsUtilities::RenderString(0, 60, "%.2f", MOF_ToDegree(m_Player->GetRotate().y));
	CGraphicsUtilities::RenderString(0, 90, "%d", m_Player->IsReverse());
	//m_Camera.Render2DDebug();

	CGraphicsUtilities::RenderString(400, 0, "%.2f", TimeControllerInstance.GetTimeScale());
	//for (int i = 0;i < m_EnemysHPRender.size();i++)
	//{
	//	//CGraphicsUtilities::RenderString(0, 500 + 30 * i, "PosZ:%.2f", m_EnemysHPRender[i]->GetPosition().z);
	//}
}

void CBattleScene::Release()
{
	m_Player->Release();
	m_Player.reset();
	ServiceLocator<CPlayer>::SetService(nullptr);
	ServiceLocator<CPlayer>::GetInstance().Release();
	m_Stage.Release();
	for (int i = 0; i < m_Enemys.size(); i++)
	{
		m_Enemys[i].reset();
	}
	m_Enemys.clear();
	for (int i = 0; i < m_EnemysHPRender.size(); i++)
	{
		m_EnemysHPRender[i].reset();
	}
	m_EnemysHPRender.clear();
	for (int i = 0; i < m_SkillCTRender.size(); i++)
	{
		m_SkillCTRender[i].reset();
	}
	m_SkillCTRender.clear();

	InputManagerInstance.Release();
	Sample::ResourceManager<CMeshContainer>::GetInstance().Release();
	Sample::ResourceManager<Effekseer::EffectRef>::GetInstance().Release();
	Sample::ResourceManager<CSprite3D>::GetInstance().Release();
	Sample::ResourceManager<CTexture>::GetInstance().Release();
	ShotManagerInstance.Release();
	EffectManagerInstance.Release();
	EffectControllerInstance.Release();
	IDManagerInstance.Release();
	TimeControllerInstance.Release();
	CameraControllerInstance.Release();
}
