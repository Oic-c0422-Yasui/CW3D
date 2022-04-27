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
		
		Transform():
			m_Position(0,0,0),
			m_Scale(1,1,1),
			m_Rotate(0,0,0),
			m_World()
		{
		}

		void Move()
		{
			////intにconst => 定数へのポインタ
			//const int* a = nullptr;
			//int const* b = nullptr;

			////int*にconst => ポインタが定数
			//int* const c = nullptr;

			////両方const
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
