#pragma once

#include "AttackCollider.h"

#include "KnockBack.h"
#include "TimeScaleController.h"
#include "CollisionDefine.h"
#include "Effect.h"

namespace ActionGame
{
	//ショットパラメーター
	struct ShotCreateParameter {
		Vector3 offset;
		float	nextHitTime;
		int		damage;
		Vector3	knockBack;
		bool	collideFlg;
		CHARA_TYPE type;
		KnockBackPtr direction;
		BYTE armorBreakLevel;
		float recieveUltGauge;
		unsigned int parentID;
		EffectCreateParameterPtr damageEffect;
	};
	//球体ショット
	struct ShotSphere : public ShotCreateParameter {
		float Radius;
	};
	//箱ショット
	struct ShotAABB : public ShotCreateParameter{
		Vector3 size;
	};
	//回転を考慮した箱ショット
	struct ShotOBB : public ShotAABB {
		Vector3 angle;
	};

	/*
	* @brief　ショットクラス
	*/
	class Shot
	{
	protected:

		//ヒット判定用構造体
		struct Hit
		{
			size_t ID;			//ヒットした相手のアクターID
			float Time;			//当たり判定を行わない時間
		};
		std::list<Hit>		hitIDs_;

		AttackColliderPtr	collider_;
		CAABB				AABB_;
		COBB				OBB_;
		CVector3			position_;
		float				radius_;
		CVector3			size_;
		Vector3				offset_;
		bool				isShow_;
		bool				isEnableCollider;
		CHARA_TYPE			parentCharaType_;
		size_t				parentID_;
		COLLISION_TYPE		collisionType_;
		float				speed_;
		int					damage_;
		float				nextHitTime_;
		KnockBackPtr		knockBackDirection_;
		CVector3			knockBackPower_;
		BYTE				armorBreakLevel_;
		float				recieveUltGauge_;
		EffectCreateParameterPtr damageEffect_;

	protected:
		/*		プライベート関数		*/

		//削除時間までタイマーを進める
		void UpdateTime();

		//ベースのショット作成
		void CreateBase(const Vector3& pos, const ShotCreateParameter& shot);

		//コライダーの座標を現在の座標に合わせる
		void ApplyColliderPosition();

	public:
		Shot();
		~Shot();

		/*
		* @brief	球体のショット作成
		* @param	pos	座標
		* @param	sphere	球体用のショットパラメータ
		*/
		void Create(const Vector3& pos, const ShotSphere& sphire);
		
		/*
		* @brief	箱のショット作成
		* @param	pos	座標
		* @param	aabb	箱用のショットパラメータ
		*/
		void Create(const Vector3& pos, const ShotAABB& aabb);

		/*
		* @brief	回転を考慮した箱のショット作成
		* @param	pos	座標
		* @param	obb	箱用のショットパラメータ
		*/
		void Create(const Vector3& pos, const ShotOBB& obb);
		
		/*
		* @brief	更新
		*/
		void Update();

		/*
		* @brief	描画
		*/
		void Render();

		/*
		* @brief	ヒットした相手のIDを追加
		* @param	hitId	ヒットした相手のID
		*/
		void AddHit(unsigned int hitId)
		{
			Hit hit = { hitId, nextHitTime_ };
			hitIDs_.push_back(hit);
		}

		/*
		* @brief	ヒット判定IDを削除
		*/
		void DeleteHitId()
		{
			auto removeIt = std::remove_if(hitIDs_.begin(), hitIDs_.end(), [&](const Hit& id) {
				return id.Time <= 0.0f; });
			hitIDs_.erase(removeIt, hitIDs_.end());
		}

		/*
		* @brief	ダメージを追加
		* @param	val ダメージ
		*/
		void AddDamage(int val) noexcept
		{
			damage_ += val;
		}

		/*
		* @brief	座標を移動
		* @param	pos 座標
		*/
		void AddPosition(const Vector3& pos) noexcept
		{
			position_ += pos;
		}


		//////////////////////////////////////////////
		///			ゲッター
		//////////////////////////////////////////////


		/*
		* @brief	表示しているか？
		* @return	true　なら表示
		*/
		bool IsShow() const noexcept {
			return isShow_;
		}

		/*
		* @brief	衝突判定が有効か？
		* @retval	true　なら有効
		* @retval	false　なら無効（当たり判定を行わない）
		*/
		bool IsEnableCollider() const noexcept {
			return isEnableCollider;
		}

		/*
		* @brief	次に衝突する時間を取得
		* @return	次に衝突する時間（秒）
		*/
		float GetNextHitTime() const noexcept
		{
			return nextHitTime_;
		}

		/*
		* @brief	親のキャラタイプを取得
		* @return	親のキャラタイプ
		*/
		CHARA_TYPE GetParentCharaType() const noexcept
		{
			return parentCharaType_;
		}

		/*
		* @brief	獲得した必殺技ゲージ量を取得
		* @return	獲得した必殺技ゲージ量
		*/
		float GetRecieveUltGauge() const noexcept
		{
			return recieveUltGauge_;
		}

		/*
		* @brief	親アクターのIDを取得
		* @return	親アクターのID
		*/
		size_t GetParentID() const noexcept
		{
			return parentID_;
		}

		/*
		* @brief	ノックバックの方向を取得
		* @return	ノックバックの方向
		*/
		const KnockBackPtr& GetDirection() const noexcept
		{
			return knockBackDirection_;
		}

		/*
		* @brief	座標を取得
		* @return	座標
		*/
		const Vector3& GetPosition() const noexcept 
		{
			return position_;
		}

		/*
		* @brief	オフセット座標を取得
		* @return	オフセット座標
		*/
		const Vector3& GetOffset() const noexcept 
		{
			return offset_;
		}

		/*
		* @brief	当たり判定の半径を取得
		* @return	当たり判定の半径
		*/
		COLLISION_TYPE GetCollisionType() const noexcept
		{
			return collisionType_;
		}

		/*
		* @brief	球体の当たり判定を取得(衝突判定のタイプが球体の場合)
		* @return	球体の当たり判定
		*/
		CSphere GetColliderSphere() const noexcept 
		{
			return collider_->GetCollider();
		}
		/*
		* @brief	球体の半径を取得(衝突判定のタイプが球体の場合)
		* @return	球体の半径
		*/
		float GetRadius() const noexcept 
		{
			return radius_;
		}

		/*
		* @brief	箱の当たり判定を取得(衝突判定のタイプが箱の場合)
		* @return	箱の当たり判定
		*/
		CAABB GetColliderAABB() const noexcept 
		{
			return AABB_;
		}

		/*
		* @brief	回転を考慮した箱の当たり判定を取得(衝突判定のタイプが回転を考慮した箱の場合)
		* @return	回転を考慮した箱の当たり判定
		*/
		COBB GetColliderOBB() const noexcept
		{
			return	OBB_;
		}

		/*
		* @brief	ノックバックの力を取得
		* @return	ノックバックの力
		*/
		const Vector3& GetKnockBackPower() const noexcept {
			return knockBackPower_;
		}

		/*
		* @brief	速度を取得
		* @return	速度
		*/
		float GetSpeed() const noexcept {
			return speed_;
		}

		/*
		* @brief	ダメージを取得
		* @return	ダメージ
		*/
		int GetDamage() const noexcept {
			return damage_;
		}

		/*
		* @brief	アーマー破壊レベルを取得
		* @return	アーマー破壊レベル
		*/
		BYTE GetArmorBreakLevel() const noexcept{
			return armorBreakLevel_;
		}
		
		/*
		* @brief	ダメージ用のエフェクトパラメータを取得
		* @return	ダメージ用のエフェクトパラメータ
		*/
		const EffectCreateParameterPtr& GetDamageEffect() const noexcept{
			return damageEffect_;
		}

		/*
		* @brief	アクターとすでに衝突しているか？
		* @param	hitId　アクターのID
		* @return	true　なら衝突している
		*/
		bool IsHit(unsigned int hitId) const noexcept
		{
			for (auto& id : hitIDs_)
			{
				if (id.ID == hitId)
				{
					return true;
				}
			}
			return false;
		}

		//////////////////////////////////////////////
		///			セッター
		//////////////////////////////////////////////

		/*
		* @brief	親のキャラタイプを設定
		* @param	type 親のキャラタイプ
		*/
		void SetParentCharaType(CHARA_TYPE type) noexcept
		{
			parentCharaType_ = type;
		}

		/*
		* @brief	表示可否を設定
		* @param	isShow 表示可否
		*/
		void SetShow(bool isShow) noexcept
		{
			isShow_ = isShow;
		}

		/*
		* @brief	衝突判定の有効化を設定
		* @param	isEnable 衝突判定の有効可否
		*/
		void SetEnableCollider(bool isEnable) noexcept
		{
			isEnableCollider = isEnable;
		}

		/*
		* @brief	ノックバックの力を設定
		* @param	val ノックバックの力
		*/
		void SetKnockBackPower(const Vector3& val) noexcept
		{
			knockBackPower_ = val;
		}

		/*
		* @brief	X軸のノックバックの力を設定
		* @param	val X軸のノックバックの力
		*/
		void SetKnockBackPowerX(float val) noexcept
		{
			knockBackPower_.x = val;
		}

		/*
		* @brief	Y軸のノックバックの力を設定
		* @param	val Y軸のノックバックの力
		*/
		void SetKnockBackPowerY(float val) noexcept
		{
			knockBackPower_.y = val;
		}

		/*
		* @brief	Z軸のノックバックの力を設定
		* @param	val Z軸のノックバックの力
		*/
		void SetKnockBackPowerZ(float val) noexcept
		{
			knockBackPower_.z = val;
		}

		/*
		* @brief	ダメージを設定
		* @param	val ダメージ
		*/
		void SetDamage(int val) noexcept
		{
			damage_ = val;
		}

		/*
		* @brief	次に衝突する時間を設定
		* @param	sec 次に衝突する時間（秒）
		*/
		void SetNextHitTime(float sec) noexcept
		{
			nextHitTime_ = sec;
		}

		/*
		* @brief	速度を設定
		* @param	val 速度
		*/
		void SetSpeed(float val) noexcept
		{
			speed_ = val;
		}

		/*
		* @brief	座標を設定
		* @param	val 座標
		*/
		void SetPosition(const Vector3& pos) noexcept
		{
			position_ = pos;
		}

		/*
		* @brief	オフセット座標を設定
		* @param	offset オフセット座標
		*/
		void SetOffset(const Vector3& offset) noexcept
		{
			offset_ = offset;
		}

		/*
		* @brief	ノックバックの向きを設定
		* @param	dir ノックバックの向き
		*/
		void SetKnockBackDirection(const KnockBackPtr& dir) noexcept
		{
			knockBackDirection_ = dir;
		}

		/*
		* @brief	アーマー破壊レベルを設定
		* @param	level アーマー破壊レベル
		*/
		void SetArmorBreakLevel(BYTE level) noexcept
		{
			armorBreakLevel_ = level;
		}

		/*
		* @brief	獲得必殺技ゲージ量を設定
		* @param	level 獲得必殺技ゲージ量
		*/
		void SetRecieveUltGauge(float gauge) noexcept
		{
			recieveUltGauge_ = gauge;
		}

		/*
		* @brief	親アクターIDを設定
		* @param	id 親アクターID
		*/
		void SetParentID(size_t id)noexcept
		{
			parentID_ = id;
		}

	};

	//ポインタ置き換え
	using ShotPtr = std::shared_ptr<Shot>;
}


