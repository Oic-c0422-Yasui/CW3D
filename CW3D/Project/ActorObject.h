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
		bool								m_ShowFlg;
		bool								m_DeadFlg;
	public:
		CActorObject();
		virtual ~CActorObject();
		virtual void Update();
		virtual void Render();
		virtual void Release();

		const ActorPtr& GetActor()
		{
			return m_Actor;
		}
		const Vector3& GetPosition() const noexcept 
		{ 
			return m_Actor->GetPosition(); 
		}
		void SetPosition(const Vector3& position)
		{
			m_Actor->SetPosition(position);
		}
		const Vector3& GetVelocity() const noexcept
		{ 
			return m_Actor->GetVelocity()->GetVelocity(); 
		}
		const bool& IsReverse() const noexcept
		{ 
			return m_Actor->IsReverse(); 
		}
		const Vector3& GetRotate() const noexcept
		{ 
			return m_Actor->GetRotate(); 
		}
		const bool& IsShow() const noexcept {
			return m_ShowFlg;
		}
		void SetShow(bool isShow)
		{
			m_ShowFlg = isShow;
		}
		CAABB GetCollider()
		{
			m_Collider.SetPosition(m_Actor->GetPosition() + m_ColliderOffset);

			return m_Collider;
		}

	};
	//ポインタ置き換え
	using ActorObjectPtr = std::shared_ptr<CActorObject>;
	using ActorObjectList = std::list<ActorObjectPtr>;
}

