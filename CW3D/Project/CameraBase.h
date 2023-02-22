#pragma once

#include "Utilities.h"

namespace ActionGame
{
	class CameraBase
	{
	protected:
		CCamera		camera_;
		CVector3	offsetPos_;
		CVector3	offsetLookPos_;
		CVector3	lookPos_;
		CVector3	position_;
		CVector3	targetPos_;
		CVector3	targetLookPos_;
		bool		isEndAnimation_;
		bool		isReset_;

		//アニメーション用構造体
		struct AnimationData
		{
			MyUtil::ANIM_V3_DATA_ARRAY posAnim;
			MyUtil::ANIM_V3_DATA_ARRAY lookPosAnim;

			bool		isAnimation;
			float		currentTime;
			int			count;

			AnimationData()
				: posAnim()
				, lookPosAnim()
				, isAnimation(false)
				, currentTime(0.0f)
				, count(0)
			{
			}
			void Release()
			{
				posAnim.clear();
				lookPosAnim.clear();
			}
		};
		AnimationData animationData_;

	public:
		CameraBase(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos);
		virtual ~CameraBase() {};
		/*
		* @brief	生成
		*/
		virtual void Create();
		/*
		* @brief	更新
		* @param	pos	座標
		* @param	lookPos	注視座標
		*/
		virtual void Update(const Vector3& pos, const Vector3& lookPos) = 0;
		/*
		* @brief	カメラの更新
		*/
		virtual void UpdateCamera();
		/*
		* @brief	デバッグ２D描画
		*/
		virtual void Render2DDebug();
		/*
		* @brief	カメラ座標更新適用
		* @param	pos	座標
		* @param	lookPos	注視座標
		*/
		virtual void Enable(const Vector3& pos, const Vector3& lookPos);
		/*
		* @brief	アニメーション設定
		* @param	posAnim	座標のアニメーション配列
		* @param	lookPosAnim	注視座標のアニメーション配列
		*/
		virtual void SetAnimation(const MyUtil::ANIM_V3_DATA_ARRAY& posAnim, const MyUtil::ANIM_V3_DATA_ARRAY& lookPosAnim);

		/*
		* @brief	座標取得
		* @return	座標
		*/
		const CVector3& GetPosition() const noexcept
		{
			return position_;
		}
		/*
		* @brief	注視座標取得
		* @return	注視座標
		*/
		const CVector3& GetLookPos() const noexcept
		{
			return lookPos_;
		}
		/*
		* @brief	ターゲットの座標取得
		* @return	ターゲットの座標
		*/
		const CVector3& GetTargetPos() const noexcept
		{
			return targetPos_;
		}
		/*
		* @brief	ターゲットの注視座標取得
		* @return	ターゲットの注視座標
		*/
		const CVector3& GetTargetLookPos() const noexcept
		{
			return targetLookPos_;
		}
		/*
		* @brief	オフセット座標取得
		* @return	オフセット座標
		*/
		const CVector3& GetOffsetPos() const noexcept
		{
			return offsetPos_;
		}
		/*
		* @brief	オフセット注視座標取得
		* @return	オフセット注視座標
		*/
		const CVector3& GetOffsetLookPos() const noexcept
		{
			return offsetLookPos_;
		}
		/*
		* @brief	カメラ取得
		* @return	カメラ
		*/
		CCamera& GetCamera() noexcept
		{
			return camera_;
		}
		/*
		* @brief	アニメーションが終了したか？
		* @return	true　なら終了
		*/
		bool IsEnd() const noexcept
		{
			return isEndAnimation_;
		}
		/*
		* @brief	座標設定
		* @param	pos　座標
		*/
		void SetPos(const Vector3& pos) noexcept
		{
			position_ = pos;
		}
		/*
		* @brief	注視座標設定
		* @param	pos　注視座標
		*/
		void SetLookPos(const Vector3& pos) noexcept
		{
			lookPos_ = pos;
		}
		/*
		* @brief	ターゲット座標設定
		* @param	pos　ターゲット座標
		*/
		void SetTargetPos(const Vector3& pos) noexcept
		{
			targetPos_ = pos;
		}
		/*
		* @brief	ターゲット注視座標設定
		* @param	pos　ターゲット注視座標
		*/
		void SetTargetLookPos(const Vector3& pos) noexcept
		{
			targetLookPos_ = pos;
		}
		/*
		* @brief	オフセット座標設定
		* @param	pos　オフセット座標
		*/
		void SetOffsetPos(const Vector3& pos) noexcept
		{
			offsetPos_ = pos;
		}
		/*
		* @brief	オフセット注視座標設定
		* @param	pos　オフセット注視座標
		*/
		void SetOffsetLookPos(const Vector3& pos) noexcept
		{
			offsetLookPos_ = pos;
		}
		/*
		* @brief	アニメーション終了設定
		* @param	isEnd　アニメーション終了フラグ
		*/
		void SetIsEndAnimation(bool isEnd) noexcept
		{
			isEndAnimation_ = isEnd;
		}
		/*
		* @brief	リセット設定
		* @param	isReset　リセットフラグ
		*/
		void SetIsReset(bool isReset) noexcept
		{
			isReset_ = isReset;
		}
	};

	using CameraPtr = std::shared_ptr<CameraBase>;
}


