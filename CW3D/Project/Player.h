#pragma once

#include	"InputManager.h"
#include	"ResourceManager.h"
#include	"ReactiveParameter.h"
#include	"ParameterHandle.h"
#include	"ActorObject.h"
#include	"Observer.h"
#include	"PlayerActionCreator.h"
#include	"PlayerStateCreator.h"
#include	"PlayerSkillCreator.h"
#include	"PlayerParameterCreator.h"
#include	"EffectController.h"
#include	"Combo.h"

namespace ActionGame
{

	#define COMBO_SHOW_TIME 5.0f

	/*
	* @brief	プレイヤー
	*/
	class CPlayer : public ActionGame::CActorObject
	{
	private:

		//インプットキー
		Input::InputPtr		input_;

		//オブザーバー最大HP
		ActionGame::ParameterHandle< ActionGame::CReactiveParameter<int> > maxHP_;

		//オブザーバー最大必殺技ゲージ
		ActionGame::ParameterHandle< ActionGame::CReactiveParameter<float> > maxUltGauge_;

		//アクション生成
		ActionGame::PlayerActionCreator actionCreator_;
		//状態生成
		ActionGame::PlayerStateCreator stateCreator_;
		//スキル生成
		ActionGame::PlayerSkillCreator skillCreator_;
		//パラメータ生成
		ActionGame::PlayerParameterCreator parameterCreator_;

		//回避時の当たり判定サイズ
		CVector3 escapeColliderSize_;

		//コンボ
		std::shared_ptr<CCombo>	combo_;

	public:
		CPlayer();
		~CPlayer() override;
		/*
		* @brief	読み込み
		* @return	true　なら読み込み成功
		*/
		bool Load() override;
		/*
		* @brief	初期化
		*/
		void Initialize() override;
		/*
		* @brief	更新
		*/
		void Update() override;
		/*
		* @brief	描画
		*/
		void Render() override;
		/*
		* @brief	２Dデバッグ描画
		*/
		void RenderDebug2D();
		/*
		* @brief	解放
		*/
		void Release()override;
		
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
		* @brief		インプットキーの設定
		* @param ptr	インプット
		*/
		void SetInput(const Input::InputPtr& input) noexcept
		{
			input_ = input;
		}

		/*
		* @brief		HPの取得
		* @return HP
		*/
		int GetHP() const noexcept
		{
			return actor_->GetParameterMap()->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_HP);
		}


		/*
		* @brief		HP変化通知
		*/
		ActionGame::IObservable<int>& GetHPSubject() 
		{ 
			return  actor_->GetParameterMap()->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_HP); 
		}
		ActionGame::IObservable<int>* GetMaxHPSubject() { return &(maxHP_.Get()); }

		
		/*
		* @brief		コンボ数通知
		*/
		ActionGame::IObservable<uint32_t>& GetComboSubject()
		{
			return combo_->GetCountParam();
		}

		/*
		* @brief		コンボ表示時間通知
		*/
		ActionGame::IObservable<float>& GetComboTimeSubject()
		{
			return combo_->GetTimeSubject();
		}

		/*
		* @brief		スキル取得
		* @param id	配列番号
		* @return スキル
		*/
		const ActionGame::SKillPtr& GetSkill(int id) const noexcept {
			return GetSkillController()->GetSkill(id);
		}


		/*
		* @brief		アップキャストしたスキル取得
		* @param id	配列番号
		* @return スキル
		*/
		template< typename T >
		const std::shared_ptr<T> GetCastSkill(int id) const noexcept {
			auto& skill = GetSkillController()->GetSkill(id);
			auto& castSkill = std::dynamic_pointer_cast<T>(skill);
			assert(castSkill);
			return  castSkill;
		}
		//必殺技ゲージ
		ActionGame::IObservable<float>* GetMaxUltSubject() { return &(maxUltGauge_.Get()); }
		ActionGame::IObservable<float>& GetUltSubject() { return actor_->GetParameterMap()->Get<ActionGame::CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE); }

		/*
		* @brief	スキルコントローラーを取得
		* @return	スキルコントローラー
		*/
		const ActionGame::SkillControllerPtr& GetSkillController() const noexcept
		{
			return actor_->GetSkillController();
		}

		/*
		* @brief	最大必殺技ゲージを取得する
		* @return	最大必殺技ゲージ
		*/
		float GetMaxUltGauge() const noexcept
		{
			return maxUltGauge_.Get();
		}

		/*
		* @brief	回避状態か？
		* @return	true　なら回避状態
		*/
		bool IsEscape() const
		{
			return actor_->GetParameterMap()->Get<bool>(PARAMETER_KEY_ESCAPE);
		}

		/*
		* @brief	無敵状態か？
		* @return	true なら無敵状態
		*/
		bool IsInvincible() const;


		/*
		* @brief	回避時の当たり判定取得
		* @return	AABBの当たり判定
		*/
		CAABB GetEscapeCollider() noexcept
		{
			CAABB collider(actor_->GetPosition() + colliderOffset_, escapeColliderSize_);
			return collider;
		}

		/*
		* @brief	クリアポーズを開始する
		*/
		void ClearPose();
	};

	using PlayerPtr = std::shared_ptr<CPlayer>;
}

