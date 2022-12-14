#include "SkillControllerRender.h"
#include "InputDefine.h"


using namespace ActionGame;


CSkillControllerRender::CSkillControllerRender()
	: m_Position(0, 0)
{
}

CSkillControllerRender::~CSkillControllerRender()
{
}



bool CSkillControllerRender::Load()
{

	m_pFrame = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "SkillUI");
	m_pFont = ResourcePtrManager<CFont>::GetInstance().GetResource("Font", "SkillFont");
	m_Position = Vector2(582, 884);

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

	m_SkillFrame[cnt].str = "SHIFT";	//0
	
	cnt++;
	m_SkillFrame[cnt].str = "SPACE";	//1

	cnt++;
	m_SkillFrame[cnt].str = "‚p";		//2

	cnt++;
	m_SkillFrame[cnt].str = "‚`";		//3

	cnt++;
	m_SkillFrame[cnt].str = "‚v";		//4

	cnt++;
	m_SkillFrame[cnt].str = "‚r";		//5

	cnt++;
	m_SkillFrame[cnt].str = "‚d";		//6

	cnt++;
	m_SkillFrame[cnt].str = "‚c";		//7

	cnt++;
	m_SkillFrame[cnt].str = "‚q";		//8

	cnt++;
	m_SkillFrame[cnt].str = "‚e";		//9

	cnt++;
	m_SkillFrame[cnt].str = "‚s";		//10

	cnt++;
	m_SkillFrame[cnt].str = "‚b";		//11

	cnt++;
	m_SkillFrame[cnt].str = "‚f";		//12

	cnt++;
	m_SkillFrame[cnt].str = "‚u";		//13

	cnt++;
	m_SkillFrame[cnt].str = "‚P";		//14

	cnt++;
	m_SkillFrame[cnt].str = "‚R";		//15

	cnt++;
	m_SkillFrame[cnt].str = "‚Q";		//16

	cnt++;
	m_SkillFrame[cnt].str = "‚S";		//17

	//ƒL[‚ÌÀ•WÝ’è
	keyIndexs[INPUT_KEY_SKILL1] = 7;
	keyIndexs[INPUT_KEY_SKILL2] = 3;
	keyIndexs[INPUT_KEY_SKILL3] = 5;
	keyIndexs[INPUT_KEY_ESCAPE] = 1;
	keyIndexs[INPUT_KEY_SKILL4] = 9;
}
