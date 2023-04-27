#pragma once

#include "AttackCollider.h"
#include "TimeScaleController.h"
#include "ShotParameter.h"



namespace ActionGame
{
	

	/*
	* @brief�@�V���b�g�N���X
	*/
	class CShot
	{
	protected:

		//�q�b�g����p�\����
		struct Hit
		{
			uint32_t ID;			//�q�b�g��������̃A�N�^�[ID
			float Time;			//�����蔻����s��Ȃ�����
		};
		std::list<Hit>		hitIDs_;

		AttackColliderPtr	collider_;
		CAABB				AABB_;
		COBB				OBB_;
		CVector3			position_;
		float				radius_;
		CVector3			size_;
		bool				isShow_;
		COLLISION_TYPE		collisionType_;
		float				speed_;
		ShotCreateParameter param_;

	protected:
		/*		�v���C�x�[�g�֐�		*/

		//�폜���Ԃ܂Ń^�C�}�[��i�߂�
		void UpdateTime();

		//�x�[�X�̃V���b�g�쐬
		void CreateBase(const Vector3& pos, const ShotCreateParameter& shot);

		//�R���C�_�[�̍��W�����݂̍��W�ɍ��킹��
		void ApplyColliderPosition();

	public:
		CShot();
		~CShot();

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
		void AddHit(uint32_t hitId)
		{
			Hit hit = { hitId, param_.nextHitTime };
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
			param_.damage += val;
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
			return param_.isEnableCollider;
		}

		/*
		* @brief	���ɏՓ˂��鎞�Ԃ��擾
		* @return	���ɏՓ˂��鎞�ԁi�b�j
		*/
		float GetNextHitTime() const noexcept
		{
			return param_.nextHitTime;
		}

		/*
		* @brief	�e�̃L�����^�C�v���擾
		* @return	�e�̃L�����^�C�v
		*/
		CHARA_TYPE GetParentCharaType() const noexcept
		{
			return param_.parentType;
		}

		/*
		* @brief	�l�������K�E�Z�Q�[�W�ʂ��擾
		* @return	�l�������K�E�Z�Q�[�W��
		*/
		float GetRecieveUltGauge() const noexcept
		{
			return param_.recieveUltGauge;
		}

		/*
		* @brief	�e�A�N�^�[��ID���擾
		* @return	�e�A�N�^�[��ID
		*/
		uint32_t GetParentID() const noexcept
		{
			return param_.parentID;
		}

		/*
		* @brief	�m�b�N�o�b�N�̕������擾
		* @return	�m�b�N�o�b�N�̕���
		*/
		const KnockBackPtr& GetDirection() const noexcept
		{
			return param_.direction;
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
			return param_.offset;
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
			return param_.knockBack;
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
		uint32_t GetDamage() const noexcept {
			return param_.damage;
		}

		/*
		* @brief	�A�[�}�[�j�󃌃x�����擾
		* @return	�A�[�}�[�j�󃌃x��
		*/
		BYTE GetArmorBreakLevel() const noexcept{
			return param_.armorBreakLevel;
		}
		
		/*
		* @brief	�_���[�W�p�̃G�t�F�N�g�p�����[�^���擾
		* @return	�_���[�W�p�̃G�t�F�N�g�p�����[�^
		*/
		const EffectCreateParameterPtr& GetDamageEffect() const noexcept{
			return param_.damageEffect;
		}

		const GravityScale& GetGravityScale() const noexcept
		{
			return param_.gravity;
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
		* @param	parentType �e�̃L�����^�C�v
		*/
		void SetParentCharaType(CHARA_TYPE type) noexcept
		{
			param_.parentType = type;
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
			param_.isEnableCollider = isEnable;
		}

		/*
		* @brief	�m�b�N�o�b�N�̗͂�ݒ�
		* @param	val �m�b�N�o�b�N�̗�
		*/
		void SetKnockBackPower(const Vector3& val) noexcept
		{
			param_.knockBack = val;
		}

		/*
		* @brief	X���̃m�b�N�o�b�N�̗͂�ݒ�
		* @param	val X���̃m�b�N�o�b�N�̗�
		*/
		void SetKnockBackPowerX(float val) noexcept
		{
			param_.knockBack.x = val;
		}

		/*
		* @brief	Y���̃m�b�N�o�b�N�̗͂�ݒ�
		* @param	val Y���̃m�b�N�o�b�N�̗�
		*/
		void SetKnockBackPowerY(float val) noexcept
		{
			param_.knockBack.y = val;
		}

		/*
		* @brief	Z���̃m�b�N�o�b�N�̗͂�ݒ�
		* @param	val Z���̃m�b�N�o�b�N�̗�
		*/
		void SetKnockBackPowerZ(float val) noexcept
		{
			param_.knockBack.z = val;
		}

		/*
		* @brief	�_���[�W��ݒ�
		* @param	val �_���[�W
		*/
		void SetDamage(uint32_t val) noexcept
		{
			param_.damage = val;
		}

		/*
		* @brief	���ɏՓ˂��鎞�Ԃ�ݒ�
		* @param	sec ���ɏՓ˂��鎞�ԁi�b�j
		*/
		void SetNextHitTime(float sec) noexcept
		{
			param_.nextHitTime = sec;
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
			param_.offset = offset;
		}

		/*
		* @brief	�m�b�N�o�b�N�̌�����ݒ�
		* @param	dir �m�b�N�o�b�N�̌���
		*/
		void SetKnockBackDirection(const KnockBackPtr& dir) noexcept
		{
			param_.direction = dir;
		}

		/*
		* @brief	�A�[�}�[�j�󃌃x����ݒ�
		* @param	level �A�[�}�[�j�󃌃x��
		*/
		void SetArmorBreakLevel(BYTE level) noexcept
		{
			param_.armorBreakLevel = level;
		}

		/*
		* @brief	�l���K�E�Z�Q�[�W�ʂ�ݒ�
		* @param	level �l���K�E�Z�Q�[�W��
		*/
		void SetRecieveUltGauge(float gauge) noexcept
		{
			param_.recieveUltGauge = gauge;
		}

		/*
		* @brief	�e�A�N�^�[ID��ݒ�
		* @param	id �e�A�N�^�[ID
		*/
		void SetParentID(uint32_t id)noexcept
		{
			param_.parentID = id;
		}

		/*
		* @brief	�d�̓X�P�[���p�����[�^�ݒ�
		* @param	scale �d�̓X�P�[���p�����[�^
		*/
		void SetGravityScale(GravityScale scale) noexcept
		{
			param_.gravity = scale;
		}

	};

	//�|�C���^�u������
	using ShotPtr = std::shared_ptr<CShot>;
}


