#pragma once

#include "AttackCollider.h"

#include "KnockBack.h"
#include "TimeScaleController.h"
#include "CollisionDefine.h"
#include "Effect.h"

namespace ActionGame
{
	//�V���b�g�p�����[�^�[
	struct ShotCreateParameter {
		Vector3 offset;
		float	nextHitTime;
		int		damage;
		Vector3	knockBack;
		bool	collideFlg;
		CHARA_TYPE type;
		KnockBackPtr direction;
		BYTE armorBreakLevel;
		float recieveUltGauge;
		unsigned int parentID;
		EffectCreateParameterPtr damageEffect;
	};
	//���̃V���b�g
	struct ShotSphere : public ShotCreateParameter {
		float Radius;
	};
	//���V���b�g
	struct ShotAABB : public ShotCreateParameter{
		Vector3 size;
	};
	//��]���l���������V���b�g
	struct ShotOBB : public ShotAABB {
		Vector3 angle;
	};

	/*
	* @brief�@�V���b�g�N���X
	*/
	class Shot
	{
	protected:

		//�q�b�g����p�\����
		struct Hit
		{
			size_t ID;			//�q�b�g��������̃A�N�^�[ID
			float Time;			//�����蔻����s��Ȃ�����
		};
		std::list<Hit>		hitIDs_;

		AttackColliderPtr	collider_;
		CAABB				AABB_;
		COBB				OBB_;
		CVector3			position_;
		float				radius_;
		CVector3			size_;
		Vector3				offset_;
		bool				isShow_;
		bool				isEnableCollider;
		CHARA_TYPE			parentCharaType_;
		size_t				parentID_;
		COLLISION_TYPE		collisionType_;
		float				speed_;
		int					damage_;
		float				nextHitTime_;
		KnockBackPtr		knockBackDirection_;
		CVector3			knockBackPower_;
		BYTE				armorBreakLevel_;
		float				recieveUltGauge_;
		EffectCreateParameterPtr damageEffect_;

	protected:
		/*		�v���C�x�[�g�֐�		*/

		//�폜���Ԃ܂Ń^�C�}�[��i�߂�
		void UpdateTime();

		//�x�[�X�̃V���b�g�쐬
		void CreateBase(const Vector3& pos, const ShotCreateParameter& shot);

		//�R���C�_�[�̍��W�����݂̍��W�ɍ��킹��
		void ApplyColliderPosition();

	public:
		Shot();
		~Shot();

		/*
		* @brief	���̂̃V���b�g�쐬
		* @param	pos	���W
		* @param	sphere	���̗p�̃V���b�g�p�����[�^
		*/
		void Create(const Vector3& pos, const ShotSphere& sphire);
		
		/*
		* @brief	���̃V���b�g�쐬
		* @param	pos	���W
		* @param	aabb	���p�̃V���b�g�p�����[�^
		*/
		void Create(const Vector3& pos, const ShotAABB& aabb);

		/*
		* @brief	��]���l���������̃V���b�g�쐬
		* @param	pos	���W
		* @param	obb	���p�̃V���b�g�p�����[�^
		*/
		void Create(const Vector3& pos, const ShotOBB& obb);
		
		/*
		* @brief	�X�V
		*/
		void Update();

		/*
		* @brief	�`��
		*/
		void Render();

		/*
		* @brief	�q�b�g���������ID��ǉ�
		* @param	hitId	�q�b�g���������ID
		*/
		void AddHit(unsigned int hitId)
		{
			Hit hit = { hitId, nextHitTime_ };
			hitIDs_.push_back(hit);
		}

		/*
		* @brief	�q�b�g����ID���폜
		*/
		void DeleteHitId()
		{
			auto removeIt = std::remove_if(hitIDs_.begin(), hitIDs_.end(), [&](const Hit& id) {
				return id.Time <= 0.0f; });
			hitIDs_.erase(removeIt, hitIDs_.end());
		}

		/*
		* @brief	�_���[�W��ǉ�
		* @param	val �_���[�W
		*/
		void AddDamage(int val) noexcept
		{
			damage_ += val;
		}

		/*
		* @brief	���W���ړ�
		* @param	pos ���W
		*/
		void AddPosition(const Vector3& pos) noexcept
		{
			position_ += pos;
		}


		//////////////////////////////////////////////
		///			�Q�b�^�[
		//////////////////////////////////////////////


		/*
		* @brief	�\�����Ă��邩�H
		* @return	true�@�Ȃ�\��
		*/
		bool IsShow() const noexcept {
			return isShow_;
		}

		/*
		* @brief	�Փ˔��肪�L�����H
		* @retval	true�@�Ȃ�L��
		* @retval	false�@�Ȃ疳���i�����蔻����s��Ȃ��j
		*/
		bool IsEnableCollider() const noexcept {
			return isEnableCollider;
		}

		/*
		* @brief	���ɏՓ˂��鎞�Ԃ��擾
		* @return	���ɏՓ˂��鎞�ԁi�b�j
		*/
		float GetNextHitTime() const noexcept
		{
			return nextHitTime_;
		}

		/*
		* @brief	�e�̃L�����^�C�v���擾
		* @return	�e�̃L�����^�C�v
		*/
		CHARA_TYPE GetParentCharaType() const noexcept
		{
			return parentCharaType_;
		}

		/*
		* @brief	�l�������K�E�Z�Q�[�W�ʂ��擾
		* @return	�l�������K�E�Z�Q�[�W��
		*/
		float GetRecieveUltGauge() const noexcept
		{
			return recieveUltGauge_;
		}

		/*
		* @brief	�e�A�N�^�[��ID���擾
		* @return	�e�A�N�^�[��ID
		*/
		size_t GetParentID() const noexcept
		{
			return parentID_;
		}

		/*
		* @brief	�m�b�N�o�b�N�̕������擾
		* @return	�m�b�N�o�b�N�̕���
		*/
		const KnockBackPtr& GetDirection() const noexcept
		{
			return knockBackDirection_;
		}

		/*
		* @brief	���W���擾
		* @return	���W
		*/
		const Vector3& GetPosition() const noexcept 
		{
			return position_;
		}

		/*
		* @brief	�I�t�Z�b�g���W���擾
		* @return	�I�t�Z�b�g���W
		*/
		const Vector3& GetOffset() const noexcept 
		{
			return offset_;
		}

		/*
		* @brief	�����蔻��̔��a���擾
		* @return	�����蔻��̔��a
		*/
		COLLISION_TYPE GetCollisionType() const noexcept
		{
			return collisionType_;
		}

		/*
		* @brief	���̂̓����蔻����擾(�Փ˔���̃^�C�v�����̂̏ꍇ)
		* @return	���̂̓����蔻��
		*/
		CSphere GetColliderSphere() const noexcept 
		{
			return collider_->GetCollider();
		}
		/*
		* @brief	���̂̔��a���擾(�Փ˔���̃^�C�v�����̂̏ꍇ)
		* @return	���̂̔��a
		*/
		float GetRadius() const noexcept 
		{
			return radius_;
		}

		/*
		* @brief	���̓����蔻����擾(�Փ˔���̃^�C�v�����̏ꍇ)
		* @return	���̓����蔻��
		*/
		CAABB GetColliderAABB() const noexcept 
		{
			return AABB_;
		}

		/*
		* @brief	��]���l���������̓����蔻����擾(�Փ˔���̃^�C�v����]���l���������̏ꍇ)
		* @return	��]���l���������̓����蔻��
		*/
		COBB GetColliderOBB() const noexcept
		{
			return	OBB_;
		}

		/*
		* @brief	�m�b�N�o�b�N�̗͂��擾
		* @return	�m�b�N�o�b�N�̗�
		*/
		const Vector3& GetKnockBackPower() const noexcept {
			return knockBackPower_;
		}

		/*
		* @brief	���x���擾
		* @return	���x
		*/
		float GetSpeed() const noexcept {
			return speed_;
		}

		/*
		* @brief	�_���[�W���擾
		* @return	�_���[�W
		*/
		int GetDamage() const noexcept {
			return damage_;
		}

		/*
		* @brief	�A�[�}�[�j�󃌃x�����擾
		* @return	�A�[�}�[�j�󃌃x��
		*/
		BYTE GetArmorBreakLevel() const noexcept{
			return armorBreakLevel_;
		}
		
		/*
		* @brief	�_���[�W�p�̃G�t�F�N�g�p�����[�^���擾
		* @return	�_���[�W�p�̃G�t�F�N�g�p�����[�^
		*/
		const EffectCreateParameterPtr& GetDamageEffect() const noexcept{
			return damageEffect_;
		}

		/*
		* @brief	�A�N�^�[�Ƃ��łɏՓ˂��Ă��邩�H
		* @param	hitId�@�A�N�^�[��ID
		* @return	true�@�Ȃ�Փ˂��Ă���
		*/
		bool IsHit(unsigned int hitId) const noexcept
		{
			for (auto& id : hitIDs_)
			{
				if (id.ID == hitId)
				{
					return true;
				}
			}
			return false;
		}

		//////////////////////////////////////////////
		///			�Z�b�^�[
		//////////////////////////////////////////////

		/*
		* @brief	�e�̃L�����^�C�v��ݒ�
		* @param	type �e�̃L�����^�C�v
		*/
		void SetParentCharaType(CHARA_TYPE type) noexcept
		{
			parentCharaType_ = type;
		}

		/*
		* @brief	�\���ۂ�ݒ�
		* @param	isShow �\����
		*/
		void SetShow(bool isShow) noexcept
		{
			isShow_ = isShow;
		}

		/*
		* @brief	�Փ˔���̗L������ݒ�
		* @param	isEnable �Փ˔���̗L����
		*/
		void SetEnableCollider(bool isEnable) noexcept
		{
			isEnableCollider = isEnable;
		}

		/*
		* @brief	�m�b�N�o�b�N�̗͂�ݒ�
		* @param	val �m�b�N�o�b�N�̗�
		*/
		void SetKnockBackPower(const Vector3& val) noexcept
		{
			knockBackPower_ = val;
		}

		/*
		* @brief	X���̃m�b�N�o�b�N�̗͂�ݒ�
		* @param	val X���̃m�b�N�o�b�N�̗�
		*/
		void SetKnockBackPowerX(float val) noexcept
		{
			knockBackPower_.x = val;
		}

		/*
		* @brief	Y���̃m�b�N�o�b�N�̗͂�ݒ�
		* @param	val Y���̃m�b�N�o�b�N�̗�
		*/
		void SetKnockBackPowerY(float val) noexcept
		{
			knockBackPower_.y = val;
		}

		/*
		* @brief	Z���̃m�b�N�o�b�N�̗͂�ݒ�
		* @param	val Z���̃m�b�N�o�b�N�̗�
		*/
		void SetKnockBackPowerZ(float val) noexcept
		{
			knockBackPower_.z = val;
		}

		/*
		* @brief	�_���[�W��ݒ�
		* @param	val �_���[�W
		*/
		void SetDamage(int val) noexcept
		{
			damage_ = val;
		}

		/*
		* @brief	���ɏՓ˂��鎞�Ԃ�ݒ�
		* @param	sec ���ɏՓ˂��鎞�ԁi�b�j
		*/
		void SetNextHitTime(float sec) noexcept
		{
			nextHitTime_ = sec;
		}

		/*
		* @brief	���x��ݒ�
		* @param	val ���x
		*/
		void SetSpeed(float val) noexcept
		{
			speed_ = val;
		}

		/*
		* @brief	���W��ݒ�
		* @param	val ���W
		*/
		void SetPosition(const Vector3& pos) noexcept
		{
			position_ = pos;
		}

		/*
		* @brief	�I�t�Z�b�g���W��ݒ�
		* @param	offset �I�t�Z�b�g���W
		*/
		void SetOffset(const Vector3& offset) noexcept
		{
			offset_ = offset;
		}

		/*
		* @brief	�m�b�N�o�b�N�̌�����ݒ�
		* @param	dir �m�b�N�o�b�N�̌���
		*/
		void SetKnockBackDirection(const KnockBackPtr& dir) noexcept
		{
			knockBackDirection_ = dir;
		}

		/*
		* @brief	�A�[�}�[�j�󃌃x����ݒ�
		* @param	level �A�[�}�[�j�󃌃x��
		*/
		void SetArmorBreakLevel(BYTE level) noexcept
		{
			armorBreakLevel_ = level;
		}

		/*
		* @brief	�l���K�E�Z�Q�[�W�ʂ�ݒ�
		* @param	level �l���K�E�Z�Q�[�W��
		*/
		void SetRecieveUltGauge(float gauge) noexcept
		{
			recieveUltGauge_ = gauge;
		}

		/*
		* @brief	�e�A�N�^�[ID��ݒ�
		* @param	id �e�A�N�^�[ID
		*/
		void SetParentID(size_t id)noexcept
		{
			parentID_ = id;
		}

	};

	//�|�C���^�u������
	using ShotPtr = std::shared_ptr<Shot>;
}


