#include "PlayerActionCreator.h"
#include "GameDefine.h"
#include	"IdleAction.h"
#include	"MoveAction.h"
#include	"JumpAction.h"
#include	"FallAction.h"
#include	"LandingAction.h"
#include	"Attack1Action.h"
#include	"Attack2Action.h"
#include	"Attack3Action.h"

#include	"RunAction.h"
#include	"IdleMotionAction.h"

#include	"RunAttack1Action.h"
#include	"ShockWaveSkillAction.h"

#include	"RunJumpAction.h"
#include	"RunFallAction.h"
#include	"RunLandingAction.h"
#include	"RunJumpAttack1Action.h"
#include	"RunJumpAttack2Action.h"
#include	"RunJumpAttack3Action.h"
#include	"JumpAttack1Action.h"
#include	"BeamSkillAction.h"
#include	"JumpBeamSkillAction.h"
#include	"StormSkillAction.h"
#include	"NoneGravityAction.h"
#include	"FlyDamageAction.h"
#include	"DownAction.h"

#include	"DamageAction.h"
#include	"DeadAction.h"
#include	"EscapeAction.h"
#include	"ClearPoseAction.h"
#include	"DropKickSkillAction.h"
#include	"StartPoseAction.h"
#include	"MoveCompensationAction.h"



bool ActionGame::PlayerActionCreator::Create(const ActorPtr& actor)
{
	//TODO:Jsonにパラメータを書き出す

	//待機
	actor->AddAction(CAction::Create<CIdleAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_IDLE,
				0.0f,
				1.0f,
				0.25f,
				true
			}
		},
		CIdleAction::Parameter{
			
			Vector3(PLAYER_SPEED * 0.3f, 1.0f,PLAYER_SPEED * 0.3f),
			Vector3(PLAYER_SPEED, 1.0f,PLAYER_SPEED)
		}));
	//待機モーション
	actor->AddAction(CAction::Create<IdleMotionAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_IDLE_MOTION,
				0.0f,
				1.0f,
				0.3f,
				false
			}
		},
		IdleMotionAction::Parameter{
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED)
		}));
	//移動
	actor->AddAction(CAction::Create<CMoveAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_MOVE,
				0.0f,
				1.0f,
				0.1f,
				true
			}
		},
		CMoveAction::Parameter{
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
			GRAVITYMAX,
		}));
	//ダッシュ
	actor->AddAction(STATE_KEY_RUN, CAction::Create<CMoveAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_RUN,
				0.0f,
				1.0f,
				0.12f,
				true
			}
		},
		CMoveAction::Parameter{
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
			Vector3(PLAYER_MAXSPEED, 1.0f, PLAYER_MAXSPEED),
			GRAVITYMAX,
		}));
	//ジャンプ
	actor->AddAction(CAction::Create<CJumpAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_JUMP,
				0.3f,
				2.0f,
				0.1f,
				false
			}
		},
		CJumpAction::Parameter{
			Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
			GRAVITY,
			GRAVITYMAX,
			PLAYER_JUMPPOWER,
		}));
	//ダッシュジャンプ
	actor->AddAction(CAction::Create<CRunJumpAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_JUMP,
				0.3f,
				2.0f,
				0.1f,
				false
			}
		},
		CMoveAction::Parameter{
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
			Vector3(PLAYER_SPEED, PLAYER_JUMPPOWER, PLAYER_SPEED),
			Vector3(PLAYER_MAXSPEED, 1.0f, PLAYER_MAXSPEED),
			GRAVITY,
			GRAVITYMAX,
		}));
	//落下
	actor->AddAction(CAction::Create<CFallAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_JUMP,
				0.81f,
				2.0f,
				0.1f,
				false
			}
		},
		CFallAction::Parameter{
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
			GRAVITY,
			GRAVITYMAX,
		}));
	//ダッシュ落下
	actor->AddAction(CAction::Create<CRunFallAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_JUMP,
				0.81f,
				2.0f,
				0.1f,
				false
			}
		},
		CRunFallAction::Parameter{
			Vector3(PLAYER_MAXSPEED, 1.0f, PLAYER_MAXSPEED),
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
			Vector3(PLAYER_MAXSPEED, 1.0f, PLAYER_MAXSPEED),
			GRAVITY,
			GRAVITYMAX,
		}));
	//着地
	actor->AddAction(CAction::Create<CLandingAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_LANDING,
				0.0f,
				1.0f,
				0.1f,
				false
			}
		},
		CLandingAction::Parameter{
			
		}));
	//ダッシュ着地
	actor->AddAction(CAction::Create<CRunLandingAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_LANDING,
				0.0f,
				1.0f,
				0.1f,
				false
			}
		},
		CRunLandingAction::Parameter{
			
		}));

	//攻撃１
	actor->AddAction(CAction::Create<CAttack1Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK1,
				0.0f,
				1.5f,
				0.1f,
				false
			}
		},
		CAttack1Action::Parameter{
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
			Vector3(0.2f, 1.0f, 1.0f),
		}));

	//攻撃２
	actor->AddAction(CAction::Create<CAttack2Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK2,
				0.0f,
				1.5f,
				0.1f,
				false
			}
		},
		CAttack2Action::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
			Vector3(0.1f, 0.0f, 0.0f),
		}));

	//攻撃３
	actor->AddAction(CAction::Create<CAttack3Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK3,
				0.0f,
				2.3f,
				0.1f,
				false
			}
		},
		CAttack3Action::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
			Vector3(0.05f, 0.0f, 0.0f),
			Vector3(0.1f, 0.0f, 0.0f),
		}));

	//ダッシュ攻撃１
	actor->AddAction(CAction::Create<CRunAttack1Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_RUN_ATTACK1,
				0.3f,
				1.0f,
				0.1f,
				false
			}
		},
		CRunAttack1Action::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
		}));
	//ダッシュ攻撃２
	actor->AddAction(STATE_KEY_RUN_ATTACK2,CAction::Create<CAttack1Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK1,
				0.0f,
				1.5f,
				0.1f,
				false
			}
		},
		CAttack1Action::Parameter{
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
			Vector3(0.2f, 1.0f, 1.0f),
		}));

	//ジャンプ攻撃１
	actor->AddAction(CAction::Create<CJumpAttack1Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_RUN_ATTACK1,
				0.0f,
				1.2f,
				0.1f,
				false
			}
		},
		CJumpAttack1Action::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
			GRAVITY,
		}));

	//ダッシュジャンプ攻撃１
	actor->AddAction(CAction::Create<CRunJumpAttack1Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK1,
				0.0f,
				1.7f,
				0.1f,
				false
			}
		},
		CRunJumpAttack1Action::Parameter{
			Vector3(0.25f, 0.0f, 0.0f),
			PLAYER_JUMPPOWER * 0.4f,
			GRAVITY * 0.7f,
			GRAVITY,
		}));
	//ダッシュジャンプ攻撃２
	actor->AddAction(CAction::Create<CRunJumpAttack2Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK2,
				0.0f,
				1.5f,
				0.1f,
				false
			}
		},
		CRunJumpAttack2Action::Parameter{
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
			Vector3(0.25f, 0.0f,0.0f),
			PLAYER_JUMPPOWER * 0.4f,
			GRAVITY * 0.7f,
			GRAVITY,
		}));
	//ダッシュジャンプ攻撃３
	actor->AddAction(CAction::Create<CRunJumpAttack3Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK3,
				0.0f,
				1.5f,
				0.1f,
				false
			}
		},
		CRunJumpAttack3Action::Parameter{
			Vector3(0.25f, 0.0f, 0.0f),
			PLAYER_JUMPPOWER * 0.4f,
			GRAVITY * 0.7f,
			GRAVITY,
		}));

	//ダメージ
	actor->AddAction(CAction::Create<CDamageAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_DAMAGE,
				0.0f,
				1.5f,
				0.1f,
				false
			}
		},
		CDamageAction::Parameter{
			Vector3(0.05f, 1.0f, 0.05f),
			GRAVITY,
			GRAVITYMAX,
		}));
	//空中ダメージ
	actor->AddAction(CAction::Create<CFlyDamageAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_FLY_DAMAGE,
				0.0f,
				1.2f,
				0.1f,
				false
			}
		},
		CFlyDamageAction::Parameter{
			
			Vector3(0.05f, 1.0f, 0.05f),
			GRAVITY,
			GRAVITYMAX * 0.4f,
		}));

	//ダウン
	actor->AddAction(CAction::Create<CDownAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_DOWN,
				0.0f,
				1.2f,
				0.1f,
				false
			}
		},
		CDownAction::Parameter{
			Vector3(0.05f, 1.0f, 0.05f),
		}));

	//死亡
	actor->AddAction(CAction::Create<CDeadAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_DOWN,
				0.0f,
				1.2f,
				0.1f,
				false
			}
		},
		CDeadAction::Parameter{	
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
			2.0f,
		}));

	//衝撃波スキル
	actor->AddAction(CAction::Create<CShockWaveSkillAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK1,
				0.0f,
				0.7f,
				0.1f,
				false
			}
		},
		CShockWaveSkillAction::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
		}));

	//ビームスキル
	actor->AddAction(CAction::Create<CBeamSkillAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_BEAM_SKILL,
				1.0f,
				2.2f,
				0.1f,
				false
			}
		},
		CBeamSkillAction::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
		}));
	//竜巻スキル
	actor->AddAction(CAction::Create<CStormSkillAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_STORM_SKILL,
				0.0f,
				1.2f,
				0.1f,
				true
			}
		},
		CStormSkillAction::Parameter{
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
		}));
	//空中ビームスキル
	actor->AddAction(CAction::Create<CJumpBeamSkillAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_BEAM_SKILL,
				1.0f,
				2.2f,
				0.1f,
				false
			}
		},
		CJumpBeamSkillAction::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
		}));
	//空中竜巻スキル
	actor->AddAction(CAction::Create<CNoneGravityAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_STORM_SKILL,
				0.0f,
				1.2f,
				0.1f,
				true
			}
		},
		CNoneGravityAction::Parameter{
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
		}));
	//回避
	actor->AddAction(CAction::Create<CEscapeAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ESCAPE,
				0.4f,
				2.0f,
				0.1f,
				false
			}
		},
		CEscapeAction::Parameter{
			Vector3(PLAYER_SPEED * 0.5f, 1.0f, PLAYER_SPEED * 0.5f),
			Vector3(PLAYER_MAXSPEED * 1.7f, 1.0f, PLAYER_MAXSPEED * 1.7f),
		}));
	//ドロップキックスキル
	actor->AddAction(CAction::Create<CDropKickSkillAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_DROPKICK_SKILL,
				0.0f,
				1.0f,
				0.0f,
				false
			}
		},
		CDropKickSkillAction::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
			Vector3(PLAYER_MAXSPEED * 2.0f, 1.0f, 1.0f),
			GRAVITY,
			GRAVITYMAX,
			PLAYER_JUMPPOWER * 0.5f,
		}));

	//クリアポーズ
	actor->AddAction(CAction::Create<ClearPoseAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_CLEARPOSE,
				0.0f,
				1.0f,
				0.0f,
				true
			}
		},
		ClearPoseAction::Parameter{
			AnimParam{
				STATE_KEY_JUMP,
				0.83f,
				1.0f,
				0.2f,
				false
			},
			Vector3(PLAYER_MAXSPEED, 1.0f, PLAYER_MAXSPEED),
			GRAVITY,
			GRAVITYMAX,
		}));

	//開始ポーズ
	actor->AddAction(CAction::Create<CStartPoseAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_STARTPOSE,
				0.0f,
				1.0f,
				0.0f,
				false
			}
		},
		CStartPoseAction::Parameter{
			Vector3(PLAYER_MAXSPEED, 1.0f, PLAYER_MAXSPEED),
			GRAVITY,
			GRAVITYMAX,
		}));

	//超ジャンプスキル
	actor->AddAction(STATE_KEY_FLYHIGH_SKILL,CAction::Create<CJumpAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_JUMP,
				0.3f,
				2.0f,
				0.1f,
				false
			}
		},
		CJumpAction::Parameter{
			Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
			GRAVITY,
			GRAVITYMAX,
			PLAYER_JUMPPOWER * 1.5f,
		}));
	{
		//ファイアフレイムスキル
		const std::string str = STATE_KEY_FIREFLAME_SKILL;
		actor->AddAction(str,
			CAction::Create<CNoneGravityAction>(
				CBaseAction::BaseParameter{
					AnimParam{
						"FireFlameStart",
						0.0f,
						1.0f,
						0.1f,
						false
					}
				},
				CNoneGravityAction::Parameter{
					Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
					Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
					Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED)
				}));
		actor->AddAction(str + STATE_KEY_FALL,
			CAction::Create<CFallAction>(
				CBaseAction::BaseParameter{
					AnimParam{
						"FireFlameEnd",
						0.0f,
						1.0f,
						0.1f,
						false
					}
				},
				CFallAction::Parameter{
					Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
					Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
					Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
					GRAVITY * 2.5f,
					GRAVITYMAX * 2.5f,
				}));
	}
	{
		//インパクトスキル
		const std::string fire = STATE_KEY_IMPACT_SKILL;
		actor->AddAction(fire,
			CAction::Create<CFallAction>(
				CBaseAction::BaseParameter{
					AnimParam{
						STATE_KEY_IMPACT_SKILL,
						0.0f,
						1.8f,
						0.1f,
						false
					}
				},
				CFallAction::Parameter{
					Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
					Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
					Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
					GRAVITY * 1.5f,
					GRAVITYMAX * 1.5f,
				}));
		actor->AddAction(fire + STATE_KEY_ATTACK1,
			CAction::Create<CAttack1Action>(
				CBaseAction::BaseParameter{
					AnimParam{
						STATE_KEY_IMPACT_SKILL,
						0.0f,
						1.8f,
						0.1f,
						false
					}
				},
				CAttack1Action::Parameter{
					Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
					Vector3(0.2f, 1.0f, 1.0f),
				}));
	}
	//チェイススキル
	actor->AddAction(STATE_KEY_CHASE_SKILL,
		CAction::Create<CDropKickSkillAction>(
			CBaseAction::BaseParameter{
				AnimParam{
					STATE_KEY_CHASE_SKILL,
					0.0f,
					1.8f,
					0.1f,
					true
				}
			},
			CDropKickSkillAction::Parameter{
				Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
				Vector3(PLAYER_MAXSPEED * 2.0f, 1.0f, 1.0f),
				GRAVITY,
				GRAVITYMAX,
				PLAYER_JUMPPOWER * 0.5f,
			}));
	

	/*
	* 移動補正
	*/
	{
		const auto type = actor->GetType();

		//攻撃１
		const std::string str = STATE_KEY_MOVECOMPENSATION;
		actor->AddAction(str + STATE_KEY_ATTACK1, CAction::Create<CMoveCompensationAction>(
			CMoveCompensationAction::BaseParameter{ true, false,false, 0.5f, 270.0f, 4.5f, type }
		));
		//攻撃２
		actor->AddAction(str + STATE_KEY_ATTACK2, CAction::Create<CMoveCompensationAction>(
			CMoveCompensationAction::BaseParameter{ true, false,false, 0.5f, 90.0f, 2.5f, type }
		));
		//ダッシュ攻撃１
		actor->AddAction(str + STATE_KEY_RUN_ATTACK1, CAction::Create<CMoveCompensationAction>(
			CMoveCompensationAction::BaseParameter{ true, false,false, 0.5f, 270.0f, 4.5f, type }
		));
		//ダッシュ攻撃２
		actor->AddAction(str + STATE_KEY_RUN_ATTACK2, CAction::Create<CMoveCompensationAction>(
			CMoveCompensationAction::BaseParameter{ true, false,false, 0.5f, 90.0f, 4.5f, type }
		));
		//チェイススキル
		actor->AddAction(str + STATE_KEY_CHASE_SKILL, CAction::Create<CMoveCompensationAction>(
			CMoveCompensationAction::BaseParameter{ true, true,false, 0.5f, 270.0f, 7.5f, type }
		));
		//ジャンプ攻撃１
		actor->AddAction(str + STATE_KEY_JUMP_ATTACK1, CAction::Create<CMoveCompensationAction>(
			CMoveCompensationAction::BaseParameter{ true, true,false, 0.5f, 120.0f, 3.5f, type }
		));
		//ダッシュジャンプ攻撃１
		actor->AddAction(str + STATE_KEY_RUN_JUMP_ATTACK1, CAction::Create<CMoveCompensationAction>(
			CMoveCompensationAction::BaseParameter{ true, true,false, 0.5f, 120.0f, 3.5f, type }
		));
		//ダッシュジャンプ攻撃２
		actor->AddAction(str + STATE_KEY_RUN_JUMP_ATTACK2, CAction::Create<CMoveCompensationAction>(
			CMoveCompensationAction::BaseParameter{ true, false,false, 0.5f, 120.0f, 2.5f, type }
		));

	}
	


	return true;
}
