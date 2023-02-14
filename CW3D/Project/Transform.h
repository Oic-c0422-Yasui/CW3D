#pragma once

#include	"Common.h"
#include	"Utilities.h"
#include	"Velocity.h"


namespace ActionGame
{
	/*
	* @brief	�p���ϊ��N���X
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
		/* �v���C�x�[�g�֐��@*/

		//�}�g���N�X���X�V
		void UpdateMatrix();

	public:
		
		Transform();

		//�}�g���N�X���擾
		/*
		* @brief	�}�g���N�X���擾
		* @return	�}�g���N�X
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
		* @brief	���]�ݒ�
		* @param	isReverse ���]��
		*/
		void SetReverse(bool isReverse) noexcept
		{
			m_ReverseFlg = isReverse;
		}

		/*
		* @brief	���]���Ă��邩�H
		* @return	true�@�Ȃ甽�]
		*/
		bool IsReverse() const noexcept
		{
			return m_ReverseFlg;
		}
		/*
		* @brief	���]���Ă��邩�H
		* @return	true�@�Ȃ甽�]
		*/
		void SetType(CHARA_TYPE type) noexcept
		{
			m_Type = type;
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
				m_Position.x = position;
				m_World.SetTranslation(m_Position);
			}

			/*
			* @brief	Y���W�ݒ�
			* @param	position	Y���W
			*/
			void SetPositionY(float position) noexcept
			{
				m_Position.y = position;
				m_World.SetTranslation(m_Position);
			}

			/*
			* @brief	Z���W�ݒ�
			* @param	position	Z���W
			*/
			void SetPositionZ(float position) noexcept
			{
				m_Position.z = position;
				m_World.SetTranslation(m_Position);
			}

			/*
			* @brief	���W�擾
			* @return	���W
			*/
			const CVector3& GetPosition() const noexcept
			{
				return m_Position;
			}

			/*
			* @brief	X���W�擾
			* @return	X���W
			*/
			float GetPositionX() const noexcept
			{
				return m_Position.x;
			}

			/*
			* @brief	Y���W�擾
			* @return	Y���W
			*/
			float GetPositionY() const noexcept
			{
				return m_Position.y;
			}

			/*
			* @brief	Z���W�擾
			* @return	Z���W
			*/
			float GetPositionZ() const noexcept
			{
				return m_Position.z;
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
				m_Scale += changeScale;
				m_UpdateFlg = true;
			}

			/*
			* @brief	�傫���̐ݒ�
			* @param	scale �傫��
			*/
			void SetScale(const Vector3& scale) noexcept
			{
				m_Scale = scale;
				m_UpdateFlg = true;
			}

			/*
			* @brief	X�̑傫���ݒ�
			* @param	scale X�̑傫��
			*/
			void SetScaleX(float scale) noexcept
			{
				m_Scale.x = scale;
				m_UpdateFlg = true;
			}

			/*
			* @brief	X�̑傫���ݒ�
			* @param	scale Y�̑傫��
			*/
			void SetScaleY(float scale) noexcept
			{
				m_Scale.y = scale;
				m_UpdateFlg = true;
			}

			/*
			* @brief	X�̑傫���ݒ�
			* @param	scale Z�̑傫��
			*/
			void SetScaleZ(float scale) noexcept
			{
				m_Scale.z = scale;
				m_UpdateFlg = true;
			}

			/*
			* @brief	�傫���擾
			* @return	�傫��
			*/
			const CVector3& GetScale() const noexcept
			{
				return m_Scale;
			}

			/*
			* @brief	X�̑傫���擾
			* @return	X�̑傫��
			*/
			float GetScaleX() const noexcept
			{
				return m_Scale.x;
			}

			/*
			* @brief	Y�̑傫���擾
			* @return	Y�̑傫��
			*/
			float GetScaleY() const noexcept
			{
				return m_Scale.y;
			}

			/*
			* @brief	Z�̑傫���擾
			* @return	Z�̑傫��
			*/
			float GetScaleZ() const noexcept
			{
				return m_Scale.z;
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
				m_Rotate += rotate;
				m_UpdateFlg = true;
			}

			/*
			* @brief	��]�̐ݒ�
			* @param	rotate	��]�l
			*/
			void SetRotate(const Vector3& rotate) noexcept
			{
				m_Rotate = rotate;
				m_UpdateFlg = true;
			}

			/*
			* @brief	X��]�̐ݒ�
			* @param	rotate	X��]�l
			*/
			void SetRotateX(float rotate) noexcept
			{
				m_Rotate.x = rotate;
				m_UpdateFlg = true;
			}

			/*
			* @brief	Y��]�̐ݒ�
			* @param	rotate	Y��]�l
			*/
			void SetRotateY(float rotate) noexcept
			{
				m_Rotate.y = rotate;
				m_UpdateFlg = true;
			}

			/*
			* @brief	Z��]�̐ݒ�
			* @param	rotate	Z��]�l
			*/
			void SetRotateZ(float rotate) noexcept
			{
				m_Rotate.z = rotate;
				m_UpdateFlg = true;
			}

			/*
			* @brief	��]�̎擾
			* @return	��]�l
			*/
			const CVector3& GetRotate() const noexcept
			{
				return m_Rotate;
			}

			/*
			* @brief	X��]�̎擾
			* @return	X��]�l
			*/
			float GetRotateX() const noexcept
			{
				return m_Rotate.x;
			}

			/*
			* @brief	Y��]�̎擾
			* @return	Y��]�l
			*/
			float GetRotateY() const noexcept
			{
				return m_Rotate.y;
			}

			/*
			* @brief	Z��]�̎擾
			* @return	Z��]�l
			*/
			float GetRotateZ() const noexcept
			{
				return m_Rotate.z;
			}

	
	};
	//�|�C���^�u������
	using TransformPtr = std::shared_ptr<Transform>;
}
