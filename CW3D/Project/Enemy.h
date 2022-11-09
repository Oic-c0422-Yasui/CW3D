#pragma once
#include "GameDefine.h"
#include	"InputManager.h"
#include	"ResourceManager.h"
#include	"ParameterHandle.h"
#include	"Observer.h"
#include	"IActionCreator.h"
#include	"IStateCreator.h"
#include	"IParameterCreator.h"
#include	"ICharacterAICreator.h"
#include	"EnemyBuildParameter.h"

#include	"ActorObject.h"

namespace Sample
{
	class CEnemy : public CActorObject
	{
	protected:
		InputPtr m_Input;

		ParameterHandle< ReactiveParameter<int> > m_HP;
		ParameterHandle< ReactiveParameter<int> > m_MaxHP;
		ParameterHandle< ReactiveParameter<Vector3> > m_Position;
		ParameterHandle< ReactiveParameter<bool> > m_HPShowFlg;

		ActionCreatorPtr	 m_ActionCreator;
		StateCreatorPtr	m_StateCreator;
		ParameterCreatorPtr m_ParameterCreator;
		CharacterAIPtr	m_AI;

		CVector3 m_DefaultPos;

	private:
		//プライベート関数
		void SettingParameter(const AnyParameterMapPtr& param,
								const EnemyStatusPtr& eneStatus);
	public:
		CEnemy();
		~CEnemy() override;
		bool Load(const EnemyBuildParameter& eneParam,
			const ActionCreatorPtr& actionCreator,
			const StateCreatorPtr& stateCreator,
			const ParameterCreatorPtr& paramCreator,
			const CharacterAICreatorPtr& aiCreator);
		void Initialize();
		void Update() override;
		void Render() override;
		void RenderDebug();
		void Render2D();
		void Render2DDebug();
		void Release() override;

		void Damage(const Vector3& direction, const Vector3& power, int damage,BYTE level);

		bool IsInvincible() const;


		bool IsShow() const noexcept
		{
			return m_ShowFlg;
		}

		void SetShow(bool isShow) noexcept
		{
			m_HPShowFlg = isShow;
			m_ShowFlg = isShow;
		}

		const Vector3& GetPosition() const noexcept
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

	//ポインタ置き換え
	using EnemyPtr = std::shared_ptr<CEnemy>;
	using EnemyArray = std::vector<EnemyPtr>;
	using EnemyArrayPtr = std::shared_ptr<EnemyArray>;
}


