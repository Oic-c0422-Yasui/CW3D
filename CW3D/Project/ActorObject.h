#pragma once

#include	"Actor.h"
#include	"StateMachine.h"
#include	"ParameterDefine.h"
#include	"StateDefine.h"

namespace ActionGame
{
	/*
	* @brief	�A�N�^�[�̃I�u�W�F�N�g�N���X
	*/
	class ActorObject
	{
	protected:
		std::shared_ptr<CMeshContainer>		m_pMesh;
		StateMachinePtr						m_StateMachine;
		AnimationStatePtr					m_Motion;
		ActorPtr							actor_;
		CMatrix44							m_MatWorld;
		CAABB								m_Collider;
		CVector3							m_ColliderOffset;
		CVector3							m_ColliderSize;
		bool								m_ShowFlg;
		bool								m_DeadFlg;
		CVector3							m_PrevPos;
		float								m_UltBoostMag;	//�K�E�Z�Q�[�W�̃u�[�X�g�{��
		float								m_Weight;


	public:
		ActorObject();
		virtual ~ActorObject();
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
		 * @return �A�N�^�[
		 */
		const ActorPtr& GetActor() const noexcept
		{
			return actor_;
		}
		/**
		 * @brief		�L�����^�C�v�擾
		 * @return �L�����^�C�v
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
			return m_ShowFlg;
		}
		/**
		 * @brief		�����蔻��擾
		 * @return		�����蔻��
		 */
		virtual const CAABB& GetCollider()
		{
			m_Collider.Size = m_ColliderSize;
			m_Collider.SetPosition(actor_->GetPosition() + m_ColliderOffset);

			return m_Collider;
		}
		/**
		 * @brief		�X�V�O���W�擾
		 * @return		�X�V�O���W
		 */
		const CVector3& GetPrevPos() const noexcept
		{
			return m_PrevPos;
		}
		/**
		 * @brief		�A�N�^�[ID�擾
		 * @return		�A�N�^�[ID
		 */
		size_t GetID() const noexcept
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
			return m_UltBoostMag;
		}
		/**
		 * @brief		���S���Ă��邩�H
		 * @return		true �Ȃ玀�S
		 */
		bool IsDead() const noexcept
		{
			return m_DeadFlg;
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
			m_ShowFlg = isShow;
		}
		/**
		 * @brief		���肪�l������K�E�Z�Q�[�W�̔{��
		 * @param		magnification ���肪�l������K�E�Z�Q�[�W�̔{��
		 */
		void SetUltBoostMag(float magnification) noexcept
		{
			m_UltBoostMag = magnification;
		}

		

	};
	//�|�C���^�u������
	using ActorObjectPtr = std::shared_ptr<ActorObject>;
	using ActorObjectWeakPtr = std::weak_ptr<ActorObject>;
	using ActorObjectList = std::list<ActorObjectPtr>;
}

