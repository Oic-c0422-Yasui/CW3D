#pragma once

#include "AttackCollider.h"

#include "KnockBack.h"
#include "TimeScaleController.h"
#include "CollisionDefine.h"

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
		float getUltGauge;
		unsigned int parentID;
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
			unsigned int ID;	//ヒットした相手のアクターID
			float Time;			//当たり判定を行わない時間
		};
		std::list<Hit>		m_HitIDs;

		AttackColliderPtr	m_Collider;
		CAABB				m_AABB;
		COBB				m_OBB;
		CVector3			m_Position;
		float				m_Radius;
		CVector3			m_Size;
		Vector3				m_Offset;
		bool				m_ShowFlg;
		bool				m_EnableColliderFlg;
		CHARA_TYPE			m_ParentCharaType;
		COLLISION_TYPE		m_CollisionType;
		float				m_Speed;
		int					m_Damage;
		float				m_NextHitTime;
		KnockBackPtr		m_KnockBackDirection;
		CVector3			m_KnockBackPower;
		BYTE				m_ArmorBreakLevel;
		float				m_GetUltGauge;
		unsigned int		m_ParentID;

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
			Hit hit = { hitId, m_NextHitTime };
			m_HitIDs.push_back(hit);
		}

		/*
		* @brief	ヒット判定IDを削除
		*/
		void DeleteHitId()
		{
			auto removeIt = std::remove_if(m_HitIDs.begin(), m_HitIDs.end(), [&](const Hit& id) {
				return id.Time <= 0.0f; });
			m_HitIDs.erase(removeIt, m_HitIDs.end());
		}

		/*
		* @brief	ダメージを追加
		* @param	val ダメージ
		*/
		void AddDamage(int val) noexcept
		{
			m_Damage += val;
		}

		/*
		* @brief	座標を移動
		* @param	pos 座標
		*/
		void AddPosition(const Vector3& pos) noexcept
		{
			m_Position += pos;
		}


		//////////////////////////////////////////////
		///			ゲッター
		//////////////////////////////////////////////


		/*
		* @brief	表示しているか？
		* @return	true　なら表示
		*/
		bool IsShow() const noexcept {
			return m_ShowFlg;
		}

		/*
		* @brief	衝突判定が有効か？
		* @retval	true　なら有効
		* @retval	false　なら無効（当たり判定を行わない）
		*/
		bool IsEnableCollider() const noexcept {
			return m_EnableColliderFlg;
		}

		/*
		* @brief	次に衝突する時間を取得
		* @return	次に衝突する時間（秒）
		*/
		float GetNextHitTime() const noexcept
		{
			return m_NextHitTime;
		}

		/*
		* @brief	親のキャラタイプを取得
		* @return	親のキャラタイプ
		*/
		CHARA_TYPE GetParentCharaType() const noexcept
		{
			return m_ParentCharaType;
		}

		/*
		* @brief	獲得した必殺技ゲージ量を取得
		* @return	獲得した必殺技ゲージ量
		*/
		float GetGetUltGauge() const noexcept
		{
			return m_GetUltGauge;
		}

		/*
		* @brief	親アクターのIDを取得
		* @return	親アクターのID
		*/
		unsigned int GetParentID() const noexcept
		{
			return m_ParentID;
		}

		/*
		* @brief	ノックバックの方向を取得
		* @return	ノックバックの方向
		*/
		const KnockBackPtr& GetDirection() const noexcept
		{
			return m_KnockBackDirection;
		}

		/*
		* @brief	座標を取得
		* @return	座標
		*/
		const Vector3& GetPosition() const noexcept 
		{
			return m_Position;
		}

		/*
		* @brief	オフセット座標を取得
		* @return	オフセット座標
		*/
		const Vector3& GetOffset() const noexcept 
		{
			return m_Offset;
		}

		/*
		* @brief	当たり判定の半径を取得
		* @return	当たり判定の半径
		*/
		COLLISION_TYPE GetCollisionType() const noexcept
		{
			return m_CollisionType;
		}

		/*
		* @brief	球体の当たり判定を取得(衝突判定のタイプが球体の場合)
		* @return	球体の当たり判定
		*/
		CSphere GetColliderSphere() const noexcept 
		{
			return m_Collider->GetCollider();
		}
		/*
		* @brief	球体の半径を取得(衝突判定のタイプが球体の場合)
		* @return	球体の半径
		*/
		float GetRadius() const noexcept 
		{
			return m_Radius;
		}

		/*
		* @brief	箱の当たり判定を取得(衝突判定のタイプが箱の場合)
		* @return	箱の当たり判定
		*/
		CAABB GetColliderAABB() const noexcept 
		{
			return m_AABB;
		}

		/*
		* @brief	回転を考慮した箱の当たり判定を取得(衝突判定のタイプが回転を考慮した箱の場合)
		* @return	回転を考慮した箱の当たり判定
		*/
		COBB GetColliderOBB() const noexcept
		{
			return	m_OBB;
		}

		/*
		* @brief	ノックバックの力を取得
		* @return	ノックバックの力
		*/
		const Vector3& GetKnockBackPower() const noexcept {
			return m_KnockBackPower;
		}

		/*
		* @brief	速度を取得
		* @return	速度
		*/
		float GetSpeed() const noexcept {
			return m_Speed;
		}

		/*
		* @brief	ダメージを取得
		* @return	ダメージ
		*/
		int GetDamage() const noexcept {
			return m_Damage;
		}

		/*
		* @brief	アーマー破壊レベルを取得
		* @return	アーマー破壊レベル
		*/
		BYTE GetArmorBreakLevel() const noexcept{
			return m_ArmorBreakLevel;
		}

		/*
		* @brief	アクターとすでに衝突しているか？
		* @param	hitId　アクターのID
		* @return	true　なら衝突している
		*/
		bool IsHit(unsigned int hitId) const noexcept
		{
			for (auto& id : m_HitIDs)
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
			m_ParentCharaType = type;
		}

		/*
		* @brief	表示可否を設定
		* @param	isShow 表示可否
		*/
		void SetShow(bool isShow) noexcept
		{
			m_ShowFlg = isShow;
		}

		/*
		* @brief	衝突判定の有効化を設定
		* @param	isEnable 衝突判定の有効可否
		*/
		void SetEnableCollider(bool isEnable) noexcept
		{
			m_EnableColliderFlg = isEnable;
		}

		/*
		* @brief	ノックバックの力を設定
		* @param	val ノックバックの力
		*/
		void SetKnockBackPower(const Vector3& val) noexcept
		{
			m_KnockBackPower = val;
		}

		/*
		* @brief	X軸のノックバックの力を設定
		* @param	val X軸のノックバックの力
		*/
		void SetKnockBackPowerX(float val) noexcept
		{
			m_KnockBackPower.x = val;
		}

		/*
		* @brief	Y軸のノックバックの力を設定
		* @param	val Y軸のノックバックの力
		*/
		void SetKnockBackPowerY(float val) noexcept
		{
			m_KnockBackPower.y = val;
		}

		/*
		* @brief	Z軸のノックバックの力を設定
		* @param	val Z軸のノックバックの力
		*/
		void SetKnockBackPowerZ(float val) noexcept
		{
			m_KnockBackPower.z = val;
		}

		/*
		* @brief	ダメージを設定
		* @param	val ダメージ
		*/
		void SetDamage(int val) noexcept
		{
			m_Damage = val;
		}

		/*
		* @brief	次に衝突する時間を設定
		* @param	sec 次に衝突する時間（秒）
		*/
		void SetNextHitTime(float sec) noexcept
		{
			m_NextHitTime = sec;
		}

		/*
		* @brief	速度を設定
		* @param	val 速度
		*/
		void SetSpeed(float val) noexcept
		{
			m_Speed = val;
		}

		/*
		* @brief	座標を設定
		* @param	val 座標
		*/
		void SetPosition(const Vector3& pos) noexcept
		{
			m_Position = pos;
		}

		/*
		* @brief	オフセット座標を設定
		* @param	offset オフセット座標
		*/
		void SetOffset(const Vector3& offset) noexcept
		{
			m_Offset = offset;
		}

		/*
		* @brief	ノックバックの向きを設定
		* @param	dir ノックバックの向き
		*/
		void SetKnockBackDirection(const KnockBackPtr& dir) noexcept
		{
			m_KnockBackDirection = dir;
		}

		/*
		* @brief	アーマー破壊レベルを設定
		* @param	level アーマー破壊レベル
		*/
		void SetArmorBreakLevel(BYTE level) noexcept
		{
			m_ArmorBreakLevel = level;
		}

		/*
		* @brief	獲得必殺技ゲージ量を設定
		* @param	level 獲得必殺技ゲージ量
		*/
		void SetGetUltGauge(float gauge) noexcept
		{
			m_GetUltGauge = gauge;
		}

		/*
		* @brief	親アクターIDを設定
		* @param	id 親アクターID
		*/
		void SetParentID(unsigned int id)noexcept
		{
			m_ParentID = id;
		}

	};

	//ポインタ置き換え
	using ShotPtr = std::shared_ptr<Shot>;
}


