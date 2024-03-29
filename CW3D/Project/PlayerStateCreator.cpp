#include "PlayerStateCreator.h"
#include "GameDefine.h"
#include "IdleState.h"
#include "MoveState.h"
#include "RunState.h"
#include "IdleMotionState.h"
#include "Attack1State.h"
#include "Attack2State.h"
#include "Attack3State.h"
#include "RunAttack1State.h"
#include "RunAttack2State.h"
#include "ShockWaveSkillState.h"
#include "JumpState.h"
#include "FallState.h"
#include "LandingState.h"
#include "RunJumpState.h"
#include "RunFallState.h"
#include "RunLandingState.h"
#include "RunJumpAttack1State.h"
#include "RunJumpAttack2State.h"
#include "RunJumpAttack3State.h"
#include "JumpAttack1State.h"
#include "BeamSkillState.h"
#include "JumpBeamSkillState.h"
#include "StormSkillState.h"
#include "JumpStormSkillState.h"
#include "DamageState.h"
#include "FlyDamageState.h"
#include "DownState.h"
#include "DeadState.h"
#include "EscapeState.h"
#include "ClearPoseState.h"
#include "DropKickSkillState.h"
#include "StartPoseState.h"
#include "FlyHighSkillState.h"
#include "FireFlameSkillState.h"
#include "ImpactSkillState.h"
#include "ChaseSkillState.h"

bool ActionGame::PlayerStateCreator::Create(const StateMachinePtr& stateMachine, const ActorPtr& actor, const Input::InputPtr& input)
{
	//TODO:Jsonにパラメータを書き出す

	//待機
	stateMachine->AddState(CState::Create<CIdleState>(actor, input,
		CIdleState::Parameter{
			5.0f
		}));

	//待機モーション
	stateMachine->AddState(CState::Create<CIdleMotionState>(actor, input));
	//移動
	stateMachine->AddState(CState::Create<CMoveState>(actor, input));
	//ジャンプ
	stateMachine->AddState(CState::Create<CJumpState>(actor, input));
	//落下
	stateMachine->AddState(CState::Create<CFallState>(actor, input));
	//着地
	stateMachine->AddState(CState::Create<CLandingState>(actor, input));
	//ダッシュ
	stateMachine->AddState(CState::Create<CRunState>(actor, input));
	//ダッシュジャンプ
	stateMachine->AddState(CState::Create<CRunJumpState>(actor, input));
	//ダッシュ落下
	stateMachine->AddState(CState::Create<CRunFallState>(actor, input));
	//ダッシュ着地
	stateMachine->AddState(CState::Create<CRunLandingState>(actor, input));
	//ダメージ
	stateMachine->AddState(CState::Create<CDamageState>(actor, input,
		CDamageState::Parameter{
			4
		}));
	//空中ダメージ
	stateMachine->AddState(CState::Create<CFlyDamageState>(actor, input));
	//死亡
	stateMachine->AddState(CState::Create<CDeadState>(actor, input));
	//ダウン
	stateMachine->AddState(CState::Create<CDownState>(actor, input,
		CDownState::Parameter{
			1.0f
		}));

	//ダメージエフェクト
	auto damageEffect = std::make_shared<EffectCreateParameter>(
		EffectCreateParameter{ "DamageEffect1", Vector3(0, 1.0f, 0) , Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f),1.0f,actor->GetType()});
	//攻撃１
	stateMachine->AddState(CState::Create<CAttack1State>(actor, input,
		CAttack1State::Parameter{
			2
			,GameFrameTime * 20.0f
			,GameFrameTime * 25.0f
			,GameFrameTime * 32.0f
			,ShotAABB{ Vector3(0.7f, 0.7f, 0), 1.5f, 0, Vector3(0.3f, 0.0f, 0.0f),false,actor->GetType(), nullptr ,2,2.5f,0,damageEffect,GravityScale(),Vector3(1.2f, 1.5f, 1.0f) }
			,EffectCreateParameter{ "AttackEffect2", Vector3(0.8f,0.8f,0), Vector3(0.5f, 0.8f, 0.0f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),1.5f,actor->GetType() }
			

		}));

	//攻撃２
	stateMachine->AddState(CState::Create<CAttack2State>(actor, input,
		CAttack2State::Parameter{
			2
			,GameFrameTime * 10.0f
			,GameFrameTime * 25.0f
			,ShotAABB{ Vector3(0.7f, 0.7f, 0), 1.0f, 0, Vector3(0.2f, 0.0f, 0.0f),false,actor->GetType(), nullptr,2,2.5f,0,damageEffect,GravityScale(), Vector3(1.2f, 1.5f, 1.0f) }
			,EffectCreateParameter{ "AttackEffect2", Vector3(0.8f,0.8f,0), Vector3(0.5f, 0.8f, 0.0f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),1.5f,actor->GetType() }

		}));

	//攻撃３
	auto targetGravity = GravityScale{true,1.0f,0.1f,1.0f};
	stateMachine->AddState(CState::Create<CAttack3State>(actor, input,
		CAttack3State::Parameter{
			2
			,GameFrameTime * 10.0f
			,GameFrameTime * 25.0f
			,ShotAABB{ Vector3(0.7f, 0.7f, 0), 0.15f, 15, Vector3(0.3f, 0.2f, 0.0f),false,actor->GetType(), nullptr,2,3.5f,0,damageEffect,targetGravity, Vector3(1.5f, 2.5f, 1.5f)}

		}));

	//ダッシュ攻撃１
	stateMachine->AddState(CState::Create<CRunAttack1State>(actor, input,
		CRunAttack1State::Parameter{
			2
			,GameFrameTime * 10.0f
			,GameFrameTime * 30.0f
			,ShotAABB{ Vector3(0.7f, 0.8f, 0), 0.5f, 0, Vector3(0.6f, 0.0f, 0.0f),false,actor->GetType(), nullptr,2,3.0f,0,damageEffect,GravityScale(), Vector3(1.7f, 1.5f, 0.8f) }
			,EffectCreateParameter{ "AttackEffect2", Vector3(0.8f, 1.0f, 0), Vector3(0.6f, 0.4f, 0.0f), Vector3(0.0f, MOF_ToRadian(360.0f), 0.0f),2.1f,actor->GetType() }

		}));

	//ダッシュ攻撃２
	stateMachine->AddState(CState::Create<CRunAttack2State>(actor, input,
		CRunAttack2State::Parameter{
			2
			,GameFrameTime * 20.0f
			,GameFrameTime * 32.0f
			,ShotAABB{ Vector3(0.7f, 0.7f, 0), 1.5f, 0, Vector3(0.3f, 0.0f, 0.0f),false,actor->GetType(), nullptr ,1,2.5f,0,damageEffect,GravityScale(),Vector3(1.2f, 1.5f, 1.0f) }
			,EffectCreateParameter{ "AttackEffect2", Vector3(0.8f,0.8f,0), Vector3(0.5f, 0.8f, 0.0f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),1.5f,actor->GetType() }

		}));

	//ジャンプ攻撃１
	targetGravity = GravityScale{ true,0.5f,0.1f,1.0f };
	auto selfGravity = GravityScale{ true,0.5f,0.05f,1.0f };
	stateMachine->AddState(CState::Create<CJumpAttack1State>(actor, input,
		CJumpAttack1State::Parameter{
			2
			,GameFrameTime * 10.0f
			,GameFrameTime * 30.0f
			,GameFrameTime * 20.0f
			,GameFrameTime * 30.0f
			,selfGravity
			,ShotAABB{ Vector3(0.7f, 0.8f, 0), 10.0f, 0, Vector3(0.1f, 0.25f, 0.0f),false,actor->GetType(), nullptr,2,2.0f,0,damageEffect,targetGravity, Vector3(1.0f, 1.2f, 1.0f) }
			,EffectCreateParameter{ "AttackEffect2", Vector3(0.8f,1.0f,0), Vector3(0.3f, 0.4f, 0.0f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),2.0f,actor->GetType() }

		}));

	//空中ダッシュ攻撃１
	stateMachine->AddState(CState::Create<CRunJumpAttack1State>(actor, input,
		CRunJumpAttack1State::Parameter{
			2
			,GameFrameTime * 15.0f
			,GameFrameTime * 22.0f
			,selfGravity
			,ShotAABB{ Vector3(0.8f, 0.7f, 0), 10.0f, 0, Vector3(0.35f, 0.2f, 0.0f),false,actor->GetType(), nullptr,2,2.0f,0,damageEffect,targetGravity, Vector3(1.5f, 1.5f, 1.5f) }
			,EffectCreateParameter{ "AttackEffect2", Vector3(0.8f,0.8f,0), Vector3(0.8f, 0.8f,0.8f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),1.5f,actor->GetType() }

		}));

	//空中ダッシュ攻撃２ステート
	stateMachine->AddState(CState::Create<CRunJumpAttack2State>(actor, input,
		CRunJumpAttack2State::Parameter{
			2
			,GameFrameTime * 20.0f
			,selfGravity
			,ShotAABB{ Vector3(0.7f, 0.7f, 0), 10.0f, 0, Vector3(0.35f, 0.2f, 0.0f),true,actor->GetType(), nullptr,2,2.0f,0,damageEffect,targetGravity, Vector3(1.5f, 1.5f, 1.5f) }

		}));

	//空中ダッシュ攻撃３ステート
	selfGravity = GravityScale{ true,1.0f,0.05f,1.0f };
	stateMachine->AddState(CState::Create<CRunJumpAttack3State>(actor, input,
		CRunJumpAttack3State::Parameter{
			2
			,GameFrameTime * 12.0f
			,GameFrameTime * 40.0f
			,selfGravity
			,ShotAABB{ Vector3(0.7f, 1.2f, 0), 0.3f, 0, Vector3(0.45f, 0.2f, 0.0f),true,actor->GetType(), nullptr,2,3.5f,0,damageEffect,targetGravity, Vector3(1.5f, 2.0f, 1.5f) }

		}));

	//衝撃波スキルステート
	stateMachine->AddState(CState::Create<CShockWaveSkillState>(actor, input,
		CShockWaveSkillState::Parameter{
			4
			,GameFrameTime * 40.0f
			,GameFrameTime * 80.0f
			,ShotAABB{ Vector3(5.0f, 0.7f, 0), 0.05f, 0, Vector3(0.35f, 0.15f, -0.3f),false,actor->GetType(), nullptr,5,0.0f,0,nullptr,GravityScale(), Vector3(7.0f, 10.0f, 7.0f) }
			,EffectCreateParameter{ "SkillEffect1", Vector3(0.8f, -1.5f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, MOF_ToRadian(90), 0.0f),1.8f,actor->GetType() }

		}));

	//ビームスキルステート
	stateMachine->AddState(CState::Create<CBeamSkillState>(actor, input,
		CBeamSkillState::Parameter{
			3
			,GameFrameTime * 15.0f
			,GameFrameTime * 25.0f
			,ShotAABB{ Vector3(6.0f, 0.7f, 0), 0.0f, 0, Vector3(0.05f, 0.2f, 0.0f),false,actor->GetType(), nullptr,2,0.2f,0,damageEffect,GravityScale(), Vector3(5.0f, 2.0f, 2.0f) }
			,ShotOBB{ Vector3(1.0f, 2.0f, 0), 0.0f, 0, Vector3(0.05f, 0.2f, 0.0f),false,actor->GetType(), nullptr,2,0.2f,0,damageEffect,GravityScale(), Vector3(5.0f, 2.0f, 2.0f), Vector3(0, 0, MOF_ToRadian(30))}
			,EffectCreateParameter{ "SkillEffect2", Vector3(1.7f, 1.2f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, MOF_ToRadian(90), 0.0f),1.2f,actor->GetType() }

		}));

	//空中ビームスキルステート
	stateMachine->AddState(CState::Create<CJumpBeamSkillState>(actor, input,
		CJumpBeamSkillState::Parameter{
			3
			,GameFrameTime * 15.0f
			,GameFrameTime * 25.0f
			,ShotAABB{ Vector3(6.0f, 0.7f, 0), 0.0f, 0, Vector3(0.05f, 0.2f, 0.0f),false,actor->GetType(), nullptr,2,0.2f,0,damageEffect,GravityScale(), Vector3(5.0f, 2.0f, 2.0f) }
			,ShotOBB{ Vector3(2.0f, 1.4f, 0), 0.0f, 0, Vector3(0.05f, 0.2f, 0.0f),false,actor->GetType(), nullptr,2,0.2f,0,damageEffect,GravityScale(), Vector3(5.0f, 2.0f, 2.0f),Vector3(0, 0, MOF_ToRadian(-30)) }
			,EffectCreateParameter{ "SkillEffect2", Vector3(1.7f, 1.2f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, MOF_ToRadian(90), 0.0f),1.2f,actor->GetType() }

		}));

	//竜巻スキルステート
	targetGravity = GravityScale{ true,1.0f,0.0f,1.0f };
	stateMachine->AddState(CState::Create<CStormSkillState>(actor, input,
		CStormSkillState::Parameter{
			3
			,GameFrameTime * 7.0f
			,3.5f
			,1.0f
			,ShotAABB{ Vector3(0.0f, 0.0f, 0), 0.25f, 0, Vector3(0.6f, 0.1f, 0.6f),false,actor->GetType(), nullptr,3,0.2f,0,damageEffect,targetGravity, Vector3(4.0f, 8.0f, 4.0f) }
			,EffectCreateParameter{ "SkillEffect3", Vector3(0, 0, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0, 0.0f),1.8f,actor->GetType() }

		}));

	//空中竜巻スキルステート
	stateMachine->AddState(CState::Create<CJumpStormSkillState>(actor, input,
		CJumpStormSkillState::Parameter{
			3
			,GameFrameTime * 7.0f
			,3.5f
			,1.0f
			,ShotAABB{ Vector3(0.0f, 0.0f, 0), 0.25f, 0, Vector3(0.6f, 0.2f, 0.6f),false,actor->GetType(),nullptr,3,0.2f,0,damageEffect,targetGravity, Vector3(4.0f, 8.0f, 4.0f) }
			,EffectCreateParameter{ "SkillEffect3", Vector3(0, -1.5f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0, 0.0f),1.8f,actor->GetType() }

		}));

	//回避ステート
	stateMachine->AddState(CState::Create<CEscapeState>(actor, input,
		CEscapeState::Parameter{
			2
			,GameFrameTime * 5.0f
			,GameFrameTime * 25.0f
			,GameFrameTime * 10.0f
			,GameFrameTime * 0.0f
			,GameFrameTime * 7.0f
		}));

	//クリアポーズステート
	stateMachine->AddState(CState::Create<CClearPoseState>(actor, input));

	//開始ポーズステート
	stateMachine->AddState(CState::Create<CStartPoseState>(actor, input,
		CStartPoseState::Parameter{
			3.0
		}));
	
	//ドロップキックスキルステート
	targetGravity = GravityScale{ true,1.0f,0.3f,1.0f };
	selfGravity = GravityScale{ true,0.5f,0.1f,1.0f };
	stateMachine->AddState(CState::Create<CDropKickSkillState>(actor, input,
		CDropKickSkillState::Parameter{
			3
			,GameFrameTime * 5.0f
			,GameFrameTime * 30.0f
			,selfGravity
			,ShotAABB{ Vector3(1.0f, 0.7f, 0), 2.0f, 0, Vector3(0.7f, 0.32f, 0.0f),false,actor->GetType(), nullptr,3,1.0f,0,damageEffect,GravityScale(), Vector3(4.0f, 3.0f, 3.0f) }
			,EffectCreateParameter{ "SkillEffect5", Vector3(5.5f, 1.2f, 0), Vector3(0.3f, 0.3f, 0.3f), Vector3(0.0f, MOF_ToRadian(-90), 0.0f),1.8f,actor->GetType() }

		}));

	//超ジャンプスキルステート
	targetGravity = GravityScale{ true,1.0f,0.0f,1.0f };
	stateMachine->AddState(CState::Create<CFlyHighSkillState>(actor, input,
		CFlyHighSkillState::Parameter{
			2
			,GameFrameTime * 5.0f
			,GameFrameTime * 10.0f
			,GameFrameTime * 0.0f
			,GameFrameTime * 7.0f
			,ShotAABB{ Vector3(0.0f, -1.0f, 0), 2.5f, 0, Vector3(0.7f, 0.3f, 0.7f),false,actor->GetType(), nullptr,3,3.0f,0,damageEffect,targetGravity, Vector3(2.0f, 3.0f, 2.0f) }
			,EffectCreateParameter{ "SkillEffect4", Vector3(0, 1.2f, 0), Vector3(0.5f, 1.0f, 0.5f), Vector3(MOF_ToRadian(180), 0.0f, 0.0f),1.8f,actor->GetType() }
		}));
	//ファイアフレイムスキルステート
	targetGravity = GravityScale{ true,2.0f,0.005f,1.0f };
	stateMachine->AddState(CState::Create<CFireFlameSkillState>(actor, input,
		CFireFlameSkillState::Parameter{
			3
			,GameFrameTime * 30.0f
			,GameFrameTime * 5.0f
			,GameFrameTime * 20.0f
			,GameFrameTime * 25.0f
			,ShotAABB{ Vector3(0.0f, 0.0f, 0), 2.5f, 0, Vector3(0.2f, 0.28f, 0.2f),false,actor->GetType(), nullptr,5,0.0f,0,damageEffect,targetGravity, Vector3(5.0f, 5.0f, 5.0f) }
			,EffectCreateParameter{ "SkillEffect7_1", Vector3(0, -2.2f, 0), Vector3(0.5f, 0.5f, 0.5f), Vector3(MOF_ToRadian(180), 0.0f, 0.0f),1.8f,actor->GetType() }
			,EffectCreateParameter{ "SkillEffect7_2", Vector3(0, -2.2f, 0), Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f),1.2f,actor->GetType() }
		}));
	//インパクトスキルステート
	targetGravity = GravityScale{ true,2.5f,0.005f,1.0f };
	stateMachine->AddState(CState::Create<CImpactSkillState>(actor, input,
		CImpactSkillState::Parameter{
			3
			,GameFrameTime * 5.0f
			,GameFrameTime * 20.0f
			,GameFrameTime * 25.0f
			,ShotAABB{ Vector3(2.5f, 0.0f, 0), 2.5f, 0, Vector3(0.0f, 0.25f, 0.0f),false,actor->GetType(), nullptr,4,3.0f,0,damageEffect,targetGravity, Vector3(3.0f, 4.0f, 2.5f) }
			,EffectCreateParameter{ "SkillEffect8", Vector3(2.5f, 0, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f,MOF_ToRadian(-90), 0.0f),2.0f,actor->GetType() }
		}));
	//チェイススキルステート
	targetGravity = GravityScale{ true,0.5f,0.01f,1.0f };
	stateMachine->AddState(CState::Create<CChaseSkillState>(actor, input,
		CChaseSkillState::Parameter{
			3
			,GameFrameTime * 5.0f
			,GameFrameTime * 30.0f
			,ShotAABB{ Vector3(0.0f, 0.7f, 0), 0.05f, 0, Vector3(0.0f, 0.1f, 0.0f),false,actor->GetType(), nullptr,2,0.3f,0,damageEffect,targetGravity, Vector3(2.0f, 3.0f, 2.0f) }
			,EffectCreateParameter{ "SkillEffect3", Vector3(0.0f, 1.2f, 0), Vector3(0.1f, 0.1f, 0.1f), Vector3(0.0f, 0.0f, 0.0f),1.8f,actor->GetType() }
		}));

	return true;
}
