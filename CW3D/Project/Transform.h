#pragma once

#include	"Common.h"
#include	"Utilities.h"
#include	"Velocity.h"


namespace ActionGame
{
	/*
	* @brief	姿勢変換クラス
	*/
	class  Transform
	{
	
	protected:

		CVector3	m_Position;

		CVector3	m_Scale;

		CVector3	m_Rotate;

		CMatrix44	m_World;

		bool		m_UpdateFlg;

		bool		m_ReverseFlg;

		CHARA_TYPE m_Type;

	private:
		/* プライベート関数　*/

		//マトリクス情報更新
		void UpdateMatrix();

	public:
		
		Transform();

		//マトリクスを取得
		/*
		* @brief	マトリクスを取得
		* @return	マトリクス
		*/
		const CMatrix44& GetWorld() {
			if (m_UpdateFlg)
			{
				UpdateMatrix();
				m_UpdateFlg = false;
			}
			return m_World;
		}

		/*
		* @brief	反転設定
		* @param	isReverse 反転可否
		*/
		void SetReverse(bool isReverse) noexcept
		{
			m_ReverseFlg = isReverse;
		}

		/*
		* @brief	反転しているか？
		* @return	true　なら反転
		*/
		bool IsReverse() const noexcept
		{
			return m_ReverseFlg;
		}
		/*
		* @brief	反転しているか？
		* @return	true　なら反転
		*/
		void SetType(CHARA_TYPE type) noexcept
		{
			m_Type = type;
		}

		////////////////////////////////////////////////////////////////
		///			座標系
		////////////////////////////////////////////////////////////////

			/*
			 * @brief		座標移動
			 * @param		position 移動座標
			 */
			void AddPosition(const Vector3& position) noexcept;

			/*
			 * @brief		座標移動
			 * @param		velocity 速度クラス
			 */
			void AddPosition(const VelocityPtr& velocity) noexcept;
			

			/*
			* @brief	座標制限
			* @param	min	最小座標
			* @param	max	最大座標
			*/
			void Clip(const Vector3& min, const  Vector3& max);

			/*
			* @brief	X座標制限
			* @param	min	最小座標
			* @param	max	最大座標
			*/
			void ClipX(float min, float max);
			

			/*
			* @brief	Y座標制限
			* @param	min	最小座標
			* @param	max	最大座標
			*/
			void ClipY(float min, float max);

			/*
			* @brief	X座標制限
			* @param	min	最小座標
			* @param	max	最大座標
			*/
			void ClipZ(float min, float max);


			/*
			* @brief	座標設定
			* @param	position	座標
			*/
			void SetPosition(const Vector3& position) noexcept;


			/*
			* @brief	X座標設定
			* @param	position	X座標
			*/
			void SetPositionX(float position) noexcept
			{
				m_Position.x = position;
				m_World.SetTranslation(m_Position);
			}

			/*
			* @brief	Y座標設定
			* @param	position	Y座標
			*/
			void SetPositionY(float position) noexcept
			{
				m_Position.y = position;
				m_World.SetTranslation(m_Position);
			}

			/*
			* @brief	Z座標設定
			* @param	position	Z座標
			*/
			void SetPositionZ(float position) noexcept
			{
				m_Position.z = position;
				m_World.SetTranslation(m_Position);
			}

			/*
			* @brief	座標取得
			* @return	座標
			*/
			const CVector3& GetPosition() const noexcept
			{
				return m_Position;
			}

			/*
			* @brief	X座標取得
			* @return	X座標
			*/
			float GetPositionX() const noexcept
			{
				return m_Position.x;
			}

			/*
			* @brief	Y座標取得
			* @return	Y座標
			*/
			float GetPositionY() const noexcept
			{
				return m_Position.y;
			}

			/*
			* @brief	Z座標取得
			* @return	Z座標
			*/
			float GetPositionZ() const noexcept
			{
				return m_Position.z;
			}

		////////////////////////////////////////////////////////////////
		///			大きさ系
		////////////////////////////////////////////////////////////////

			/*
			* @brief	大きさの変更
			* @param	changeScale 大きさ
			*/
			void AddScale(const Vector3& changeScale) noexcept
			{
				m_Scale += changeScale;
				m_UpdateFlg = true;
			}

			/*
			* @brief	大きさの設定
			* @param	scale 大きさ
			*/
			void SetScale(const Vector3& scale) noexcept
			{
				m_Scale = scale;
				m_UpdateFlg = true;
			}

			/*
			* @brief	Xの大きさ設定
			* @param	scale Xの大きさ
			*/
			void SetScaleX(float scale) noexcept
			{
				m_Scale.x = scale;
				m_UpdateFlg = true;
			}

			/*
			* @brief	Xの大きさ設定
			* @param	scale Yの大きさ
			*/
			void SetScaleY(float scale) noexcept
			{
				m_Scale.y = scale;
				m_UpdateFlg = true;
			}

			/*
			* @brief	Xの大きさ設定
			* @param	scale Zの大きさ
			*/
			void SetScaleZ(float scale) noexcept
			{
				m_Scale.z = scale;
				m_UpdateFlg = true;
			}

			/*
			* @brief	大きさ取得
			* @return	大きさ
			*/
			const CVector3& GetScale() const noexcept
			{
				return m_Scale;
			}

			/*
			* @brief	Xの大きさ取得
			* @return	Xの大きさ
			*/
			float GetScaleX() const noexcept
			{
				return m_Scale.x;
			}

			/*
			* @brief	Yの大きさ取得
			* @return	Yの大きさ
			*/
			float GetScaleY() const noexcept
			{
				return m_Scale.y;
			}

			/*
			* @brief	Zの大きさ取得
			* @return	Zの大きさ
			*/
			float GetScaleZ() const noexcept
			{
				return m_Scale.z;
			}

		////////////////////////////////////////////////////////////////
		///			回転系
		////////////////////////////////////////////////////////////////

			/*
			* @brief	追加回転
			* @param	rotate	回転値
			*/
			void AddRotate(const Vector3& rotate) noexcept
			{
				m_Rotate += rotate;
				m_UpdateFlg = true;
			}

			/*
			* @brief	回転の設定
			* @param	rotate	回転値
			*/
			void SetRotate(const Vector3& rotate) noexcept
			{
				m_Rotate = rotate;
				m_UpdateFlg = true;
			}

			/*
			* @brief	X回転の設定
			* @param	rotate	X回転値
			*/
			void SetRotateX(float rotate) noexcept
			{
				m_Rotate.x = rotate;
				m_UpdateFlg = true;
			}

			/*
			* @brief	Y回転の設定
			* @param	rotate	Y回転値
			*/
			void SetRotateY(float rotate) noexcept
			{
				m_Rotate.y = rotate;
				m_UpdateFlg = true;
			}

			/*
			* @brief	Z回転の設定
			* @param	rotate	Z回転値
			*/
			void SetRotateZ(float rotate) noexcept
			{
				m_Rotate.z = rotate;
				m_UpdateFlg = true;
			}

			/*
			* @brief	回転の取得
			* @return	回転値
			*/
			const CVector3& GetRotate() const noexcept
			{
				return m_Rotate;
			}

			/*
			* @brief	X回転の取得
			* @return	X回転値
			*/
			float GetRotateX() const noexcept
			{
				return m_Rotate.x;
			}

			/*
			* @brief	Y回転の取得
			* @return	Y回転値
			*/
			float GetRotateY() const noexcept
			{
				return m_Rotate.y;
			}

			/*
			* @brief	Z回転の取得
			* @return	Z回転値
			*/
			float GetRotateZ() const noexcept
			{
				return m_Rotate.z;
			}

	
	};
	//ポインタ置き換え
	using TransformPtr = std::shared_ptr<Transform>;
}
