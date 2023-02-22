#include "CreateWindow.h"

using namespace ActionGame;

CCreateWindow::CCreateWindow():
	m_Color(),
	position_(),
	scale_(),
	m_Texture(),
	m_TexSize(),
	m_TextureRect()
{
}

CCreateWindow::~CCreateWindow()
{
	Release();
}

void CCreateWindow::Load(CTexture* tex)
{
	for (int i = 0; i < TEXTURE_SLICE; i++)
	{
		m_Texture[i] = tex;
	}
}

void CCreateWindow::Create(const Vector2& pos, const Vector2& scale)
{
	scale_ = scale;
	m_Color.SetU32Color(MOF_ARGB(255,255,255,255));
	//１ブロックのサイズを調べる
	m_TexSize = Vector2(m_Texture[0]->GetWidth() / 3, m_Texture[0]->GetHeight() / 3);
	//位置セット
	SetPos(pos);

	int i = 0;
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			m_TextureRect[i] = CRectangle(m_TexSize.x * x, m_TexSize.y * y, m_TexSize.x * x + m_TexSize.x, m_TexSize.y * y + m_TexSize.y);
			i++;
		}
	}
	m_WindowRect = CRectangle(position_[0].x, position_[0].y, position_[0].x + GetWidth(), position_[0].y + GetHeight());

}

void CCreateWindow::Render()
{
	//１段目
	m_Texture[0]->Render(position_[0].x, position_[0].y, m_TextureRect[0], m_Color.ToU32Color());
	m_Texture[1]->RenderScale(position_[1].x, position_[1].y,scale_.x,1, m_TextureRect[1], m_Color.ToU32Color());
	m_Texture[2]->Render(position_[2].x, position_[2].y, m_TextureRect[2], m_Color.ToU32Color());

	//２段目
	m_Texture[3]->RenderScale(position_[3].x , position_[3].y,1 , scale_.y, m_TextureRect[3], m_Color.ToU32Color());
	m_Texture[4]->RenderScale(position_[4].x, position_[4].y, scale_.x, scale_.y, m_TextureRect[4], m_Color.ToU32Color());
	m_Texture[5]->RenderScale(position_[5].x, position_[5].y, 1, scale_.y, m_TextureRect[5], m_Color.ToU32Color());

	//３段目
	m_Texture[6]->Render(position_[6].x, position_[6].y, m_TextureRect[6], m_Color.ToU32Color());
	m_Texture[7]->RenderScale(position_[7].x, position_[7].y, scale_.x, 1, m_TextureRect[7], m_Color.ToU32Color());
	m_Texture[8]->Render(position_[8].x, position_[8].y, m_TextureRect[8], m_Color.ToU32Color());

}

void CCreateWindow::Release()
{
	for (int i = 0; i < TEXTURE_SLICE; i++)
	{
		m_Texture[i]->Release();
	}
}

void CCreateWindow::SetColor(MofU32 color)
{
	m_Color.SetU32Color(color);
}

float CCreateWindow::GetWidth()
{
	float width = 0.0f;

	width = position_[2].x + m_TextureRect[0].GetWidth() - position_[0].x;

	return width;
}

float CCreateWindow::GetHeight()
{
	float height = 0.0f;

	height = position_[6].y + m_TextureRect[0].GetHeight() - position_[0].y;

	return height;
}

void CCreateWindow::SetPos(const Vector2& pos)
{
	Vector2 addPos(0, 0);
	int i = 0;
	for (int y = 0; y < 3; y++)
	{
		switch (y)
		{
		case 0:
		{
			addPos.y = 0;
			break;
		}
		case 1:
		{
			addPos.y = m_TexSize.y;
			break;
		}
		case 2:
		{
			addPos.y = m_TexSize.y + (m_TexSize.y * scale_.y);
			break;
		}
		default:
			break;
		}
		for (int x = 0; x < 3; x++)
		{
			switch (x)
			{
			case 0:
			{
				addPos.x = 0;
				break;
			}
			case 1:
			{
				addPos.x = m_TexSize.x;
				break;
			}
			case 2:
			{
				addPos.x = m_TexSize.x + (m_TexSize.x * scale_.x);
				break;
			}
			default:
				break;
			}
			position_[i] = Vector2(pos.x + addPos.x, pos.y + addPos.y);
			i++;
		}
	}
}


