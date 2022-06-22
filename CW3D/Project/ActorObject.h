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
		BYTE								m_ArmorLevel;
		CVector3							m_PrevPos;

	public:
		CActorObject();
		virtual ~CActorObject();
		virtual void Update();
		virtual void Render();
		virtual void Release();

		const ActorPtr& GetActor() const noexcept
		{
			return m_Actor;
		}
		CHARACTER_TYPE GetType() const noexcept
		{
			return m_Actor->GetType();
		}
		void SetType(CHARACTER_TYPE type) noexcept
		{
			m_Actor->SetType(type);
		}

		const CVector3& GetPosition() const noexcept 
		{ 
			return m_Actor->GetPosition(); 
		}
		void SetPosition(const Vector3& position) noexcept
		{
			m_Actor->SetPosition(position);
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
		void SetShow(bool isShow)
		{
			m_ShowFlg = isShow;
		}
		BYTE GetArmorLevel() const noexcept
		{
			return m_ArmorLevel;
		}
		void SetArmorLevel(BYTE level) noexcept
		{
			m_ArmorLevel = level;
		}

		const CAABB& GetCollider()
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

	};
	//ポインタ置き換え
	using ActorObjectPtr = std::shared_ptr<CActorObject>;
	using ActorObjectList = std::list<ActorObjectPtr>;
}

