#pragma once

#include "Common.h"

namespace ActionGame
{
	class CCreateWindow
	{
	#define TEXTURE_SLICE 9	//テクスチャの分割数
	private:
		CVector4 m_Color;
		Vector2	m_Scale;
		Vector2 m_Position[TEXTURE_SLICE];
		CTexture* m_Texture[TEXTURE_SLICE];
		CRectangle m_TextureRect[TEXTURE_SLICE];
		Vector2 m_TexSize;
		CRectangle m_WindowRect;

	public:
		CCreateWindow();
		~CCreateWindow();
		void Load(CTexture* tex);
		void Create(const Vector2& pos, const Vector2& scale);
		void Render();
		void Release();
		void SetColor(MofU32 color);
		float GetWidth();
		float GetHeight();
		const Vector2& GetPos() { return m_Position[0]; }
		void SetPos(const Vector2& pos);
		void SetScale(const Vector2& scale) { m_Scale = scale; }
		CRectangle GetRect() { return m_WindowRect; }

	};
}



