#include "SkillControllerRender.h"
#include "Player.h"

using namespace Sample;


CSkillControllerRender::CSkillControllerRender()
	: m_Position(0, 0)
{
}

CSkillControllerRender::~CSkillControllerRender()
{
}



bool CSkillControllerRender::Load()
{

	m_pFrame = ResourceManager<CTexture>::GetInstance().GetResource("SkillUI");
	m_pFont = ResourceManager<CFont>::GetInstance().GetResource("SkillFont");
	m_Position = Vector2(582, 884);
	auto& player = ServiceLocator< CPlayer >::GetService();

	FrameSetting();

	return true;

}

void CSkillControllerRender::Render()
{
	m_pFrame->Render(m_Position.x, m_Position.y);
}

void CSkillControllerRender::RenderDebug2D()
{

}

void CSkillControllerRender::Release(void)
{
	m_pFrame.reset();
	m_pSkill.reset();
	m_pFont.reset();
}

void CSkillControllerRender::RenderKeyName()
{
	for (int i = 0; i < SKILLMAX_COUNT; i++)
	{
		m_pFont->RenderString(m_SkillFrame[i].position.x - m_SkillFrame[i].rect.GetWidth() * 0.5f, m_SkillFrame[i].position.y - m_SkillFrame[i].rect.GetHeight() * 0.5f, m_SkillFrame[i].str);
	}
}



void CSkillControllerRender::FrameSetting()
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

void CSkillControllerRender::SetName()
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

	//ƒL[‚ÌÀ•W
	keyIndexs[INPUT_KEY_SKILL1] = 7;
	keyIndexs[INPUT_KEY_SKILL2] = 3;
	keyIndexs[INPUT_KEY_SKILL3] = 5;
	keyIndexs[INPUT_KEY_ESCAPE] = 1;
	keyIndexs[INPUT_KEY_SKILL_DROPKICK] = 9;
}
