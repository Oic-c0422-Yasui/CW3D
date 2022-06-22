#pragma once
#include "GameDefine.h"
#include	"InputManager.h"
#include	"ResourceManager.h"
#include	"AttackCollider.h"
#include	"ReactiveParameter.h"
#include	"ParameterHandle.h"
#include	"Observer.h"
#include	"CharacterStateAI.h"


#include	"ActorObject.h"

namespace Sample
{
	class CEnemy : public CActorObject
	{
	protected:


		InputPtr m_Input;


		AttackColliderPtr m_Collider;

		CharacterAIPtr	m_AI;

		bool	m_DeadFlg;

		ParameterHandle< ReactiveParameter<int> > m_HP;
		ParameterHandle< ReactiveParameter<int> > m_MaxHP;
		ParameterHandle< ReactiveParameter<Vector3> > m_Position;
		ParameterHandle< ReactiveParameter<bool> > m_HPShowFlg;

	public:
		CEnemy();
		~CEnemy() override;
		bool Load();
		void Initialize(CVector3 pos);
		void Update() override;
		void Render() override;
		void RenderDebug();
		void Render2D();
		void Render2DDebug();
		void Release() override;

		void Damage(const Vector3& direction, Vector3 power, int damage);

		bool IsInvincible() const;

		/*CSphere GetCollider() {
			m_Collider->SetPosition(m_Position.Get() + Vector3(0, 0.7f, 0));
			return m_Collider->GetCollider();
		}*/

		float GetSize()
		{
			return m_Collider->GetRadius();
		}

		bool IsShow()
		{
			return m_ShowFlg;
		}

		void SetShow(bool isShow)
		{
			m_ShowFlg = isShow;
		}

		const Vector3& GetPosition()
		{
			return m_Position.Get();
		}

		/**
		 * @brief		HP変化通知
		 */
		Sample::IObservable<int>* GetHPSubject() { return &(m_HP.Get()); }

		/**
		 * @brief		HP変化通知
		 */
		Sample::IObservable<int>* GetMaxHPSubject() { return &(m_MaxHP.Get()); }

		/**
		 * @brief		座標変化通知
		 */
		Sample::IObservable<Vector3>* GetPositionSubject() { return &(m_Position.Get()); }

		/**
		 * @brief		表示変化通知
		 */
		Sample::IObservable<bool>* GetShowSubject() { return &(m_HPShowFlg.Get()); }

		int GetHP()
		{
			return m_HP.Get();
		}

		void SetPosition(const Vector3& pos)
		{
			m_Actor->SetPosition(pos);
			m_Position = m_Actor->GetPosition();
		}

		


	};

	using EnemyPtr = std::shared_ptr<CEnemy>;

}


