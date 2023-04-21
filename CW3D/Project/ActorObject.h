#pragma once

#include	"Actor.h"
#include	"StateMachine.h"
#include	"ParameterDefine.h"
#include	"StateDefine.h"
#include	"NormalMapSkinnedParameter.h"
#include	"Shadow.h"

namespace ActionGame
{
	//メッシュポインタ
	using MeshPtr = std::shared_ptr<CMeshContainer>;

	/*
	* @brief	アクターのオブジェクトクラス
	*/
	class CActorObject
	{
	protected:
		MeshPtr									mesh_;
		MyClass::NormalMapSkinnedParameterPtr	normalMap_;
		StateMachinePtr							stateMachine_;
		AnimationStatePtr						motion_;
		ActorPtr								actor_;
		CMatrix44								matWorld_;
		CVector3								colliderOffset_;
		CVector3								colliderSize_;
		bool									isShow_;
		bool									isDead_;
		CVector3								prevPosision_;
		float									ultBoostMag_;	//必殺技ゲージのブースト倍率
		float									weight_;
		CShadow									shadow_;

	public:
		CActorObject();
		virtual ~CActorObject();
		virtual bool Load();
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
		 * @return		アクター
		 */
		const ActorPtr& GetActor() const noexcept
		{
			return actor_;
		}
		/**
		 * @brief		キャラタイプ取得
		 * @return		キャラタイプ
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
			return isShow_;
		}
		/**
		 * @brief		当たり判定取得
		 * @return		当たり判定
		 */
		virtual const CAABB& GetCollider()
		{
			return actor_->GetCollider()->GetCollider();
		}
		/**
		 * @brief		更新前座標取得
		 * @return		更新前座標
		 */
		const CVector3& GetPrevPos() const noexcept
		{
			return prevPosision_;
		}
		/**
		 * @brief		アクターID取得
		 * @return		アクターID
		 */
		uint32_t GetID() const noexcept
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
			return ultBoostMag_;
		}
		/**
		 * @brief		死亡しているか？
		 * @return		true なら死亡
		 */
		bool IsDead() const noexcept
		{
			return isDead_;
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
			isShow_ = isShow;
		}
		/**
		 * @brief		相手が獲得する必殺技ゲージの倍率
		 * @param		magnification 相手が獲得する必殺技ゲージの倍率
		 */
		void SetUltBoostMag(float magnification) noexcept
		{
			ultBoostMag_ = magnification;
		}

		

	};
	//ポインタ置き換え
	using ActorObjectPtr = std::shared_ptr<CActorObject>;
	using ActorObjectWeakPtr = std::weak_ptr<CActorObject>;
	using ActorObjectList = std::list<ActorObjectPtr>;
	using ActorObjectWeakList = std::list<ActorObjectWeakPtr>;
	using ActorObjectWeakListPtr = std::shared_ptr<ActorObjectWeakList>;
}

