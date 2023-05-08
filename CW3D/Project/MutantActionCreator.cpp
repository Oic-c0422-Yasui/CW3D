#include "MutantActionCreator.h"
#include "GameDefine.h"
#include "Attack1Action.h"
#include "IdleAction.h"
#include "MoveAction.h"
#include "DeadState.h"
#include "DamageState.h"
#include "FlyDamageState.h"
#include "NPCStartPoseAction.h"
#include "MoveCompensationAction.h"
#include "Attack3Action.h"

bool ActionGame::MutantActionCreator::Create(const ActorPtr& actor)
{
	//‘Ò‹@
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
	//”æ˜Jó‘Ô
	actor->AddAction(STATE_KEY_TIRED,CAction::Create<CIdleAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_TIRED,
				0.0f,
				0.8f,
				0.25f,
				true
			}
		},
		CIdleAction::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f,PLAYER_SPEED * 0.3f),
			Vector3(PLAYER_SPEED, 1.0f,PLAYER_SPEED)
		}));
	//ˆÚ“®
	actor->AddAction(CAction::Create<CMoveAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_MOVE,
				0.0f,
				1.5f,
				0.1f,
				true
			}
		},
		CMoveAction::Parameter{
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.5f, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.5f),
			Vector3(PLAYER_SPEED * PLAYER_WALKSPEED * 0.9f, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED * 0.9f),
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED * 1.5f, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED * 1.5f),
			GRAVITYMAX,
		}));

	//UŒ‚‚P
	actor->AddAction(CAction::Create<CAttack1Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK1,
				0.0f,
				1.2f,
				0.1f,
				false
			}
		},
		CAttack1Action::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
			Vector3(0.0f, 1.0f, 0.0f)
		}));

	//ƒ_ƒ[ƒW
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
	//ƒ_ƒ[ƒW
	actor->AddAction(CAction::Create<CFlyDamageAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_DAMAGE,
				0.0f,
				1.5f,
				0.1f,
				false
			}
		},
		CFlyDamageAction::Parameter{
			Vector3(0.05f, 1.0f, 0.05f),
			GRAVITY,
			GRAVITYMAX,
		}));

	//Ž€–S
	actor->AddAction(CAction::Create<CDeadAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_DEAD,
				0.0f,
				1.2f,
				0.1f,
				false
			}
		},
		CDeadAction::Parameter{
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
			1.5f,
		}));

	//ŠJŽnƒ|[ƒY
	actor->AddAction(CAction::Create<CNPCStartPoseAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_STARTPOSE,
				0.0f,
				1.5f,
				0.2f,
				false
			}
		},
		CNPCStartPoseAction::Parameter{
			Vector3(0.0f, 0.0f, 0.0f),
			1.0f,
		}));

	//‘„UŒ‚
	actor->AddAction(STATE_KEY_SPEAR_ATTACK,CAction::Create<CAttack1Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_STARTPOSE,
				0.0f,
				0.8f,
				0.1f,
				false
			}
		},
		CAttack1Action::Parameter{
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
			Vector3(0.0f, 1.0f, 0.0f)
		}));

	//ƒ^ƒbƒNƒ‹
	{
		const std::string str = STATE_KEY_TACKLE_ATTACK;
		//‘Ò‹@
		actor->AddAction(str,CAction::Create<CIdleAction>(
			CBaseAction::BaseParameter{
				AnimParam{
					"RunReady",
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
		//ˆÚ“®
		actor->AddAction(str + STATE_KEY_MOVE,CAction::Create<CMoveAction>(
			CBaseAction::BaseParameter{
				AnimParam{
					"RunAttack",
					0.0f,
					1.5f,
					0.1f,
					true
				}
			},
			CMoveAction::Parameter{
				Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.5f, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.5f),
				Vector3(0.0f, 1.0f, 0.0f),
				Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED * 1.5f, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED * 1.5f),
				GRAVITYMAX,
			}));
	}
	//^
	{
		const std::string str = STATE_KEY_SLASH_ATTACK;
		//UŒ‚‚R
		actor->AddAction(str,CAction::Create<CAttack3Action>(
			CBaseAction::BaseParameter{
				AnimParam{
					STATE_KEY_ATTACK2,
					0.0f,
					0.5f,
					0.1f,
					false
				}
			},
			CAttack3Action::Parameter{
				Vector3(PLAYER_SPEED * 0.4f, 1.0f, PLAYER_SPEED * 0.4f),
				Vector3(0.2f, 0.0f, 0.0f),
				Vector3(0.25f, 0.0f, 0.0f),
			}));
		//UŒ‚‚P
		actor->AddAction(str + STATE_KEY_ATTACK1,CAction::Create<CAttack1Action>(
			CBaseAction::BaseParameter{
				AnimParam{
					STATE_KEY_ATTACK1,
					0.8f,
					1.5f,
					0.1f,
					false
				}
			},
			CAttack1Action::Parameter{
				Vector3(PLAYER_SPEED * 0.4f, 1.0f, PLAYER_SPEED * 0.4f),
				Vector3(PLAYER_SPEED * 0.3f, 0.0f, PLAYER_SPEED * 0.3f)
			}));
	}

	/*
	* ˆÚ“®•â³
	*/
	{
		const auto type = actor->GetType();

		//ƒ^ƒbƒNƒ‹
		const std::string str = STATE_KEY_MOVECOMPENSATION;
		actor->AddAction(str + STATE_KEY_TACKLE_ATTACK, CAction::Create<CMoveCompensationAction>(
			CMoveCompensationAction::BaseParameter{ true, false,true, 2.0f, 360.0f, 12.5f, type }
		));
	}



    return true;
}
