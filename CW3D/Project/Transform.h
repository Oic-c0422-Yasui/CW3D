#pragma once

#include	"Common.h"

namespace Sample
{
	//�p���ϊ��N���X
	class  Transform
	{
	
	protected:
		//���W
		CVector3	m_Position;
		//�傫��
		CVector3	m_Scale;
		//��]
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

		//�}�g���N�X���擾
		const CMatrix44& GetWorld() {
			if (m_UpdateFlg)
			{
				UpdateMatrix();
				m_UpdateFlg = false;
			}
			return m_World;
		}


		/**
		 * @brief		���W�n
		 */

			//���W�̈ړ�
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

			//���W�̐ݒ�
			void SetPosition(CVector3 position) noexcept
			{
				m_Position = position;
				m_World.SetTranslation(m_Position);
			}

			//���W�̐ݒ�
			void SetPositionX(float position) noexcept
			{
				m_Position.x = position;
				m_World.SetTranslation(m_Position);
			}

			//���W�̐ݒ�
			void SetPositionY(float position) noexcept
			{
				m_Position.y = position;
				m_World.SetTranslation(m_Position);
			}

			//���W�̐ݒ�
			void SetPositionZ(float position) noexcept
			{
				m_Position.z = position;
				m_World.SetTranslation(m_Position);
			}

			//���W�̎擾
			CVector3 GetPosition() const noexcept
			{
				return m_Position;
			}

			//���W�̎擾
			float GetPositionX() const noexcept
			{
				return m_Position.x;
			}

			//���W�̎擾
			float GetPositionY() const noexcept
			{
				return m_Position.y;
			}

			//���W�̎擾
			float GetPositionZ() const noexcept
			{
				return m_Position.z;
			}

		/**
		 * @brief		�T�C�Y�n
		 */

			 //�T�C�Y�̕ύX
			void MoveScale(CVector3 changeScale) noexcept
			{
				m_Scale += changeScale;
				m_UpdateFlg = true;
			}

			//�T�C�Y�̐ݒ�
			void SetScale(CVector3 scale) noexcept
			{
				m_Scale = scale;
				m_UpdateFlg = true;
			}

			//�T�C�Y�̐ݒ�
			void SetScaleX(float scale) noexcept
			{
				m_Scale.x = scale;
				m_UpdateFlg = true;
			}

			//�T�C�Y�̐ݒ�
			void SetScaleY(float scale) noexcept
			{
				m_Scale.y = scale;
				m_UpdateFlg = true;
			}

			//�T�C�Y�̐ݒ�
			void SetScaleZ(float scale) noexcept
			{
				m_Scale.z = scale;
				m_UpdateFlg = true;
			}

			//�T�C�Y�̎擾
			CVector3 GetScale() const noexcept
			{
				return m_Scale;
			}

			//�T�C�Y�̎擾
			float GetScaleX() const noexcept
			{
				return m_Scale.x;
			}

			//�T�C�Y�̎擾
			float GetScaleY() const noexcept
			{
				return m_Scale.y;
			}

			//�T�C�Y�̎擾
			float GetScaleZ() const noexcept
			{
				return m_Scale.z;
			}

		/**
		 * @brief		��]�n
		 */

			//��]
			void MoveRotate(CVector3 rotate) noexcept
			{
				m_Rotate += rotate;
				m_UpdateFlg = true;
			}

			//��]�̐ݒ�
			void SetRotate(CVector3 rotate) noexcept
			{
				m_Rotate = rotate;
				m_UpdateFlg = true;
			}

			//��]�̐ݒ�
			void SetRotateX(float rotate) noexcept
			{
				m_Rotate.x = rotate;
				m_UpdateFlg = true;
			}

			//��]�̐ݒ�
			void SetRotateY(float rotate) noexcept
			{
				m_Rotate.y = rotate;
				m_UpdateFlg = true;
			}

			//��]�̐ݒ�
			void SetRotateZ(float rotate) noexcept
			{
				m_Rotate.z = rotate;
				m_UpdateFlg = true;
			}

			//��]�̎擾
			CVector3 GetRotate() const noexcept
			{
				return m_Scale;
			}

			//��]�̎擾
			float GetRotateX() const noexcept
			{
				return m_Scale.x;
			}

			//��]�̎擾
			float GetRotateY() const noexcept
			{
				return m_Scale.y;
			}

			//��]�̎擾
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
	//�|�C���^�u������
	using TransformPtr = std::shared_ptr<Transform>;
}
