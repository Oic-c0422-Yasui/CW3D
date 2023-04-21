#pragma once

#include	"Actor.h"
#include	"StateMachine.h"
#include	"ParameterDefine.h"
#include	"StateDefine.h"
#include	"NormalMapSkinnedParameter.h"
#include	"Shadow.h"

namespace ActionGame
{
	//���b�V���|�C���^
	using MeshPtr = std::shared_ptr<CMeshContainer>;

	/*
	* @brief	�A�N�^�[�̃I�u�W�F�N�g�N���X
	*/
	class CActorObject
	{
	protected:
		MeshPtr									mesh_;
		MyClass::NormalMapSkinnedParameterPtr	normalMap_;
		StateMachinePtr							stateMachine_;
		AnimationStatePtr						motion_;
		ActorPtr								actor_;
		CMatrix44								matWorld_;
		CVector3								colliderOffset_;
		CVector3								colliderSize_;
		bool									isShow_;
		bool									isDead_;
		CVector3								prevPosision_;
		float									ultBoostMag_;	//�K�E�Z�Q�[�W�̃u�[�X�g�{��
		float									weight_;
		CShadow									shadow_;

	public:
		CActorObject();
		virtual ~CActorObject();
		virtual bool Load();
		virtual void Initialize();
		virtual void Update();
		virtual void Render();
		virtual void Release();

		/**
		 * @brief	�K�E�Z�Q�[�W��ǉ�����
		 * @param	�K�E�Z�Q�[�W
		 */
		void AddUltGauge(float gauge);

		////////////////////////////////////////////////////////
		///				�Q�b�^�[
		////////////////////////////////////////////////////////
		/**
		 * @brief		�A�N�^�[�擾
		 * @return		�A�N�^�[
		 */
		const ActorPtr& GetActor() const noexcept
		{
			return actor_;
		}
		/**
		 * @brief		�L�����^�C�v�擾
		 * @return		�L�����^�C�v
		 */
		CHARA_TYPE GetType() const noexcept
		{
			return actor_->GetType();
		}
		/**
		 * @brief		���W�擾
		 * @return		���W
		 */
		const CVector3& GetPosition() const noexcept 
		{ 
			return actor_->GetPosition(); 
		}
		/**
		 * @brief		���x�擾
		 * @return		���x
		 */
		const CVector3& GetVelocity() const noexcept
		{ 
			return actor_->GetVelocity()->GetVelocity(); 
		}
		/**
		 * @brief		���]���Ă��邩�H
		 * @return		true�@�Ȃ甽�]
		 */
		bool IsReverse() const noexcept
		{ 
			return actor_->IsReverse(); 
		}
		/**
		 * @brief		��]�擾
		 * @return		��]
		 */
		const CVector3& GetRotate() const noexcept
		{ 
			return actor_->GetRotate(); 
		}
		/**
		 * @brief		�\�����Ă��邩�H
		 * @return		true�@�Ȃ�\��
		 */
		virtual bool IsShow() const noexcept {
			return isShow_;
		}
		/**
		 * @brief		�����蔻��擾
		 * @return		�����蔻��
		 */
		virtual const CAABB& GetCollider()
		{
			return actor_->GetCollider()->GetCollider();
		}
		/**
		 * @brief		�X�V�O���W�擾
		 * @return		�X�V�O���W
		 */
		const CVector3& GetPrevPos() const noexcept
		{
			return prevPosision_;
		}
		/**
		 * @brief		�A�N�^�[ID�擾
		 * @return		�A�N�^�[ID
		 */
		uint32_t GetID() const noexcept
		{
			return actor_->GetID();
		}
		/**
		 * @brief		�����蔻��𖳎����邩�H
		 * @return		true �Ȃ疳��
		 */
		bool IsThroughCollision() const noexcept;
		/**
		 * @brief		�K�E�Z�Q�[�W�̃u�[�X�g�{���擾
		 * @return		�K�E�Z�Q�[�W�̃u�[�X�g�{��
		 */
		float GetUltBoostMag() const noexcept
		{
			return ultBoostMag_;
		}
		/**
		 * @brief		���S���Ă��邩�H
		 * @return		true �Ȃ玀�S
		 */
		bool IsDead() const noexcept
		{
			return isDead_;
		}

		////////////////////////////////////////////////////////
		///				�Z�b�^�[
		////////////////////////////////////////////////////////
		/**
		 * @brief		�L�����^�C�v��ݒ�
		 * @param		type �L�����^�C�v
		 */
		void SetType(CHARA_TYPE type) noexcept
		{
			actor_->SetType(type);
		}
		/**
		 * @brief		���W��ݒ�
		 * @param		pos ���W
		 */
		virtual void SetPosition(const Vector3& position) noexcept
		{
			actor_->SetPosition(position);
		}
		/**
		 * @brief		�\���t���O��ݒ�
		 * @param		isShow �\���t���O
		 */
		virtual void SetShow(bool isShow)
		{
			isShow_ = isShow;
		}
		/**
		 * @brief		���肪�l������K�E�Z�Q�[�W�̔{��
		 * @param		magnification ���肪�l������K�E�Z�Q�[�W�̔{��
		 */
		void SetUltBoostMag(float magnification) noexcept
		{
			ultBoostMag_ = magnification;
		}

		

	};
	//�|�C���^�u������
	using ActorObjectPtr = std::shared_ptr<CActorObject>;
	using ActorObjectWeakPtr = std::weak_ptr<CActorObject>;
	using ActorObjectList = std::list<ActorObjectPtr>;
	using ActorObjectWeakList = std::list<ActorObjectWeakPtr>;
	using ActorObjectWeakListPtr = std::shared_ptr<ActorObjectWeakList>;
}

