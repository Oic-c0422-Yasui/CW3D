#pragma once
#include "ServiceLocator.h"
#include "SceneChanger.h"
#include "SceneInitializer.h"

//��ʑJ�ڗp�T�[�r�X
using SceneChangeService = CServiceLocator<Scene::ISceneChanger>;
//��ʏ������p�T�[�r�X
using SceneInitializeService = CServiceLocator<Scene::ISceneInitializer>;
