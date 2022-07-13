#pragma once

#include	"Actor.h"
#include	"StateMachine.h"

namespace Sample
{

	class CActorObject
	{
	protected:
		std::shared_ptr<CMeshContainer>		m_pMesh;
		StateMachinePtr						m_StateMachine;
		AnimationStatePtr					m_Motion;
		ActorPtr							m_Actor;
		CMatrix44							matWorld;
		CAABB								m_Collider;
		CVector3							m_ColliderOffset;
		CVector3							m_ColliderSize;
		bool								m_ShowFlg;
		bool								m_DeadFlg;
		CVector3							m_PrevPos;
		float								m_UltBoostMag;

	public:
		CActorObject();
		virtual ~CActorObject();
		virtual void Initialize();
		virtual void Update();
		virtual void Render();
		virtual void Release();

		/**
		 * @brief		ゲッター
		 */
		const ActorPtr& GetActor() const noexcept
		{
			return m_Actor;
		}
		CHARACTER_TYPE GetType() const noexcept
		{
			return m_Actor->GetType();
		}
		const CVector3& GetPosition() const noexcept 
		{ 
			return m_Actor->GetPosition(); 
		}
		const CVector3& GetVelocity() const noexcept
		{ 
			return m_Actor->GetVelocity()->GetVelocity(); 
		}
		bool IsReverse() const noexcept
		{ 
			return m_Actor->IsReverse(); 
		}
		const CVector3& GetRotate() const noexcept
		{ 
			return m_Actor->GetRotate(); 
		}
		bool IsShow() const noexcept {
			return m_ShowFlg;
		}
		virtual const CAABB& GetCollider()
		{
			m_Collider.Size = m_ColliderSize;
			m_Collider.SetPosition(m_Actor->GetPosition() + m_ColliderOffset);

			return m_Collider;
		}
		const CVector3& GetPrevPos() const noexcept
		{
			return m_PrevPos;
		}
		unsigned int GetID() const noexcept
		{
			return m_Actor->GetID();
		}
		bool IsThrough() const noexcept
		{
			return m_Actor->IsThrough();
		}
		float GetUltBoostMag() const noexcept
		{
			return m_UltBoostMag;
		}
		bool IsDead() const noexcept
		{
			return m_DeadFlg;
		}
		/**
		 * @brief		セッター
		 */
		void SetType(CHARACTER_TYPE type) noexcept
		{
			m_Actor->SetType(type);
		}
		void SetPosition(const Vector3& position) noexcept
		{
			m_Actor->SetPosition(position);
		}
		void SetShow(bool isShow)
		{
			m_ShowFlg = isShow;
		}
		void SetUltBoostMag(float magnification) noexcept
		{
			m_UltBoostMag = magnification;
		}

		/**
		 * @brief	必殺技ゲージ
		 */
		void AddUltGauge(float gauge);

	};
	//ポインタ置き換え
	using ActorObjectPtr = std::shared_ptr<CActorObject>;
	using ActorObjectWeakPtr = std::weak_ptr<CActorObject>;
	using ActorObjectList = std::list<ActorObjectPtr>;
}

