#pragma once
#include "Utilities.h"
#include "ServiceLocator.h"
#include "SceneDefine.h"
#include "SceneInitializer.h"
#include "SceneChanger.h"
#include "StateDefine.h"
#include "AnimationDefine.h"
#include "InputDefine.h"
#include "SkillDefine.h"
#include "CharaTypeDefine.h"
#include "ParameterDefine.h"
#include "CollisionDefine.h"



//仮
#define PLAYER_SPEED 0.02f
#define PLAYER_MAXSPEED 0.14f
//プレイヤーの移動速度(0.6倍)
#define PLAYER_WALKSPEED 0.6f
#define GRAVITY 0.01f
#define GRAVITYMAX 0.3f
#define PLAYER_JUMPPOWER 0.22f


//FPS60
constexpr float GameFrameTime = 1.0f / 60.0f;

//初期アーマーレベル
constexpr BYTE DEFAULT_ARMORLEVEL = 1;



//画面遷移用サービス
using SceneChangeService = ActionGame::ServiceLocator<ActionGame::ISceneChanger>;
//画面初期化用サービス
using SceneInitializeService = ActionGame::ServiceLocator<ActionGame::ISceneInitializer>;


