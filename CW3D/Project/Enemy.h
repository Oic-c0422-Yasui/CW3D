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
#include	"ISkillCreator.h"

#include	"ActorObject.h"
#include	"EffectController.h"

namespace ActionGame
{
	/*
	* @brief	敵クラス
	*/
	class CEnemy : public CActorObject
	{
	protected:
		Input::InputPtr input_;

		ParameterHandle< CReactiveParameter<int> > HP_;
		ParameterHandle< CReactiveParameter<int> > maxHP_;
		ParameterHandle< CReactiveParameter<Vector3> > position_;

		CharacterAIPtr	AI_;

		Vector3			defaultPos_;
		std::string		name_;
		bool			isBoss_;
	protected:
		//プライベート関数

		/*
		* @brief	敵のパラメータ設定
		*/
		virtual void SettingParameter(const AnyParameterMapPtr& param,
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
		* @param	aiCreator	　AIの生成
		* @param	skillCreator　スキルの生成
		*/
		virtual bool Load(const EnemyBuildParameterPtr& eneParam,
				const ActionCreatorPtr& actionCreator,
				const StateCreatorPtr& stateCreator,
				const ParameterCreatorPtr& paramCreator,
				const CharacterAICreatorPtr& aiCreator,
				const SkillCreatorPtr& skillCreator);
		/*
		* @brief	初期化
		*/
		virtual void Initialize() override;
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
		* @param armorBrakeLevel アーマー破壊レベル
		*/
		void Damage(const Vector3& direction,
					const Vector3& power,
					int damage,
					BYTE armorBrakeLevel);
		/*
		* @brief		ダメージ処理(エフェクトを発生させる)
		* @param direction	ノックバックの方向
		* @param power	ノックバックの力
		* @param damage ダメージ量
		* @param armorBrakeLevel アーマー破壊レベル
		* @param effect	ダメージエフェクト
		*/
		void Damage(const Vector3& direction,
					const Vector3& power,
					int damage,
					BYTE armorBrakeLevel,
					const EffectCreateParameterPtr& effect);
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
			return &(HP_.Get());
		}

		/**
		 * @brief		最大HP変化通知
		 */
		ActionGame::IObservable<int>* GetMaxHPSubject() 
		{ 
			return &(maxHP_.Get()); 
		}

		/**
		 * @brief		座標変化通知
		 */
		ActionGame::IObservable<Vector3>* GetPositionSubject() 
		{ 
			return &(position_.Get()); 
		}
		/**
		 * @brief		HPバー表示状態変化通知
		 */
		ActionGame::IObservable<bool>& GetShowSubject() 
		{ 
			return  actor_->GetParameterMap()->Get<ActionGame::CReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP); 
		}

		/*
		* @brief	HP取得
		* @return	HP
		*/
		int GetHP()
		{
			return HP_.Get();
		}

		/*
		* @brief 表示用の名前取得
		* @return 表示用の名前
		*/
		const std::string& GetName() const noexcept
		{
			return name_;
		}
		/*
		* @brief	ボスか判断
		* @return	true　ならボス
		*/
		bool IsBoss() const noexcept
		{
			return isBoss_;
		}

		/*
		* @brief	座標設定
		* @param	pos 座標
		*/
		void SetPosition(const Vector3& pos) noexcept override
		{
			actor_->SetPosition(pos);
			position_ = actor_->GetPosition();
		}
		/*
		* @brief	表示設定
		* @param	isShow 表示可否
		*/
		void SetShow(bool isShow) noexcept override
		{
			if (!isShow)
			{
				auto& showFlg = actor_->GetParameterMap()->Get<ActionGame::CReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP);
				showFlg = isShow;
			}
			isShow_ = isShow;
		}
		
	};

	//ポインタ置き換え
	using EnemyPtr = std::shared_ptr<CEnemy>;
	using EnemyArray = std::vector<EnemyPtr>;
	using EnemyArrayPtr = std::shared_ptr<EnemyArray>;
}


