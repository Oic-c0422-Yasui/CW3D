#pragma once

#include "AttackCollider.h"

#include "KnockBack.h"
#include "TimeScaleController.h"
#include "CollisionDefine.h"

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
		float getUltGauge;
		unsigned int parentID;
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
			unsigned int ID;	//�q�b�g��������̃A�N�^�[ID
			float Time;			//�����蔻����s��Ȃ�����
		};
		std::list<Hit>		m_HitIDs;

		AttackColliderPtr	m_Collider;
		CAABB				m_AABB;
		COBB				m_OBB;
		CVector3			m_Position;
		float				m_Radius;
		CVector3			m_Size;
		Vector3				m_Offset;
		bool				m_ShowFlg;
		bool				m_EnableColliderFlg;
		CHARA_TYPE			m_ParentCharaType;
		COLLISION_TYPE		m_CollisionType;
		float				m_Speed;
		int					m_Damage;
		float				m_NextHitTime;
		KnockBackPtr		m_KnockBackDirection;
		CVector3			m_KnockBackPower;
		BYTE				m_ArmorBreakLevel;
		float				m_GetUltGauge;
		unsigned int		m_ParentID;

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
			Hit hit = { hitId, m_NextHitTime };
			m_HitIDs.push_back(hit);
		}

		/*
		* @brief	�q�b�g����ID���폜
		*/
		void DeleteHitId()
		{
			auto removeIt = std::remove_if(m_HitIDs.begin(), m_HitIDs.end(), [&](const Hit& id) {
				return id.Time <= 0.0f; });
			m_HitIDs.erase(removeIt, m_HitIDs.end());
		}

		/*
		* @brief	�_���[�W��ǉ�
		* @param	val �_���[�W
		*/
		void AddDamage(int val) noexcept
		{
			m_Damage += val;
		}

		/*
		* @brief	���W���ړ�
		* @param	pos ���W
		*/
		void AddPosition(const Vector3& pos) noexcept
		{
			m_Position += pos;
		}


		//////////////////////////////////////////////
		///			�Q�b�^�[
		//////////////////////////////////////////////


		/*
		* @brief	�\�����Ă��邩�H
		* @return	true�@�Ȃ�\��
		*/
		bool IsShow() const noexcept {
			return m_ShowFlg;
		}

		/*
		* @brief	�Փ˔��肪�L�����H
		* @retval	true�@�Ȃ�L��
		* @retval	false�@�Ȃ疳���i�����蔻����s��Ȃ��j
		*/
		bool IsEnableCollider() const noexcept {
			return m_EnableColliderFlg;
		}

		/*
		* @brief	���ɏՓ˂��鎞�Ԃ��擾
		* @return	���ɏՓ˂��鎞�ԁi�b�j
		*/
		float GetNextHitTime() const noexcept
		{
			return m_NextHitTime;
		}

		/*
		* @brief	�e�̃L�����^�C�v���擾
		* @return	�e�̃L�����^�C�v
		*/
		CHARA_TYPE GetParentCharaType() const noexcept
		{
			return m_ParentCharaType;
		}

		/*
		* @brief	�l�������K�E�Z�Q�[�W�ʂ��擾
		* @return	�l�������K�E�Z�Q�[�W��
		*/
		float GetGetUltGauge() const noexcept
		{
			return m_GetUltGauge;
		}

		/*
		* @brief	�e�A�N�^�[��ID���擾
		* @return	�e�A�N�^�[��ID
		*/
		unsigned int GetParentID() const noexcept
		{
			return m_ParentID;
		}

		/*
		* @brief	�m�b�N�o�b�N�̕������擾
		* @return	�m�b�N�o�b�N�̕���
		*/
		const KnockBackPtr& GetDirection() const noexcept
		{
			return m_KnockBackDirection;
		}

		/*
		* @brief	���W���擾
		* @return	���W
		*/
		const Vector3& GetPosition() const noexcept 
		{
			return m_Position;
		}

		/*
		* @brief	�I�t�Z�b�g���W���擾
		* @return	�I�t�Z�b�g���W
		*/
		const Vector3& GetOffset() const noexcept 
		{
			return m_Offset;
		}

		/*
		* @brief	�����蔻��̔��a���擾
		* @return	�����蔻��̔��a
		*/
		COLLISION_TYPE GetCollisionType() const noexcept
		{
			return m_CollisionType;
		}

		/*
		* @brief	���̂̓����蔻����擾(�Փ˔���̃^�C�v�����̂̏ꍇ)
		* @return	���̂̓����蔻��
		*/
		CSphere GetColliderSphere() const noexcept 
		{
			return m_Collider->GetCollider();
		}
		/*
		* @brief	���̂̔��a���擾(�Փ˔���̃^�C�v�����̂̏ꍇ)
		* @return	���̂̔��a
		*/
		float GetRadius() const noexcept 
		{
			return m_Radius;
		}

		/*
		* @brief	���̓����蔻����擾(�Փ˔���̃^�C�v�����̏ꍇ)
		* @return	���̓����蔻��
		*/
		CAABB GetColliderAABB() const noexcept 
		{
			return m_AABB;
		}

		/*
		* @brief	��]���l���������̓����蔻����擾(�Փ˔���̃^�C�v����]���l���������̏ꍇ)
		* @return	��]���l���������̓����蔻��
		*/
		COBB GetColliderOBB() const noexcept
		{
			return	m_OBB;
		}

		/*
		* @brief	�m�b�N�o�b�N�̗͂��擾
		* @return	�m�b�N�o�b�N�̗�
		*/
		const Vector3& GetKnockBackPower() const noexcept {
			return m_KnockBackPower;
		}

		/*
		* @brief	���x���擾
		* @return	���x
		*/
		float GetSpeed() const noexcept {
			return m_Speed;
		}

		/*
		* @brief	�_���[�W���擾
		* @return	�_���[�W
		*/
		int GetDamage() const noexcept {
			return m_Damage;
		}

		/*
		* @brief	�A�[�}�[�j�󃌃x�����擾
		* @return	�A�[�}�[�j�󃌃x��
		*/
		BYTE GetArmorBreakLevel() const noexcept{
			return m_ArmorBreakLevel;
		}

		/*
		* @brief	�A�N�^�[�Ƃ��łɏՓ˂��Ă��邩�H
		* @param	hitId�@�A�N�^�[��ID
		* @return	true�@�Ȃ�Փ˂��Ă���
		*/
		bool IsHit(unsigned int hitId) const noexcept
		{
			for (auto& id : m_HitIDs)
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
			m_ParentCharaType = type;
		}

		/*
		* @brief	�\���ۂ�ݒ�
		* @param	isShow �\����
		*/
		void SetShow(bool isShow) noexcept
		{
			m_ShowFlg = isShow;
		}

		/*
		* @brief	�Փ˔���̗L������ݒ�
		* @param	isEnable �Փ˔���̗L����
		*/
		void SetEnableCollider(bool isEnable) noexcept
		{
			m_EnableColliderFlg = isEnable;
		}

		/*
		* @brief	�m�b�N�o�b�N�̗͂�ݒ�
		* @param	val �m�b�N�o�b�N�̗�
		*/
		void SetKnockBackPower(const Vector3& val) noexcept
		{
			m_KnockBackPower = val;
		}

		/*
		* @brief	X���̃m�b�N�o�b�N�̗͂�ݒ�
		* @param	val X���̃m�b�N�o�b�N�̗�
		*/
		void SetKnockBackPowerX(float val) noexcept
		{
			m_KnockBackPower.x = val;
		}

		/*
		* @brief	Y���̃m�b�N�o�b�N�̗͂�ݒ�
		* @param	val Y���̃m�b�N�o�b�N�̗�
		*/
		void SetKnockBackPowerY(float val) noexcept
		{
			m_KnockBackPower.y = val;
		}

		/*
		* @brief	Z���̃m�b�N�o�b�N�̗͂�ݒ�
		* @param	val Z���̃m�b�N�o�b�N�̗�
		*/
		void SetKnockBackPowerZ(float val) noexcept
		{
			m_KnockBackPower.z = val;
		}

		/*
		* @brief	�_���[�W��ݒ�
		* @param	val �_���[�W
		*/
		void SetDamage(int val) noexcept
		{
			m_Damage = val;
		}

		/*
		* @brief	���ɏՓ˂��鎞�Ԃ�ݒ�
		* @param	sec ���ɏՓ˂��鎞�ԁi�b�j
		*/
		void SetNextHitTime(float sec) noexcept
		{
			m_NextHitTime = sec;
		}

		/*
		* @brief	���x��ݒ�
		* @param	val ���x
		*/
		void SetSpeed(float val) noexcept
		{
			m_Speed = val;
		}

		/*
		* @brief	���W��ݒ�
		* @param	val ���W
		*/
		void SetPosition(const Vector3& pos) noexcept
		{
			m_Position = pos;
		}

		/*
		* @brief	�I�t�Z�b�g���W��ݒ�
		* @param	offset �I�t�Z�b�g���W
		*/
		void SetOffset(const Vector3& offset) noexcept
		{
			m_Offset = offset;
		}

		/*
		* @brief	�m�b�N�o�b�N�̌�����ݒ�
		* @param	dir �m�b�N�o�b�N�̌���
		*/
		void SetKnockBackDirection(const KnockBackPtr& dir) noexcept
		{
			m_KnockBackDirection = dir;
		}

		/*
		* @brief	�A�[�}�[�j�󃌃x����ݒ�
		* @param	level �A�[�}�[�j�󃌃x��
		*/
		void SetArmorBreakLevel(BYTE level) noexcept
		{
			m_ArmorBreakLevel = level;
		}

		/*
		* @brief	�l���K�E�Z�Q�[�W�ʂ�ݒ�
		* @param	level �l���K�E�Z�Q�[�W��
		*/
		void SetGetUltGauge(float gauge) noexcept
		{
			m_GetUltGauge = gauge;
		}

		/*
		* @brief	�e�A�N�^�[ID��ݒ�
		* @param	id �e�A�N�^�[ID
		*/
		void SetParentID(unsigned int id)noexcept
		{
			m_ParentID = id;
		}

	};

	//�|�C���^�u������
	using ShotPtr = std::shared_ptr<Shot>;
}


