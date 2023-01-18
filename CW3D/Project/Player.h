#pragma once

#include	"InputManager.h"
#include	"ResourceManager.h"
#include	"ReactiveParameter.h"
#include	"ParameterHandle.h"
#include	"ActorObject.h"
#include	"Observer.h"
#include	"PlayerActionCreator.h"
#include	"PlayerStateCreator.h"
#include	"PlayerSkillCreater.h"
#include	"PlayerParameterCreator.h"

/*
* @brief	プレイヤー
*/
class CPlayer : public ActionGame::ActorObject
{
private:

	//インプットキー
	ActionGame::InputPtr		m_pInput;

	//オブザーバー最大HP
	ActionGame::ParameterHandle< ActionGame::ReactiveParameter<int> > m_MaxHP;

	//オブザーバー最大必殺技ゲージ
	ActionGame::ParameterHandle< ActionGame::ReactiveParameter<float> > m_MaxUltGauge;

	//アクション生成
	ActionGame::PlayerActionCreator m_ActionCreator;
	//状態生成
	ActionGame::PlayerStateCreator m_StateCreator;
	//スキル生成
	ActionGame::PlayerSkillCreator m_SkillCreator;
	//パラメータ生成
	ActionGame::PlayerParameterCreator m_ParameterCreator;

	//回避時の当たり判定サイズ
	CVector3 m_EscapeColliderSize;

public:
	CPlayer();
	~CPlayer() override;
	/*
	* @brief	読み込み
	* @return	true　なら読み込み成功
	*/
	bool Load();
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
	void Damage(const Vector3& direction, const Vector3& power, int damage, BYTE armorBrakeLevel);
	
	/*
	* @brief		インプットキーの設定
	* @param ptr	インプット
	*/
	void SetInput(const ActionGame::InputPtr& ptr) noexcept
	{
		m_pInput = ptr;
	}

	/*
	* @brief		HPの取得
	* @return HP
	*/
	int GetHP() const noexcept
	{
		return m_Actor->GetParameterMap()->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	}


	/**
	* @brief		HP変化通知
	*/
	ActionGame::IObservable<int>& GetHPSubject() { return  m_Actor->GetParameterMap()->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_HP); }
	ActionGame::IObservable<int>* GetMaxHPSubject() { return &(m_MaxHP.Get()); }


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
	ActionGame::IObservable<float>* GetMaxUltSubject() { return &(m_MaxUltGauge.Get()); }
	ActionGame::IObservable<float>& GetUltSubject() { return m_Actor->GetParameterMap()->Get<ActionGame::ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE); }

	/*
	* @brief	スキルコントローラーを取得
	* @return	スキルコントローラー
	*/
	const ActionGame::SkillControllerPtr& GetSkillController() const noexcept
	{
		return m_Actor->GetSkillController();
	}
	
	/*
	* @brief	最大必殺技ゲージを取得する
	* @return	最大必殺技ゲージ
	*/
	float GetMaxUltGauge() const noexcept
	{
		return m_MaxUltGauge.Get();
	}

	/*
	* @brief	回避状態か？
	* @return	true　なら回避状態
	*/
	bool IsEscape() const
	{
		return m_Actor->GetParameterMap()->Get<bool>(PARAMETER_KEY_ESCAPE);
	}

	/*
	* @brief	無敵状態か？
	* @return	true なら無敵状態
	*/
	bool IsInvincible() const;

	/*
	* @brief	当たり判定取得
	* @return	AABBの当たり判定
	*/
	const CAABB& GetCollider() override
	{
		m_Collider.Size = m_ColliderSize;
		m_Collider.SetPosition(m_Actor->GetPosition() + m_ColliderOffset);

		return m_Collider;
	}
	
	/*
	* @brief	回避時の当たり判定取得
	* @return	AABBの当たり判定
	*/
	const CAABB& GetEscapeCollider() noexcept
	{
		m_Collider.Size = m_EscapeColliderSize;
		m_Collider.SetPosition(m_Actor->GetPosition() + m_ColliderOffset);
		return m_Collider;
	}

	/*
	* @brief	クリアポーズを開始する
	*/
	void ClearPose();
};

using PlayerPtr = std::shared_ptr<CPlayer>;