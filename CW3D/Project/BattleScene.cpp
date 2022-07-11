#include "BattleScene.h"
#include "HPPresenter.h"
#include	"SkillPresenter.h"

#include	"CollisionEnemyEnemy.h"
#include	"CollisionPlayerEnemy.h"
#include	"CollisionShotEnemy.h"
#include	"CollisionShotPlayer.h"
#include	"CollisionObjectPlayer.h"
#include	"CollisionObjectEnemy.h"
#include	"NomalCamera.h"
#include	"StateInput.h"
#include	"ActorObjectManager.h"
#include	"Stage1.h"


using namespace Sample;


CBattleScene::CBattleScene()
	: m_Player(std::make_shared<CPlayer>())
	, m_GameClearFlg(false)
	, m_GameOverFlg(false)
{
}

CBattleScene::~CBattleScene()
{
}

bool CBattleScene::Load()
{
	//インプット読み込み
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
	input->AddKeyboardKey(INPUT_KEY_RETRY, MOFKEY_F2);
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
	if (!m_UICreater.Create())
	{
		return false;
	}

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
	effect = Effekseer::Effect::Create(EffectManagerInstance.GetManager(), u"Effect/Track.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResourceT("ClosedEffect", effect);

	//ステージ読み込み
	StagePtr stage = std::make_shared<CStage1>();
	m_StageManager.Load(stage);

	//プレイヤー読み込み
	m_Player->SetInput(input);
	if (!m_Player->Load())
	{
		return false;
	}
	//サービスロケーターの設定
	ServiceLocator<CPlayer>::SetService(m_Player);

	//プレイヤーUI読み込み
	m_PlayerUIRender = std::make_shared<CPlayerUIRender>();
	m_PlayerUIRender->Load();
	CHPPresenter::Present(m_Player, m_PlayerUIRender->GetHPRender());


	//敵読み込み
	auto stg = m_StageManager;
	for (int i = 0; i < stg.GetDivCount(); i++)
	{
		for (int j = 0; j < stg.GetDivEnemyCount(i); j++)
		{
			//ステージから敵のポインターを受け取る
			auto& ene = stg.GetEnemy(i, j);
			m_Enemys.push_back(ene);
			ene->Load();
		}
	}
	for (int i = 0; i < m_Enemys.size(); i++)
	{
		//敵をマネージャーに登録
		ActorObjectManagerInstance.Add(m_Enemys[i]);

		//敵のHPバー生成＆オブザーバーに登録
		m_EnemysHPRender.push_back(std::make_shared<CEnemyHPRender>());
		CHPPresenter::Present(m_Enemys[i], m_EnemysHPRender[i]);
	}

	
	//カメラ初期化
	CameraPtr camera = std::make_shared<CNomalCamera>(m_Player->GetPosition(), m_Player->GetPosition(),Vector3(0,0,0), Vector3(0, 0, 0));
	CameraControllerInstance.Load(camera);

	//プレイヤーをマネージャーに登録
	ActorObjectManagerInstance.Add(m_Player);
	

	m_Font.Create(225, "MS gosikku");

	tempMesh.reset();

	return true;
}

void CBattleScene::Initialize()
{
	EffectControllerInstance.Reset();

	m_Player->Initialize();
	m_PlayerUIRender->Initialize();

	for (auto& enemy : m_Enemys)
	{
		enemy->Initialize();
	}
	m_StageManager.Initialize();
	
	
	for (int i = 0; i < m_Enemys.size(); i++)
	{
		
		m_EnemysHPRender[i]->Initialize();
	}

	m_Light.SetDirection(Vector3(0.0f, -1.0f, 1.0f));
	CGraphicsUtilities::SetDirectionalLight(&m_Light);
	m_Light.SetAmbient(MOF_XRGB(255, 255, 255));
	m_Light.SetDiffuse(MOF_XRGB(220, 220, 220));
	m_Light.SetSpeculer(MOF_XRGB(255, 255, 255));

	m_GameClearFlg = false;
	m_GameOverFlg = false;

	ShotManagerInstance.Reset();
	CameraControllerInstance.SetDefault();
	TimeControllerInstance.Reset();

}

void CBattleScene::Update()
{
	//入力更新
	InputManagerInstance.Update();

	if (m_GameClearFlg || m_GameOverFlg)
	{
		//ゲームオーバーORクリア時、リトライ可能
		if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_RETRY))
		{
			Initialize();
			return;
		}
	}

	m_Player->Update();

	for (int i = 0; i < m_Enemys.size(); i++)
	{
		m_Enemys[i]->Update();
	}

	m_StageManager.Update();

	ShotManagerInstance.Update();

	if (!m_GameClearFlg && !m_GameOverFlg)
	{
		Collision();
	}
	int count = 0;
	for (auto enemy : m_Enemys)
	{
		if (!enemy->IsShow() && enemy->IsDead())
		{
			count++;
		}
	}
	if (count >= m_Enemys.size())
	{
		if (!m_GameClearFlg)
		{
			m_Player->SetClearPose();
			m_GameClearFlg = true;
		}
	}
	if (!m_Player->IsShow() && m_Player->IsDead())
	{
		m_GameOverFlg = true;
	}

	
	EffectManagerInstance.Update();
	EffectControllerInstance.Update();
	TimeControllerInstance.Update();
	CameraControllerInstance.Update(m_Player->GetPosition(), m_Player->GetPosition());

	ShotManagerInstance.Delete();
	EffectControllerInstance.Delete();
	ActorObjectManagerInstance.Delete();
}

void CBattleScene::Render()
{
	m_StageManager.Render();
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
	m_StageManager.RenderDebug();

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
	if (m_Player->IsEscape())
	{
		CGraphicsUtilities::RenderBox(m_Player->GetEscapeCollider(), Vector4(0, 0, 1, 0.2f));
	}

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

	//敵HPバーの描画入れ替え
	std::sort(m_EnemysHPRender.begin(), m_EnemysHPRender.end(),
		[](Sample::EnemyHPRenderPtr& obj1,Sample::EnemyHPRenderPtr& obj2)
	{
		return obj1->GetViewPosition().z > obj2->GetViewPosition().z;
	});
	for (auto& enemyHP : m_EnemysHPRender)
	{
		enemyHP->Render();
	}

	//プレイヤーのUI描画
	m_PlayerUIRender->Render();

	if (m_GameClearFlg || m_GameOverFlg)
	{
		CGraphicsUtilities::RenderString(20, 1000, "F2でリトライ");
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

	CGraphicsUtilities::RenderString(400, 0, "%.2f", TimeControllerInstance.GetTimeScale());
	Vector2 pos;
	g_pInput->GetMousePos(pos);
	CGraphicsUtilities::RenderString(400, 30, "X:%.1f Y:%.1f", pos.x, pos.y);
}

void CBattleScene::Release()
{
	m_StageManager.Release();
	m_Player->Release();
	m_Player.reset();

	ServiceLocator<CPlayer>::GetInstance().Release();

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
	m_PlayerUIRender.reset();
	

	InputManagerInstance.Release();
	Sample::ResourceManager<CMeshContainer>::GetInstance().Release();
	Sample::ResourceManager<Effekseer::EffectRef>::GetInstance().Release();
	Sample::ResourceManager<CSprite3D>::GetInstance().Release();
	Sample::ResourceManager<CTexture>::GetInstance().Release();
	ResourceManager<CFont>::GetInstance().Release();
	ShotManagerInstance.Release();
	EffectManagerInstance.Release();
	EffectControllerInstance.Release();
	IDManagerInstance.Release();
	TimeControllerInstance.Release();
	CameraControllerInstance.Release();
	ActorObjectManagerInstance.Release();
}

void CBattleScene::Collision()
{
	//敵の当たり判定
	for (int i = 0; i < m_Enemys.size(); i++)
	{
		//敵とプレイヤー
		CCollision::CollisionObj(m_Player, m_Enemys[i]);

		if (!m_Enemys[i]->IsInvincible())
		{
			for (int j = i + 1; j < m_Enemys.size(); j++)
			{
				//敵と敵
				CCollision::CollisionObj(m_Enemys[i], m_Enemys[j]);
			}
			for (size_t j = 0; j < ShotManagerInstance.GetShotSize(); j++)
			{
				//敵と弾
				auto& shot = ShotManagerInstance.GetShot(j);
				CCollision::CollisionObj(shot, m_Enemys[i]);
			}
		}
		for (int j = 0; j < m_StageManager.GetDivCount(); j++)
		{
			for (int k = 0; k < m_StageManager.GetDivObjCount(j); k++)
			{
				//敵とオブジェクト
				ObjectPtr obj = m_StageManager.GetObj(j, k);
				CCollision::CollisionObj(m_Enemys[i], obj);
			}
		}
	}

	//プレイヤーの当たり判定
	for (int i = 0; i < m_StageManager.GetDivCount(); i++)
	{
		for (int j = 0; j < m_StageManager.GetDivObjCount(i); j++)
		{
			//プレイヤーとオブジェクト
			ObjectPtr obj = m_StageManager.GetObj(i, j);
			CCollision::CollisionObj(m_Player, obj);
		}
	}

		for (size_t i = 0; i < ShotManagerInstance.GetShotSize(); i++)
		{
			//プレイヤーと弾
			auto& shot = ShotManagerInstance.GetShot(i);
			CCollision::CollisionObj(shot, m_Player);
		}

	
}