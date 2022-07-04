#include "SkillControllerUIRender.h"

using namespace Sample;


Sample::SkillControllerUIRender::SkillControllerUIRender()
	: m_Position(0, 0)
{
}

Sample::SkillControllerUIRender::~SkillControllerUIRender()
{
}



bool Sample::SkillControllerUIRender::Load()
{

	m_pFrame = Sample::ResourceManager<CTexture>::GetInstance().GetResource("SkillUI");
	m_pFont = Sample::ResourceManager<CFont>::GetInstance().GetResource("SkillFont");
	m_Position = Vector2(582, 884);


	FrameSetting();

	return true;

}

void Sample::SkillControllerUIRender::Render()
{
	m_pFrame->Render(m_Position.x, m_Position.y);
}

void Sample::SkillControllerUIRender::RenderDebug2D()
{

}

void Sample::SkillControllerUIRender::Release(void)
{
	m_pFrame.reset();
	m_pSkill.reset();
	m_pFont.reset();
}

void Sample::SkillControllerUIRender::RenderKeyName()
{
	for (int i = 0; i < SKILLMAX_COUNT; i++)
	{
		m_pFont->RenderString(m_SkillFrame[i].position.x - m_SkillFrame[i].rect.GetWidth() * 0.5f, m_SkillFrame[i].position.y - m_SkillFrame[i].rect.GetHeight() * 0.5f, m_SkillFrame[i].str);
	}
}



void Sample::SkillControllerUIRender::FrameSetting()
{
	for (int i = 0; i < SKILLMAX_COUNT; i++)
	{
		m_SkillFrame[i].size = 50;
	}

	int cnt = 0;

	//À•W‚Æ“–‚½‚è”»’è—p‹éŒ`Ý’è
	//¶‘¤
	for (int x = 0; x < SKILL_LEFTLINE_COUNT; x++)
	{
		for (int y = 0; y < SKILL_COLUMN_COUNT; y++)
		{
			m_SkillFrame[cnt].position = Vector2(736, y * 61 + 939);

			cnt++;
		}
	}
	//^‚ñ’†
	for (int x = 0; x < SKILL_CENTERLINE_COUNT; x++)
	{
		for (int y = 0; y < SKILL_COLUMN_COUNT; y++)
		{
			m_SkillFrame[cnt].position = Vector2(x * 63 + 852, y * 61 + 939);
			cnt++;
		}
	}
	//‰E‘¤
	for (int x = 0; x < SKILL_RIGHTLINE_COUNT; x++)
	{
		for (int y = 0; y < SKILL_COLUMN_COUNT; y++)
		{
			m_SkillFrame[cnt].position = Vector2(x * 70 + 1282, y * 61 + 939);
			cnt++;
		}
	}

	//“–‚½‚è”»’è—p‹éŒ`Ý’è
	for (int i = 0; i < SKILLMAX_COUNT; i++)
	{
		Vector2 leftTop(m_SkillFrame[i].position.x - m_SkillFrame[i].size * 0.5f, m_SkillFrame[i].position.y - m_SkillFrame[i].size * 0.5f);
		Vector2 rightButtom(m_SkillFrame[i].position.x + m_SkillFrame[i].size * 0.5f, m_SkillFrame[i].position.y + m_SkillFrame[i].size * 0.5f);
		m_SkillFrame[i].rect = CRectangle(leftTop, rightButtom);
	}

	SetName();
}

void Sample::SkillControllerUIRender::SetName()
{

	//ƒL[ƒ{[ƒh–¼Ý’è
	int cnt = 0;

	m_SkillFrame[cnt].str = "SHIFT";
	
	cnt++;
	m_SkillFrame[cnt].str = "SPACE";

	cnt++;
	m_SkillFrame[cnt].str = "‚p";

	cnt++;
	m_SkillFrame[cnt].str = "‚`";

	cnt++;
	m_SkillFrame[cnt].str = "‚v";

	cnt++;
	m_SkillFrame[cnt].str = "‚r";

	cnt++;
	m_SkillFrame[cnt].str = "‚d";

	cnt++;
	m_SkillFrame[cnt].str = "‚c";

	cnt++;
	m_SkillFrame[cnt].str = "‚q";

	cnt++;
	m_SkillFrame[cnt].str = "‚e";

	cnt++;
	m_SkillFrame[cnt].str = "‚s";

	cnt++;
	m_SkillFrame[cnt].str = "‚b";

	cnt++;
	m_SkillFrame[cnt].str = "‚f";

	cnt++;
	m_SkillFrame[cnt].str = "‚u";

	cnt++;
	m_SkillFrame[cnt].str = "‚P";

	cnt++;
	m_SkillFrame[cnt].str = "‚R";

	cnt++;
	m_SkillFrame[cnt].str = "‚Q";

	cnt++;
	m_SkillFrame[cnt].str = "‚S";

}
