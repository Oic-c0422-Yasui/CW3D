#pragma once

#include "Utilities.h"

namespace ActionGame
{
	class CameraBase
	{
	protected:
		CCamera		m_Camera;
		CVector3	m_OffsetPos;
		CVector3	m_OffsetLookPos;
		CVector3	m_LookPos;
		CVector3	m_Position;
		CVector3	m_TargetPos;
		CVector3	m_TargetLookPos;
		bool		m_AnimEndFlg;
		bool		m_ResetFlg;

		//アニメーション用構造体
		struct animData
		{
			MyUtilities::ANIM_V3_DATA_ARRAY Pos;
			MyUtilities::ANIM_V3_DATA_ARRAY LookPos;

			bool		Flg;
			float		CurrentTime;
			int			Count;

			animData()
				: Pos()
				, LookPos()
				, Flg(false)
				, CurrentTime(0.0f)
				, Count(0)
			{
			}
			void Release()
			{
				Pos.clear();
				LookPos.clear();
			}
		};
		animData m_AnimData;

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
		* @param	offsetPos	オフセット座標アニメーション
		* @param	offsetLookPos	オフセット注視座標アニメーション
		*/
		virtual void SetAnim(const MyUtilities::ANIM_V3_DATA_ARRAY& offsetPos, const MyUtilities::ANIM_V3_DATA_ARRAY& offsetLookPos);

		/*
		* @brief	座標取得
		* @return	座標
		*/
		const CVector3& GetPos() const noexcept
		{
			return m_Position;
		}
		/*
		* @brief	注視座標取得
		* @return	注視座標
		*/
		const CVector3& GetLookPos() const noexcept
		{
			return m_LookPos;
		}
		/*
		* @brief	ターゲットの座標取得
		* @return	ターゲットの座標
		*/
		const CVector3& GetTargetPos() const noexcept
		{
			return m_TargetPos;
		}
		/*
		* @brief	ターゲットの注視座標取得
		* @return	ターゲットの注視座標
		*/
		const CVector3& GetTargetLookPos() const noexcept
		{
			return m_TargetLookPos;
		}
		/*
		* @brief	オフセット座標取得
		* @return	オフセット座標
		*/
		const CVector3& GetOffsetPos() const noexcept
		{
			return m_OffsetPos;
		}
		/*
		* @brief	オフセット注視座標取得
		* @return	オフセット注視座標
		*/
		const CVector3& GetOffsetLookPos() const noexcept
		{
			return m_OffsetLookPos;
		}
		/*
		* @brief	カメラ取得
		* @return	カメラ
		*/
		CCamera& GetCamera() noexcept
		{
			return m_Camera;
		}
		/*
		* @brief	アニメーションが終了したか？
		* @return	true　なら終了
		*/
		bool IsEnd() const noexcept
		{
			return m_AnimEndFlg;
		}
		/*
		* @brief	座標設定
		* @param	pos　座標
		*/
		void SetPos(const Vector3& pos) noexcept
		{
			m_Position = pos;
		}
		/*
		* @brief	注視座標設定
		* @param	pos　注視座標
		*/
		void SetLookPos(const Vector3& pos) noexcept
		{
			m_LookPos = pos;
		}
		/*
		* @brief	ターゲット座標設定
		* @param	pos　ターゲット座標
		*/
		void SetTargetPos(const Vector3& pos) noexcept
		{
			m_TargetPos = pos;
		}
		/*
		* @brief	ターゲット注視座標設定
		* @param	pos　ターゲット注視座標
		*/
		void SetTargetLookPos(const Vector3& pos) noexcept
		{
			m_TargetLookPos = pos;
		}
		/*
		* @brief	オフセット座標設定
		* @param	pos　オフセット座標
		*/
		void SetOffsetPos(const Vector3& pos) noexcept
		{
			m_OffsetPos = pos;
		}
		/*
		* @brief	オフセット注視座標設定
		* @param	pos　オフセット注視座標
		*/
		void SetOffsetLookPos(const Vector3& pos) noexcept
		{
			m_OffsetLookPos = pos;
		}
		/*
		* @brief	アニメーション終了設定
		* @param	isEnd　アニメーション終了フラグ
		*/
		void SetEndAnimFlg(bool isEnd) noexcept
		{
			m_AnimEndFlg = isEnd;
		}
		/*
		* @brief	リセット設定
		* @param	isReset　リセットフラグ
		*/
		void SetResetFlg(bool isReset) noexcept
		{
			m_ResetFlg = isReset;
		}
	};

	using CameraPtr = std::shared_ptr<CameraBase>;
}


