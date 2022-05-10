#pragma once

#include	"Common.h"

namespace Sample
{
	//姿勢変換クラス
	class  Transform
	{
	
	protected:
		//座標
		CVector3	m_Position;
		//大きさ
		CVector3	m_Scale;
		//回転
		CVector3	m_Rotate;

		CMatrix44	m_World;

		bool		m_UpdateFlg;

	public:
		
		Transform() :
			m_Position(0, 0, 0),
			m_Scale(1, 1, 1),
			m_Rotate(0, 0, 0),
			m_World(),
			m_UpdateFlg(false)
		{
		}

		//マトリクスを取得
		const CMatrix44& GetWorld() {
			if (m_UpdateFlg)
			{
				UpdateMatrix();
				m_UpdateFlg = false;
			}
			return m_World;
		}


		/**
		 * @brief		座標系
		 */

			//座標の移動
			void MovePosition(CVector3 movePos) noexcept
			{
				m_Position += movePos;
				m_World.SetTranslation(m_Position);
			}

			void ClipZ(float min, float max)
			{
				m_Position.z = ((m_Position.z > max) ?
					max : ((m_Position.z < min) ? min : m_Position.z));
			}

			//座標の設定
			void SetPosition(CVector3 position) noexcept
			{
				m_Position = position;
				m_World.SetTranslation(m_Position);
			}

			//座標の設定
			void SetPositionX(float position) noexcept
			{
				m_Position.x = position;
				m_World.SetTranslation(m_Position);
			}

			//座標の設定
			void SetPositionY(float position) noexcept
			{
				m_Position.y = position;
				m_World.SetTranslation(m_Position);
			}

			//座標の設定
			void SetPositionZ(float position) noexcept
			{
				m_Position.z = position;
				m_World.SetTranslation(m_Position);
			}

			//座標の取得
			CVector3 GetPosition() const noexcept
			{
				return m_Position;
			}

			//座標の取得
			float GetPositionX() const noexcept
			{
				return m_Position.x;
			}

			//座標の取得
			float GetPositionY() const noexcept
			{
				return m_Position.y;
			}

			//座標の取得
			float GetPositionZ() const noexcept
			{
				return m_Position.z;
			}

		/**
		 * @brief		サイズ系
		 */

			 //サイズの変更
			void MoveScale(CVector3 changeScale) noexcept
			{
				m_Scale += changeScale;
				m_UpdateFlg = true;
			}

			//サイズの設定
			void SetScale(CVector3 scale) noexcept
			{
				m_Scale = scale;
				m_UpdateFlg = true;
			}

			//サイズの設定
			void SetScaleX(float scale) noexcept
			{
				m_Scale.x = scale;
				m_UpdateFlg = true;
			}

			//サイズの設定
			void SetScaleY(float scale) noexcept
			{
				m_Scale.y = scale;
				m_UpdateFlg = true;
			}

			//サイズの設定
			void SetScaleZ(float scale) noexcept
			{
				m_Scale.z = scale;
				m_UpdateFlg = true;
			}

			//サイズの取得
			CVector3 GetScale() const noexcept
			{
				return m_Scale;
			}

			//サイズの取得
			float GetScaleX() const noexcept
			{
				return m_Scale.x;
			}

			//サイズの取得
			float GetScaleY() const noexcept
			{
				return m_Scale.y;
			}

			//サイズの取得
			float GetScaleZ() const noexcept
			{
				return m_Scale.z;
			}

		/**
		 * @brief		回転系
		 */

			//回転
			void MoveRotate(CVector3 rotate) noexcept
			{
				m_Rotate += rotate;
				m_UpdateFlg = true;
			}

			//回転の設定
			void SetRotate(CVector3 rotate) noexcept
			{
				m_Rotate = rotate;
				m_UpdateFlg = true;
			}

			//回転の設定
			void SetRotateX(float rotate) noexcept
			{
				m_Rotate.x = rotate;
				m_UpdateFlg = true;
			}

			//回転の設定
			void SetRotateY(float rotate) noexcept
			{
				m_Rotate.y = rotate;
				m_UpdateFlg = true;
			}

			//回転の設定
			void SetRotateZ(float rotate) noexcept
			{
				m_Rotate.z = rotate;
				m_UpdateFlg = true;
			}

			//回転の取得
			CVector3 GetRotate() const noexcept
			{
				return m_Scale;
			}

			//回転の取得
			float GetRotateX() const noexcept
			{
				return m_Scale.x;
			}

			//回転の取得
			float GetRotateY() const noexcept
			{
				return m_Scale.y;
			}

			//回転の取得
			float GetRotateZ() const noexcept
			{
				return m_Scale.z;
			}

	private:
		void UpdateMatrix()
		{
			CMatrix44 matScale;
			CMatrix44 matRotate;
			matScale.Scaling(m_Scale);
			matRotate.RotationZXY(m_Rotate);
			m_World = matScale * matRotate;

			m_World.SetTranslation(m_Position);

			//m_World *= parent->GetWorld();
		}
	};
	//ポインタ置き換え
	using TransformPtr = std::shared_ptr<Transform>;
}
