#pragma once
#include "JsonCreatorUtilities.h"
#include "Effect.h"
#include "Shot.h"
#include "GravityScale.h"

namespace ActionGame
{
	
	GravityScale CreateGravityScale(nlohmann::json& os);
	/*
	* @brief	エフェクトパラメータ作成
	*/
	EffectCreateParameter CreateEffectParam(nlohmann::json& os);

	/*
	* @brief	基底ショットパラメータ作成
	*/
	void				  CreateShotBaseParam(nlohmann::json& os, ShotCreateParameter& value);
	/*
	* @brief	AABBパラメータ作成
	*/
	ShotAABB			  CreateAABBParam(nlohmann::json& os);
	/*
	* @brief	OBBパラメータ作成
	*/
	ShotOBB				  CreateOBBParam(nlohmann::json& os);
	/*
	* @brief	球体パラメータ作成
	*/
	ShotSphere			  CreateSphereParam(nlohmann::json& os);
}