#pragma once

#include	"Common.h"
#include	"Utilities.h"
#include	"Velocity.h"


namespace ActionGame
{
	/*
	* @brief	�p���ϊ��N���X
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
		/* �v���C�x�[�g�֐��@*/

		//�}�g���N�X���X�V
		void UpdateMatrix();

	public:
		
		CTransform();

		//�}�g���N�X���擾
		/*
		* @brief	�}�g���N�X���擾
		* @return	�}�g���N�X
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
		* @brief	���]�ݒ�
		* @param	isReverse ���]��
		*/
		void SetReverse(bool isReverse) noexcept
		{
			isReverse_ = isReverse;
		}

		/*
		* @brief	���]���Ă��邩�H
		* @return	true�@�Ȃ甽�]
		*/
		bool IsReverse() const noexcept
		{
			return isReverse_;
		}
		/*
		* @brief	���]���Ă��邩�H
		* @return	true�@�Ȃ甽�]
		*/
		void SetType(CHARA_TYPE type) noexcept
		{
			type_ = type;
		}

		////////////////////////////////////////////////////////////////
		///			���W�n
		////////////////////////////////////////////////////////////////

			/*
			 * @brief		���W�ړ�
			 * @param		position �ړ����W
			 */
			void AddPosition(const Vector3& position) noexcept;

			/*
			 * @brief		���W�ړ�
			 * @param		velocity ���x�N���X
			 */
			void AddPosition(const VelocityPtr& velocity) noexcept;
			

			/*
			* @brief	���W����
			* @param	min	�ŏ����W
			* @param	max	�ő���W
			*/
			void Clip(const Vector3& min, const  Vector3& max);

			/*
			* @brief	X���W����
			* @param	min	�ŏ����W
			* @param	max	�ő���W
			*/
			void ClipX(float min, float max);
			

			/*
			* @brief	Y���W����
			* @param	min	�ŏ����W
			* @param	max	�ő���W
			*/
			void ClipY(float min, float max);

			/*
			* @brief	X���W����
			* @param	min	�ŏ����W
			* @param	max	�ő���W
			*/
			void ClipZ(float min, float max);


			/*
			* @brief	���W�ݒ�
			* @param	position	���W
			*/
			void SetPosition(const Vector3& position) noexcept;


			/*
			* @brief	X���W�ݒ�
			* @param	position	X���W
			*/
			void SetPositionX(float position) noexcept
			{
				position_.x = position;
				world_.SetTranslation(position_);
			}

			/*
			* @brief	Y���W�ݒ�
			* @param	position	Y���W
			*/
			void SetPositionY(float position) noexcept
			{
				position_.y = position;
				world_.SetTranslation(position_);
			}

			/*
			* @brief	Z���W�ݒ�
			* @param	position	Z���W
			*/
			void SetPositionZ(float position) noexcept
			{
				position_.z = position;
				world_.SetTranslation(position_);
			}

			/*
			* @brief	���W�擾
			* @return	���W
			*/
			const CVector3& GetPosition() const noexcept
			{
				return position_;
			}

			/*
			* @brief	X���W�擾
			* @return	X���W
			*/
			float GetPositionX() const noexcept
			{
				return position_.x;
			}

			/*
			* @brief	Y���W�擾
			* @return	Y���W
			*/
			float GetPositionY() const noexcept
			{
				return position_.y;
			}

			/*
			* @brief	Z���W�擾
			* @return	Z���W
			*/
			float GetPositionZ() const noexcept
			{
				return position_.z;
			}

		////////////////////////////////////////////////////////////////
		///			�傫���n
		////////////////////////////////////////////////////////////////

			/*
			* @brief	�傫���̕ύX
			* @param	changeScale �傫��
			*/
			void AddScale(const Vector3& changeScale) noexcept
			{
				scale_ += changeScale;
				isUpdate_ = true;
			}

			/*
			* @brief	�傫���̐ݒ�
			* @param	scale �傫��
			*/
			void SetScale(const Vector3& scale) noexcept
			{
				scale_ = scale;
				isUpdate_ = true;
			}

			/*
			* @brief	X�̑傫���ݒ�
			* @param	scale X�̑傫��
			*/
			void SetScaleX(float scale) noexcept
			{
				scale_.x = scale;
				isUpdate_ = true;
			}

			/*
			* @brief	X�̑傫���ݒ�
			* @param	scale Y�̑傫��
			*/
			void SetScaleY(float scale) noexcept
			{
				scale_.y = scale;
				isUpdate_ = true;
			}

			/*
			* @brief	X�̑傫���ݒ�
			* @param	scale Z�̑傫��
			*/
			void SetScaleZ(float scale) noexcept
			{
				scale_.z = scale;
				isUpdate_ = true;
			}

			/*
			* @brief	�傫���擾
			* @return	�傫��
			*/
			const CVector3& GetScale() const noexcept
			{
				return scale_;
			}

			/*
			* @brief	X�̑傫���擾
			* @return	X�̑傫��
			*/
			float GetScaleX() const noexcept
			{
				return scale_.x;
			}

			/*
			* @brief	Y�̑傫���擾
			* @return	Y�̑傫��
			*/
			float GetScaleY() const noexcept
			{
				return scale_.y;
			}

			/*
			* @brief	Z�̑傫���擾
			* @return	Z�̑傫��
			*/
			float GetScaleZ() const noexcept
			{
				return scale_.z;
			}

		////////////////////////////////////////////////////////////////
		///			��]�n
		////////////////////////////////////////////////////////////////

			/*
			* @brief	�ǉ���]
			* @param	rotate	��]�l
			*/
			void AddRotate(const Vector3& rotate) noexcept
			{
				rotate_ += rotate;
				isUpdate_ = true;
			}

			/*
			* @brief	��]�̐ݒ�
			* @param	rotate	��]�l
			*/
			void SetRotate(const Vector3& rotate) noexcept
			{
				rotate_ = rotate;
				isUpdate_ = true;
			}

			/*
			* @brief	X��]�̐ݒ�
			* @param	rotate	X��]�l
			*/
			void SetRotateX(float rotate) noexcept
			{
				rotate_.x = rotate;
				isUpdate_ = true;
			}

			/*
			* @brief	Y��]�̐ݒ�
			* @param	rotate	Y��]�l
			*/
			void SetRotateY(float rotate) noexcept
			{
				rotate_.y = rotate;
				isUpdate_ = true;
			}

			/*
			* @brief	Z��]�̐ݒ�
			* @param	rotate	Z��]�l
			*/
			void SetRotateZ(float rotate) noexcept
			{
				rotate_.z = rotate;
				isUpdate_ = true;
			}

			/*
			* @brief	��]�̎擾
			* @return	��]�l
			*/
			const CVector3& GetRotate() const noexcept
			{
				return rotate_;
			}

			/*
			* @brief	X��]�̎擾
			* @return	X��]�l
			*/
			float GetRotateX() const noexcept
			{
				return rotate_.x;
			}

			/*
			* @brief	Y��]�̎擾
			* @return	Y��]�l
			*/
			float GetRotateY() const noexcept
			{
				return rotate_.y;
			}

			/*
			* @brief	Z��]�̎擾
			* @return	Z��]�l
			*/
			float GetRotateZ() const noexcept
			{
				return rotate_.z;
			}

	
	};
	//�|�C���^�u������
	using TransformPtr = std::shared_ptr<CTransform>;
}
