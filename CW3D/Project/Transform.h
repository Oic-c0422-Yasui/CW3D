#pragma once

#include	"Common.h"
#include	"Utilities.h"
#include	"Velocity.h"


namespace ActionGame
{
	/*
	* @brief	姿勢変換クラス
	*/
	class  CTransform
	{
	
	protected:

		CVector3	position_;

		CVector3	scale_;

		CVector3	rotate_;

		CMatrix44	world_;

		bool		isUpdate_;

		bool		isReverse_;

		CHARA_TYPE type_;

	private:
		/* プライベート関数　*/

		//マトリクス情報更新
		void UpdateMatrix();

	public:
		
		CTransform();

		//マトリクスを取得
		/*
		* @brief	マトリクスを取得
		* @return	マトリクス
		*/
		const CMatrix44& GetWorld() {
			if (isUpdate_)
			{
				UpdateMatrix();
				isUpdate_ = false;
			}
			return world_;
		}

		/*
		* @brief	反転設定
		* @param	isReverse 反転可否
		*/
		void SetReverse(bool isReverse) noexcept
		{
			isReverse_ = isReverse;
		}

		/*
		* @brief	反転しているか？
		* @return	true　なら反転
		*/
		bool IsReverse() const noexcept
		{
			return isReverse_;
		}
		/*
		* @brief	反転しているか？
		* @return	true　なら反転
		*/
		void SetType(CHARA_TYPE type) noexcept
		{
			type_ = type;
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
				position_.x = position;
				world_.SetTranslation(position_);
			}

			/*
			* @brief	Y座標設定
			* @param	position	Y座標
			*/
			void SetPositionY(float position) noexcept
			{
				position_.y = position;
				world_.SetTranslation(position_);
			}

			/*
			* @brief	Z座標設定
			* @param	position	Z座標
			*/
			void SetPositionZ(float position) noexcept
			{
				position_.z = position;
				world_.SetTranslation(position_);
			}

			/*
			* @brief	座標取得
			* @return	座標
			*/
			const CVector3& GetPosition() const noexcept
			{
				return position_;
			}

			/*
			* @brief	X座標取得
			* @return	X座標
			*/
			float GetPositionX() const noexcept
			{
				return position_.x;
			}

			/*
			* @brief	Y座標取得
			* @return	Y座標
			*/
			float GetPositionY() const noexcept
			{
				return position_.y;
			}

			/*
			* @brief	Z座標取得
			* @return	Z座標
			*/
			float GetPositionZ() const noexcept
			{
				return position_.z;
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
				scale_ += changeScale;
				isUpdate_ = true;
			}

			/*
			* @brief	大きさの設定
			* @param	scale 大きさ
			*/
			void SetScale(const Vector3& scale) noexcept
			{
				scale_ = scale;
				isUpdate_ = true;
			}

			/*
			* @brief	Xの大きさ設定
			* @param	scale Xの大きさ
			*/
			void SetScaleX(float scale) noexcept
			{
				scale_.x = scale;
				isUpdate_ = true;
			}

			/*
			* @brief	Xの大きさ設定
			* @param	scale Yの大きさ
			*/
			void SetScaleY(float scale) noexcept
			{
				scale_.y = scale;
				isUpdate_ = true;
			}

			/*
			* @brief	Xの大きさ設定
			* @param	scale Zの大きさ
			*/
			void SetScaleZ(float scale) noexcept
			{
				scale_.z = scale;
				isUpdate_ = true;
			}

			/*
			* @brief	大きさ取得
			* @return	大きさ
			*/
			const CVector3& GetScale() const noexcept
			{
				return scale_;
			}

			/*
			* @brief	Xの大きさ取得
			* @return	Xの大きさ
			*/
			float GetScaleX() const noexcept
			{
				return scale_.x;
			}

			/*
			* @brief	Yの大きさ取得
			* @return	Yの大きさ
			*/
			float GetScaleY() const noexcept
			{
				return scale_.y;
			}

			/*
			* @brief	Zの大きさ取得
			* @return	Zの大きさ
			*/
			float GetScaleZ() const noexcept
			{
				return scale_.z;
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
				rotate_ += rotate;
				isUpdate_ = true;
			}

			/*
			* @brief	回転の設定
			* @param	rotate	回転値
			*/
			void SetRotate(const Vector3& rotate) noexcept
			{
				rotate_ = rotate;
				isUpdate_ = true;
			}

			/*
			* @brief	X回転の設定
			* @param	rotate	X回転値
			*/
			void SetRotateX(float rotate) noexcept
			{
				rotate_.x = rotate;
				isUpdate_ = true;
			}

			/*
			* @brief	Y回転の設定
			* @param	rotate	Y回転値
			*/
			void SetRotateY(float rotate) noexcept
			{
				rotate_.y = rotate;
				isUpdate_ = true;
			}

			/*
			* @brief	Z回転の設定
			* @param	rotate	Z回転値
			*/
			void SetRotateZ(float rotate) noexcept
			{
				rotate_.z = rotate;
				isUpdate_ = true;
			}

			/*
			* @brief	回転の取得
			* @return	回転値
			*/
			const CVector3& GetRotate() const noexcept
			{
				return rotate_;
			}

			/*
			* @brief	X回転の取得
			* @return	X回転値
			*/
			float GetRotateX() const noexcept
			{
				return rotate_.x;
			}

			/*
			* @brief	Y回転の取得
			* @return	Y回転値
			*/
			float GetRotateY() const noexcept
			{
				return rotate_.y;
			}

			/*
			* @brief	Z回転の取得
			* @return	Z回転値
			*/
			float GetRotateZ() const noexcept
			{
				return rotate_.z;
			}

	
	};
	//ポインタ置き換え
	using TransformPtr = std::shared_ptr<CTransform>;
}
