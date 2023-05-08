#pragma once
#include "Common.h"
#include "GravityScale.h"
#include "KnockBack.h"
#include "CollisionDefine.h"
#include "Effect.h"

namespace ActionGame
{
	//ショットパラメーター
	/*
	* @brief	ショットパラメータ
	* @param	offset			オフセット
	* @param	nextHitTime		次のヒット時間
	* @param	damage			ダメージ
	* @param	knockBack		ノックバック力
	* @param	isEnableCollider 当たり判定有効化
	* @param	parentType		親タイプ
	* @param	direction		ノックバック方向
	* @param	armorBreakLevel アーマー破壊レベル
	* @param	recieveUltGauge 受け取る必殺技ゲージ量
	* @param	parentID	　	親ID
	* @param	damageEffect	ダメージエフェクト
	* @param	gravity		　	重力パラメータ
	*/
	struct ShotCreateParameter {
		Vector3 offset;
		float	nextHitTime;
		int		damage;
		Vector3	knockBack;
		bool	isEnableCollider;
		CHARA_TYPE parentType;
		KnockBackPtr direction;
		BYTE armorBreakLevel;
		float recieveUltGauge;
		uint32_t parentID;
		EffectCreateParameterPtr damageEffect;
		GravityScale gravity;
	};

	/*
	* @brief	球体ショットパラメータ
	* @param	offset			オフセット
	* @param	nextHitTime		次のヒット時間
	* @param	damage			ダメージ
	* @param	knockBack		ノックバック力
	* @param	isEnableCollider 当たり判定有効化
	* @param	parentType		親タイプ
	* @param	direction		ノックバック方向
	* @param	armorBreakLevel アーマー破壊レベル
	* @param	recieveUltGauge 受け取る必殺技ゲージ量
	* @param	parentID	　	親ID
	* @param	damageEffect	ダメージエフェクト
	* @param	gravity		　	重力パラメータ
	* @param	Radius			半径
	*/
	struct ShotSphere : public ShotCreateParameter {
		float Radius;
	};
	/*
	* @brief	箱ショットパラメータ
	* @param	offset			オフセット
	* @param	nextHitTime		次のヒット時間
	* @param	damage			ダメージ
	* @param	knockBack		ノックバック力
	* @param	isEnableCollider 当たり判定有効化
	* @param	parentType		親タイプ
	* @param	direction		ノックバック方向
	* @param	armorBreakLevel アーマー破壊レベル
	* @param	recieveUltGauge 受け取る必殺技ゲージ量
	* @param	parentID	　	親ID
	* @param	damageEffect	ダメージエフェクト
	* @param	gravity		　	重力パラメータ
	* @param	size			サイズ
	*/
	struct ShotAABB : public ShotCreateParameter {
		Vector3 size;
	};
	/*
	* @brief	回転を考慮した箱ショットパラメータ
	* @param	offset			オフセット
	* @param	nextHitTime		次のヒット時間
	* @param	damage			ダメージ
	* @param	knockBack		ノックバック力
	* @param	isEnableCollider 当たり判定有効化
	* @param	parentType		親タイプ
	* @param	direction		ノックバック方向
	* @param	armorBreakLevel アーマー破壊レベル
	* @param	recieveUltGauge 受け取る必殺技ゲージ量
	* @param	parentID	　	親ID
	* @param	damageEffect	ダメージエフェクト
	* @param	gravity		　	重力パラメータ
	* @param	size			サイズ
	* @param	angle			角度
	*/
	struct ShotOBB : public ShotAABB {
		Vector3 angle;
	};
}
