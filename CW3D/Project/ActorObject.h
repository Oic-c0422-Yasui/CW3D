#pragma once

#include	"Actor.h"
#include	"StateMachine.h"
#include	"ParameterDefine.h"
#include	"StateDefine.h"

namespace ActionGame
{
	/*
	* @brief	アクターのオブジェクトクラス
	*/
	class ActorObject
	{
	protected:
		std::shared_ptr<CMeshContainer>		m_pMesh;
		StateMachinePtr						m_StateMachine;
		AnimationStatePtr					m_Motion;
		ActorPtr							actor_;
		CMatrix44							m_MatWorld;
		CAABB								m_Collider;
		CVector3							m_ColliderOffset;
		CVector3							m_ColliderSize;
		bool								m_ShowFlg;
		bool								m_DeadFlg;
		CVector3							m_PrevPos;
		float								m_UltBoostMag;	//必殺技ゲージのブースト倍率
		float								m_Weight;


	public:
		ActorObject();
		virtual ~ActorObject();
		virtual void Initialize();
		virtual void Update();
		virtual void Render();
		virtual void Release();

		/**
		 * @brief	必殺技ゲージを追加する
		 * @param	必殺技ゲージ
		 */
		void AddUltGauge(float gauge);

		////////////////////////////////////////////////////////
		///				ゲッター
		////////////////////////////////////////////////////////
		/**
		 * @brief		アクター取得
		 * @return アクター
		 */
		const ActorPtr& GetActor() const noexcept
		{
			return actor_;
		}
		/**
		 * @brief		キャラタイプ取得
		 * @return キャラタイプ
		 */
		CHARA_TYPE GetType() const noexcept
		{
			return actor_->GetType();
		}
		/**
		 * @brief		座標取得
		 * @return		座標
		 */
		const CVector3& GetPosition() const noexcept 
		{ 
			return actor_->GetPosition(); 
		}
		/**
		 * @brief		速度取得
		 * @return		速度
		 */
		const CVector3& GetVelocity() const noexcept
		{ 
			return actor_->GetVelocity()->GetVelocity(); 
		}
		/**
		 * @brief		反転しているか？
		 * @return		true　なら反転
		 */
		bool IsReverse() const noexcept
		{ 
			return actor_->IsReverse(); 
		}
		/**
		 * @brief		回転取得
		 * @return		回転
		 */
		const CVector3& GetRotate() const noexcept
		{ 
			return actor_->GetRotate(); 
		}
		/**
		 * @brief		表示しているか？
		 * @return		true　なら表示
		 */
		virtual bool IsShow() const noexcept {
			return m_ShowFlg;
		}
		/**
		 * @brief		当たり判定取得
		 * @return		当たり判定
		 */
		virtual const CAABB& GetCollider()
		{
			m_Collider.Size = m_ColliderSize;
			m_Collider.SetPosition(actor_->GetPosition() + m_ColliderOffset);

			return m_Collider;
		}
		/**
		 * @brief		更新前座標取得
		 * @return		更新前座標
		 */
		const CVector3& GetPrevPos() const noexcept
		{
			return m_PrevPos;
		}
		/**
		 * @brief		アクターID取得
		 * @return		アクターID
		 */
		size_t GetID() const noexcept
		{
			return actor_->GetID();
		}
		/**
		 * @brief		当たり判定を無視するか？
		 * @return		true なら無視
		 */
		bool IsThroughCollision() const noexcept;
		/**
		 * @brief		必殺技ゲージのブースト倍率取得
		 * @return		必殺技ゲージのブースト倍率
		 */
		float GetUltBoostMag() const noexcept
		{
			return m_UltBoostMag;
		}
		/**
		 * @brief		死亡しているか？
		 * @return		true なら死亡
		 */
		bool IsDead() const noexcept
		{
			return m_DeadFlg;
		}

		////////////////////////////////////////////////////////
		///				セッター
		////////////////////////////////////////////////////////
		/**
		 * @brief		キャラタイプを設定
		 * @param		type キャラタイプ
		 */
		void SetType(CHARA_TYPE type) noexcept
		{
			actor_->SetType(type);
		}
		/**
		 * @brief		座標を設定
		 * @param		pos 座標
		 */
		virtual void SetPosition(const Vector3& position) noexcept
		{
			actor_->SetPosition(position);
		}
		/**
		 * @brief		表示フラグを設定
		 * @param		isShow 表示フラグ
		 */
		virtual void SetShow(bool isShow)
		{
			m_ShowFlg = isShow;
		}
		/**
		 * @brief		相手が獲得する必殺技ゲージの倍率
		 * @param		magnification 相手が獲得する必殺技ゲージの倍率
		 */
		void SetUltBoostMag(float magnification) noexcept
		{
			m_UltBoostMag = magnification;
		}

		

	};
	//ポインタ置き換え
	using ActorObjectPtr = std::shared_ptr<ActorObject>;
	using ActorObjectWeakPtr = std::weak_ptr<ActorObject>;
	using ActorObjectList = std::list<ActorObjectPtr>;
}

