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
		
		Transform():
			m_Position(0,0,0),
			m_Scale(1,1,1),
			m_Rotate(0,0,0),
			m_World()
		{
		}

		void Move()
		{
			////int��const => �萔�ւ̃|�C���^
			//const int* a = nullptr;
			//int const* b = nullptr;

			////int*��const => �|�C���^���萔
			//int* const c = nullptr;

			////����const
			//const int* const d = nullptr;
		}

		const CMatrix44& GetWorld() {
			if (m_UpdateFlg)
			{
				UpdateMatrix();
				m_UpdateFlg = false;
			}
			return m_World;
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

}
