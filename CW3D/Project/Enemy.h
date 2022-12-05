#pragma once
#include	"GameDefine.h"
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

namespace ActionGame
{
	class CEnemy : public ActorObject
	{
	protected:
		InputPtr m_Input;

		ParameterHandle< ReactiveParameter<int> > m_HP;
		ParameterHandle< ReactiveParameter<int> > m_MaxHP;
		ParameterHandle< ReactiveParameter<Vector3> > m_Position;
		ParameterHandle< ReactiveParameter<bool> > m_HPShowFlg;

		CharacterAIPtr	m_AI;

		CVector3 m_DefaultPos;

	private:
		//プライベート関数
		/*
		* @brief	敵のパラメータ設定
		*/
		void SettingParameter(const AnyParameterMapPtr& param,
								const EnemyStatusPtr& eneStatus);
	public:
		CEnemy();
		~CEnemy() override;
		/*
		* @brief	読み込み
		* @param	eneParam 敵生成に使うパラメータ
		* @param	actionCreator アクションの生成
		* @param	stateCreator ステートの生成
		* @param	paramCreator パラメータの生成
		* @param	aiCreator AIの生成
		*/
		bool Load(const EnemyBuildParameterPtr& eneParam,
			const ActionCreatorPtr& actionCreator,
			const StateCreatorPtr& stateCreator,
			const ParameterCreatorPtr& paramCreator,
			const CharacterAICreatorPtr& aiCreator);
		/*
		* @brief	初期化
		*/
		void Initialize();
		/*
		* @brief	更新
		*/
		void Update() override;
		/*
		* @brief	描画
		*/
		void Render() override;
		/*
		* @brief	デバッグ描画
		*/
		void RenderDebug();
		/*
		* @brief	２D描画
		*/
		void Render2D();
		/*
		* @brief	２Dデバッグ描画
		*/
		void Render2DDebug();
		/*
		* @brief	解放
		*/
		void Release() override;
		/*
		* @brief		ダメージ処理
		* @param direction	ノックバックの方向
		* @param power	ノックバックの力
		* @param damage ダメージ量
		* @param level	アーマー破壊レベル
		*/
		void Damage(const Vector3& direction, const Vector3& power, int damage,BYTE level);
		/*
		* @brief	無敵状態か？
		* @return	true なら無敵状態
		*/
		bool IsInvincible() const;

		/*const Vector3& GetPosition() const noexcept
		{
			return m_Position.Get();
		}*/

		/**
		 * @brief		HP変化通知
		 */
		ActionGame::IObservable<int>* GetHPSubject() { return &(m_HP.Get()); }

		/**
		 * @brief		HP変化通知
		 */
		ActionGame::IObservable<int>* GetMaxHPSubject() { return &(m_MaxHP.Get()); }

		/**
		 * @brief		座標変化通知
		 */
		ActionGame::IObservable<Vector3>* GetPositionSubject() { return &(m_Position.Get()); }

		/**
		 * @brief		表示変化通知
		 */
		ActionGame::IObservable<bool>* GetShowSubject() { return &(m_HPShowFlg.Get()); }

		int GetHP()
		{
			return m_HP.Get();
		}

		void SetPosition(const Vector3& pos) noexcept override
		{
			m_Actor->SetPosition(pos);
			m_Position = m_Actor->GetPosition();
		}

		void SetShow(bool isShow) noexcept override
		{
			m_HPShowFlg = isShow;
			m_ShowFlg = isShow;
		}

	};

	//ポインタ置き換え
	using EnemyPtr = std::shared_ptr<CEnemy>;
	using EnemyArray = std::vector<EnemyPtr>;
	using EnemyArrayPtr = std::shared_ptr<EnemyArray>;
}


