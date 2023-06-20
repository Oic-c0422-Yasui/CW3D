#pragma once
#include "JsonCreatorUtilities.h"
#include "Effect.h"
#include "Shot.h"
#include "GravityScale.h"

namespace ActionGame
{
	
	GravityScale CreateGravityScale(nlohmann::json& os);
	/*
	* @brief	�G�t�F�N�g�p�����[�^�쐬
	*/
	EffectCreateParameter CreateEffectParam(nlohmann::json& os);

	/*
	* @brief	���V���b�g�p�����[�^�쐬
	*/
	void				  CreateShotBaseParam(nlohmann::json& os, ShotCreateParameter& value);
	/*
	* @brief	AABB�p�����[�^�쐬
	*/
	ShotAABB			  CreateAABBParam(nlohmann::json& os);
	/*
	* @brief	OBB�p�����[�^�쐬
	*/
	ShotOBB				  CreateOBBParam(nlohmann::json& os);
	/*
	* @brief	���̃p�����[�^�쐬
	*/
	ShotSphere			  CreateSphereParam(nlohmann::json& os);
}