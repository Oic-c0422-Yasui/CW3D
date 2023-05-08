#pragma once
#include "Common.h"
#include "GravityScale.h"
#include "KnockBack.h"
#include "CollisionDefine.h"
#include "Effect.h"

namespace ActionGame
{
	//�V���b�g�p�����[�^�[
	/*
	* @brief	�V���b�g�p�����[�^
	* @param	offset			�I�t�Z�b�g
	* @param	nextHitTime		���̃q�b�g����
	* @param	damage			�_���[�W
	* @param	knockBack		�m�b�N�o�b�N��
	* @param	isEnableCollider �����蔻��L����
	* @param	parentType		�e�^�C�v
	* @param	direction		�m�b�N�o�b�N����
	* @param	armorBreakLevel �A�[�}�[�j�󃌃x��
	* @param	recieveUltGauge �󂯎��K�E�Z�Q�[�W��
	* @param	parentID	�@	�eID
	* @param	damageEffect	�_���[�W�G�t�F�N�g
	* @param	gravity		�@	�d�̓p�����[�^
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
	* @brief	���̃V���b�g�p�����[�^
	* @param	offset			�I�t�Z�b�g
	* @param	nextHitTime		���̃q�b�g����
	* @param	damage			�_���[�W
	* @param	knockBack		�m�b�N�o�b�N��
	* @param	isEnableCollider �����蔻��L����
	* @param	parentType		�e�^�C�v
	* @param	direction		�m�b�N�o�b�N����
	* @param	armorBreakLevel �A�[�}�[�j�󃌃x��
	* @param	recieveUltGauge �󂯎��K�E�Z�Q�[�W��
	* @param	parentID	�@	�eID
	* @param	damageEffect	�_���[�W�G�t�F�N�g
	* @param	gravity		�@	�d�̓p�����[�^
	* @param	Radius			���a
	*/
	struct ShotSphere : public ShotCreateParameter {
		float Radius;
	};
	/*
	* @brief	���V���b�g�p�����[�^
	* @param	offset			�I�t�Z�b�g
	* @param	nextHitTime		���̃q�b�g����
	* @param	damage			�_���[�W
	* @param	knockBack		�m�b�N�o�b�N��
	* @param	isEnableCollider �����蔻��L����
	* @param	parentType		�e�^�C�v
	* @param	direction		�m�b�N�o�b�N����
	* @param	armorBreakLevel �A�[�}�[�j�󃌃x��
	* @param	recieveUltGauge �󂯎��K�E�Z�Q�[�W��
	* @param	parentID	�@	�eID
	* @param	damageEffect	�_���[�W�G�t�F�N�g
	* @param	gravity		�@	�d�̓p�����[�^
	* @param	size			�T�C�Y
	*/
	struct ShotAABB : public ShotCreateParameter {
		Vector3 size;
	};
	/*
	* @brief	��]���l���������V���b�g�p�����[�^
	* @param	offset			�I�t�Z�b�g
	* @param	nextHitTime		���̃q�b�g����
	* @param	damage			�_���[�W
	* @param	knockBack		�m�b�N�o�b�N��
	* @param	isEnableCollider �����蔻��L����
	* @param	parentType		�e�^�C�v
	* @param	direction		�m�b�N�o�b�N����
	* @param	armorBreakLevel �A�[�}�[�j�󃌃x��
	* @param	recieveUltGauge �󂯎��K�E�Z�Q�[�W��
	* @param	parentID	�@	�eID
	* @param	damageEffect	�_���[�W�G�t�F�N�g
	* @param	gravity		�@	�d�̓p�����[�^
	* @param	size			�T�C�Y
	* @param	angle			�p�x
	*/
	struct ShotOBB : public ShotAABB {
		Vector3 angle;
	};
}
