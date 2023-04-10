#pragma once
#include "ServiceLocator.h"
#include "SceneChanger.h"
#include "SceneInitializer.h"

//画面遷移用サービス
using SceneChangeService = CServiceLocator<Scene::ISceneChanger>;
//画面初期化用サービス
using SceneInitializeService = CServiceLocator<Scene::ISceneInitializer>;
