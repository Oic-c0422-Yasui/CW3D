#pragma once

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
	/*
	* @brief	敵クラス
	*/
	class Enemy : public ActorObject
	{
	protected:
		InputPtr m_Input;

		ParameterHandle< ReactiveParameter<int> > m_HP;
		ParameterHandle< ReactiveParameter<int> > m_MaxHP;
		ParameterHandle< ReactiveParameter<Vector3> > m_Position;

		CharacterAIPtr	m_AI;

		CVector3 m_DefaultPos;
		std::string		m_Name;
		bool			m_BossFlg;
	protected:
		//プライベート関数

		/*
		* @brief	敵のパラメータ設定
		*/
		virtual void SettingParameter(const AnyParameterMapPtr& param,
										const EnemyStatusPtr& eneStatus);
	public:
		Enemy();
		~Enemy() override;
		/*
		* @brief	読み込み
		* @param	eneParam 敵生成に使うパラメータ
		* @param	actionCreator アクションの生成
		* @param	stateCreator ステートの生成
		* @param	paramCreator パラメータの生成
		* @param	aiCreator AIの生成
		*/
		virtual bool Load(const EnemyBuildParameterPtr& eneParam,
				const ActionCreatorPtr& actionCreator,
				const StateCreatorPtr& stateCreator,
				const ParameterCreatorPtr& paramCreator,
				const CharacterAICreatorPtr& aiCreator);
		/*
		* @brief	初期化
		*/
		virtual void Initialize();
		/*
		* @brief	更新
		*/
		virtual void Update() override;
		/*
		* @brief	描画
		*/
		virtual void Render() override;
		/*
		* @brief	デバッグ描画
		*/
		virtual void RenderDebug();
		/*
		* @brief	２D描画
		*/
		virtual void Render2D();
		/*
		* @brief	２Dデバッグ描画
		*/
		virtual void Render2DDebug();
		/*
		* @brief	解放
		*/
		virtual void Release() override;
		/*
		* @brief		ダメージ処理
		* @param direction	ノックバックの方向
		* @param power	ノックバックの力
		* @param damage ダメージ量
		* @param armorBrekeLevel	アーマー破壊レベル
		*/
		virtual void Damage(const Vector3& direction, const Vector3& power, int damage,BYTE armorBrekeLevel);
		/*
		* @brief	無敵状態か？
		* @return	true なら無敵状態
		*/
		virtual bool IsInvincible() const;

		/**
		 * @brief		HP変化通知
		 */
		ActionGame::IObservable<int>* GetHPSubject() 
		{ 
			return &(m_HP.Get());
		}

		/**
		 * @brief		最大HP変化通知
		 */
		ActionGame::IObservable<int>* GetMaxHPSubject() 
		{ 
			return &(m_MaxHP.Get()); 
		}

		/**
		 * @brief		座標変化通知
		 */
		ActionGame::IObservable<Vector3>* GetPositionSubject() 
		{ 
			return &(m_Position.Get()); 
		}
		/**
		 * @brief		HPバー表示状態変化通知
		 */
		ActionGame::IObservable<bool>& GetShowSubject() 
		{ 
			return  m_Actor->GetParameterMap()->Get<ActionGame::ReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP); 
		}

		/*
		* @brief	HP取得
		* @return	HP
		*/
		int GetHP()
		{
			return m_HP.Get();
		}

		/*
		* @brief 表示用の名前取得
		* @return 表示用の名前
		*/
		const std::string& GetName() const noexcept
		{
			return m_Name;
		}
		/*
		* @brief	ボスか判断
		* @return	true　ならボス
		*/
		bool IsBoss() const noexcept
		{
			return m_BossFlg;
		}

		/*
		* @brief	座標設定
		* @param	pos 座標
		*/
		void SetPosition(const Vector3& pos) noexcept override
		{
			m_Actor->SetPosition(pos);
			m_Position = m_Actor->GetPosition();
		}
		/*
		* @brief	表示設定
		* @param	isShow 表示可否
		*/
		void SetShow(bool isShow) noexcept override
		{
			if (!isShow)
			{
				auto& showFlg = m_Actor->GetParameterMap()->Get<ActionGame::ReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP);
				showFlg = isShow;
			}
			m_ShowFlg = isShow;
		}
		
	};

	//ポインタ置き換え
	using EnemyPtr = std::shared_ptr<Enemy>;
	using EnemyArray = std::vector<EnemyPtr>;
	using EnemyArrayPtr = std::shared_ptr<EnemyArray>;
}


