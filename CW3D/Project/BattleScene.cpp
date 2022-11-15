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
#include	"JsonStageLoader.h"	


using namespace Sample;


CBattleScene::CBattleScene()
	: m_Player(std::make_shared<CPlayer>())
	, m_Enemys(std::make_shared<EnemyArray>())
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
	input->AddKeyboardKey(INPUT_KEY_SKILL_DROPKICK, MOFKEY_F);
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
	ResourcePtrManager<CMeshContainer>::GetInstance().AddResource("Player", "Player", tempMesh);

	
	//テクスチャ読み込み
	if (!m_UICreater.Create())
	{
		return false;
	}

	//エフェクト読み込み
	EffectManagerInstance.Set();
	Effekseer::EffectRef effect = Effekseer::Effect::Create(EffectManagerInstance.GetManager(), u"Effect/Laser01.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "Effect1", effect);
	effect = Effekseer::Effect::Create(EffectManagerInstance.GetManager(), u"Effect/sword.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "DamageEffect1", effect);
	effect = Effekseer::Effect::Create(EffectManagerInstance.GetManager(), u"Effect/tuki.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "Effect2", effect);
	effect = Effekseer::Effect::Create(EffectManagerInstance.GetManager(), u"Effect/sandStome.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "Effect3", effect);
	effect = Effekseer::Effect::Create(EffectManagerInstance.GetManager(), u"Effect/Laser01.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "Effect4", effect);
	effect = Effekseer::Effect::Create(EffectManagerInstance.GetManager(), u"Effect/tornade.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "Effect5", effect);
	effect = Effekseer::Effect::Create(EffectManagerInstance.GetManager(), u"Effect/fire.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "Effect6", effect);
	effect = Effekseer::Effect::Create(EffectManagerInstance.GetManager(), u"Effect/drill.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "Effect7", effect);
	effect = Effekseer::Effect::Create(EffectManagerInstance.GetManager(), u"Effect/Track.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "ClosedEffect", effect);

	//ステージ情報読み込み
	JsonStageLoader stageLoader;
	stageLoader.Load("Text/Stage1.json");
	//ステージ読み込み
	StagePtr stage = std::make_shared<CStage1>();
	m_StageManager.Load(stage, stageLoader.GetDivisionArray());


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
	m_Timer.Start();

	m_StageManager.Initialize();

	m_Player->Initialize();
	m_PlayerUIRender->Initialize();

	//敵生成
	CreateEnemys();


	m_ClearTermProvider = std::make_shared<ClearTermProvider>(m_Enemys);
	
	//ライト設定
	m_Light.SetDirection(Vector3(0.0f, -1.0f, 1.0f));
	CGraphicsUtilities::SetDirectionalLight(&m_Light);
	m_Light.SetAmbient(MOF_XRGB(255, 255, 255));
	m_Light.SetDiffuse(MOF_XRGB(220, 220, 220));
	m_Light.SetSpeculer(MOF_XRGB(255, 255, 255));

	m_GameClearFlg = false;
	m_GameOverFlg = false;

	EffectControllerInstance.Reset();
	ShotManagerInstance.Reset();
	CameraControllerInstance.SetDefault();
	TimeScaleControllerInstance.Reset();

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

	m_Timer.Update();

	m_ClearTermProvider->SetDivisionTime(m_Timer.GetTime());

	//プレイヤー更新
	m_Player->Update();

	//敵更新
	for (auto& enemy : *m_Enemys)
	{
		enemy->Update();
	}

	//ステージの区画をクリアしているなら
	if (m_StageManager.GetCurrentDivision()->IsClear() && !m_GameClearFlg)
	{
		//次の区画へ
		m_StageManager.NextPhase();
		//敵を生成する
		CreateEnemys();
		//タイマーをリセット
		m_Timer.Start();
	}

	m_StageManager.Update(m_ClearTermProvider);

	
	if (!m_GameClearFlg && !m_GameOverFlg)
	{
		//当たり判定
		Collision();
	}

	//クリア判定
	if (m_StageManager.IsClear())
	{
		if (!m_GameClearFlg)
		{
			m_Player->SetClearPose();
			m_GameClearFlg = true;
		}
	}
	
	//死亡判定
	if (!m_Player->IsShow() && m_Player->IsDead())
	{
		m_GameOverFlg = true;
	}


	//エフェクトマネージャー更新
	EffectManagerInstance.Update();
	//エフェクト操作更新
	EffectControllerInstance.Update();
	//時間操作更新
	TimeScaleControllerInstance.Update();
	//カメラ操作更新
	CameraControllerInstance.Update(m_Player->GetPosition(), m_Player->GetPosition());

	//ショットマネージャー更新
	ShotManagerInstance.Update();
	//ショット削除処理
	ShotManagerInstance.Delete();
	EffectControllerInstance.Delete();
	ActorObjectManagerInstance.Delete();
}

void CBattleScene::Render()
{
	m_StageManager.Render();
	m_Player->Render();
	for (auto& enemy : *m_Enemys)
	{
		enemy->Render();
	}
	ShotManagerInstance.Render();
	EffectManagerInstance.Render();

}

void CBattleScene::RenderDebug()
{
	//ステージデバッグ描画
	m_StageManager.RenderDebug();

	//ショットデバッグ描画
	for (size_t i = 0; i < ShotManagerInstance.GetShotSize(); i++)
	{
		auto& shot = ShotManagerInstance.GetShot(i);

		if (!shot->IsShow() || !shot->GetCollideFlg())
		{
			continue;
		}
		switch (shot->GetColliderType())
		{
		case COLLISION_SPHERE:
		{
			CGraphicsUtilities::RenderLineSphere(shot->GetColliderSphere(), Vector4(1, 0, 0, 0.2f));
			break;
		}
		case COLLISION_AABB:
		{
			CGraphicsUtilities::RenderBox(shot->GetColliderAABB(), Vector4(1, 0, 0, 0.2f)); 
			break;
		}
		default:
			break;
		}
	}
	//プレイヤー当たり判定デバッグ描画
	CGraphicsUtilities::RenderBox(m_Player->GetCollider(), Vector4(0, 1, 0, 0.2f));
	//プレイヤー回避時当たり判定デバッグ描画
	if (m_Player->IsEscape())
	{
		CGraphicsUtilities::RenderBox(m_Player->GetEscapeCollider(), Vector4(0, 0, 1, 0.2f));
	}
	//敵当たり判定デバッグ描画
	for (auto& enemy : *m_Enemys)
	{
		CGraphicsUtilities::RenderBox(enemy->GetCollider(), Vector4(0, 1, 0, 0.2f));
	}
	
}

void CBattleScene::Render2D()
{

	//敵HPバーの描画入れ替え
	std::sort(m_EnemysHPRender.begin(), m_EnemysHPRender.end(),
		[](Sample::EnemyHPRenderPtr& obj1,Sample::EnemyHPRenderPtr& obj2)
	{
		return obj1->GetViewPosition().z > obj2->GetViewPosition().z;
	});

	//敵のHPバー描画
	for (auto& enemyHP : m_EnemysHPRender)
	{
		enemyHP->Render();
	}

	//プレイヤーのUI描画
	m_PlayerUIRender->Render();


	//リトライ描画
	if (m_GameClearFlg || m_GameOverFlg)
	{
		CGraphicsUtilities::RenderString(20, 1000, "F2でリトライ");
	}

	//ゲームクリア描画
	if (m_GameClearFlg)
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

	CGraphicsUtilities::RenderString(400, 0, "%.2f", TimeScaleControllerInstance.GetTimeScale());
	Vector2 pos;
	g_pInput->GetMousePos(pos);
	CGraphicsUtilities::RenderString(400, 30, "X:%.1f Y:%.1f", pos.x, pos.y);
}

void CBattleScene::Release()
{
	ActorObjectManagerInstance.Release();
	m_StageManager.Release();
	m_Player->Release();
	m_Player.reset();

	ServiceLocator<CPlayer>::GetInstance().Release();

	m_Enemys->clear();
	m_Enemys.reset();
	for (int i = 0; i < m_EnemysHPRender.size(); i++)
	{
		m_EnemysHPRender[i].reset();
	}
	m_EnemysHPRender.clear();
	m_PlayerUIRender.reset();
	

	InputManagerInstance.Release();
	Sample::ResourceManager<Effekseer::EffectRef>::GetInstance().Release();
	Sample::ResourcePtrManager<CMeshContainer>::GetInstance().Release();
	Sample::ResourcePtrManager<CSprite3D>::GetInstance().Release();
	Sample::ResourcePtrManager<CTexture>::GetInstance().Release();
	Sample::ResourcePtrManager<CFont>::GetInstance().Release();
	ShotManagerInstance.Release();
	EffectManagerInstance.Release();
	EffectControllerInstance.Release();
	IDManagerInstance.Release();
	TimeScaleControllerInstance.Release();
	CameraControllerInstance.Release();
}

void CBattleScene::Collision()
{
	//敵の当たり判定
	for (auto& enemy : *m_Enemys)
	{
		//敵とプレイヤー
		CCollision::CollisionObj(m_Player, enemy);

		if (!enemy->IsInvincible())
		{
			//for (int j = i + 1; j < m_Enemys.size(); j++)
			//{
			//	//敵と敵
			//	CCollision::CollisionObj(m_Enemys[i], m_Enemys[j]);
			//}
			//敵と弾
			for (int j = 0; j < ShotManagerInstance.GetShotSize(); j++)
			{
				ShotPtr shot = ShotManagerInstance.GetShot(j);
				CCollision::CollisionObj(shot, enemy);
			}
		}

		//敵とオブジェクト
		for (int j = 0; j < m_StageManager.GetCurrentDivision()->GetObjCount(); j++)
		{
			ObjectPtr obj = m_StageManager.GetCurrentDivision()->GetObj(j);
			CCollision::CollisionObj(enemy, obj);
		}
	}

	//プレイヤーとオブジェクトの当たり判定
	for (int i = 0; i < m_StageManager.GetCurrentDivision()->GetObjCount(); i++)
	{
		ObjectPtr obj = m_StageManager.GetCurrentDivision()->GetObj(i);
		CCollision::CollisionObj(m_Player, obj);
	}

	//プレイヤーと弾の当たり判定
	for (int i = 0; i < ShotManagerInstance.GetShotSize(); i++)
	{
		ShotPtr shot = ShotManagerInstance.GetShot(i);
		CCollision::CollisionObj(shot, m_Player);
	}

	
}

void CBattleScene::CreateEnemys()
{

	m_Enemys->clear();
	m_EnemysHPRender.clear();

	//現在の区画から敵の情報を受け取る
	auto division = m_StageManager.GetCurrentDivision();
	auto enemysParam = division->GetEnemysParam();
	int enemyCount = division->GetEnemyCount();

	//敵のビルダーの辞書
	EnemyBuilderDictionary dictionary;

	for (int i = 0; i < enemyCount; i++)
	{
		//敵のタイプに合ったビルダーを取得
		auto builder = dictionary.Get(enemysParam[i].GetParam().m_Type);


		m_Enemys->push_back(builder->Create(enemysParam[i]));

		//敵をマネージャーに登録
		ActorObjectManagerInstance.Add(m_Enemys->at(i));
		//敵のHPバー生成＆オブザーバーに登録
		m_EnemysHPRender.push_back(std::make_shared<CEnemyHPRender>());
		CHPPresenter::Present(m_Enemys->at(i), m_EnemysHPRender[i]);
		m_EnemysHPRender[i]->Initialize();
	}
}
