#pragma once

#include "AttackCollider.h"
#include "TimeScaleController.h"
#include "ShotParameter.h"



namespace ActionGame
{
	

	/*
	* @brief　ショットクラス
	*/
	class CShot
	{
	protected:

		//ヒット判定用構造体
		struct Hit
		{
			uint32_t ID;			//ヒットした相手のアクターID
			float Time;			//当たり判定を行わない時間
		};
		std::list<Hit>		hitIDs_;

		AttackColliderPtr	collider_;
		CAABB				AABB_;
		COBB				OBB_;
		CVector3			position_;
		float				radius_;
		CVector3			size_;
		bool				isShow_;
		COLLISION_TYPE		collisionType_;
		float				speed_;
		ShotCreateParameter param_;

	protected:
		/*		プライベート関数		*/

		//削除時間までタイマーを進める
		void UpdateTime();

		//ベースのショット作成
		void CreateBase(const Vector3& pos, const ShotCreateParameter& shot);

		//コライダーの座標を現在の座標に合わせる
		void ApplyColliderPosition();

	public:
		CShot();
		~CShot();

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
		void AddHit(uint32_t hitId)
		{
			Hit hit = { hitId, param_.nextHitTime };
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
			param_.damage += val;
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
			return param_.isEnableCollider;
		}

		/*
		* @brief	次に衝突する時間を取得
		* @return	次に衝突する時間（秒）
		*/
		float GetNextHitTime() const noexcept
		{
			return param_.nextHitTime;
		}

		/*
		* @brief	親のキャラタイプを取得
		* @return	親のキャラタイプ
		*/
		CHARA_TYPE GetParentCharaType() const noexcept
		{
			return param_.parentType;
		}

		/*
		* @brief	獲得した必殺技ゲージ量を取得
		* @return	獲得した必殺技ゲージ量
		*/
		float GetRecieveUltGauge() const noexcept
		{
			return param_.recieveUltGauge;
		}

		/*
		* @brief	親アクターのIDを取得
		* @return	親アクターのID
		*/
		uint32_t GetParentID() const noexcept
		{
			return param_.parentID;
		}

		/*
		* @brief	ノックバックの方向を取得
		* @return	ノックバックの方向
		*/
		const KnockBackPtr& GetDirection() const noexcept
		{
			return param_.direction;
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
			return param_.offset;
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
			return param_.knockBack;
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
		uint32_t GetDamage() const noexcept {
			return param_.damage;
		}

		/*
		* @brief	アーマー破壊レベルを取得
		* @return	アーマー破壊レベル
		*/
		BYTE GetArmorBreakLevel() const noexcept{
			return param_.armorBreakLevel;
		}
		
		/*
		* @brief	ダメージ用のエフェクトパラメータを取得
		* @return	ダメージ用のエフェクトパラメータ
		*/
		const EffectCreateParameterPtr& GetDamageEffect() const noexcept{
			return param_.damageEffect;
		}

		const GravityScale& GetGravityScale() const noexcept
		{
			return param_.gravity;
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
		* @param	parentType 親のキャラタイプ
		*/
		void SetParentCharaType(CHARA_TYPE type) noexcept
		{
			param_.parentType = type;
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
			param_.isEnableCollider = isEnable;
		}

		/*
		* @brief	ノックバックの力を設定
		* @param	val ノックバックの力
		*/
		void SetKnockBackPower(const Vector3& val) noexcept
		{
			param_.knockBack = val;
		}

		/*
		* @brief	X軸のノックバックの力を設定
		* @param	val X軸のノックバックの力
		*/
		void SetKnockBackPowerX(float val) noexcept
		{
			param_.knockBack.x = val;
		}

		/*
		* @brief	Y軸のノックバックの力を設定
		* @param	val Y軸のノックバックの力
		*/
		void SetKnockBackPowerY(float val) noexcept
		{
			param_.knockBack.y = val;
		}

		/*
		* @brief	Z軸のノックバックの力を設定
		* @param	val Z軸のノックバックの力
		*/
		void SetKnockBackPowerZ(float val) noexcept
		{
			param_.knockBack.z = val;
		}

		/*
		* @brief	ダメージを設定
		* @param	val ダメージ
		*/
		void SetDamage(uint32_t val) noexcept
		{
			param_.damage = val;
		}

		/*
		* @brief	次に衝突する時間を設定
		* @param	sec 次に衝突する時間（秒）
		*/
		void SetNextHitTime(float sec) noexcept
		{
			param_.nextHitTime = sec;
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
			param_.offset = offset;
		}

		/*
		* @brief	ノックバックの向きを設定
		* @param	dir ノックバックの向き
		*/
		void SetKnockBackDirection(const KnockBackPtr& dir) noexcept
		{
			param_.direction = dir;
		}

		/*
		* @brief	アーマー破壊レベルを設定
		* @param	level アーマー破壊レベル
		*/
		void SetArmorBreakLevel(BYTE level) noexcept
		{
			param_.armorBreakLevel = level;
		}

		/*
		* @brief	獲得必殺技ゲージ量を設定
		* @param	level 獲得必殺技ゲージ量
		*/
		void SetRecieveUltGauge(float gauge) noexcept
		{
			param_.recieveUltGauge = gauge;
		}

		/*
		* @brief	親アクターIDを設定
		* @param	id 親アクターID
		*/
		void SetParentID(uint32_t id)noexcept
		{
			param_.parentID = id;
		}

		/*
		* @brief	重力スケールパラメータ設定
		* @param	scale 重力スケールパラメータ
		*/
		void SetGravityScale(GravityScale scale) noexcept
		{
			param_.gravity = scale;
		}

	};

	//ポインタ置き換え
	using ShotPtr = std::shared_ptr<CShot>;
}


