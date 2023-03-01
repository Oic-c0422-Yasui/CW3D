#include "SkillControllerRender.h"
#include "InputDefine.h"


using namespace ActionGame;


CSkillControllerRender::CSkillControllerRender()
	: position_(0, 0)
{
}

CSkillControllerRender::~CSkillControllerRender()
{
	Release();
}



bool CSkillControllerRender::Load()
{

	frame_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "SkillUI");
	font_ = ResourcePtrManager<CFont>::GetInstance().GetResource("Font", "SkillFont");
	position_ = Vector2(582, 884);

	FrameSetting();

	return true;

}

void CSkillControllerRender::Render()
{
	frame_->Render(position_.x, position_.y);
}

void CSkillControllerRender::RenderDebug2D()
{

}

void CSkillControllerRender::Release()
{
	frame_.reset();
	font_.reset();
}

void CSkillControllerRender::RenderKeyName()
{
	for (int i = 0; i < SKILLMAX_COUNT; i++)
	{
		font_->RenderString(skillFrame_[i].position.x - skillFrame_[i].rect.GetWidth() * 0.5f, skillFrame_[i].position.y - skillFrame_[i].rect.GetHeight() * 0.5f, skillFrame_[i].str);
	}
}



void CSkillControllerRender::FrameSetting()
{
	for (int i = 0; i < SKILLMAX_COUNT; i++)
	{
		skillFrame_[i].size = 50;
	}

	int cnt = 0;

	//À•W‚Æ“–‚½‚è”»’è—p‹éŒ`Ý’è
	//¶‘¤
	for (int x = 0; x < SKILL_LEFTLINE_COUNT; x++)
	{
		for (int y = 0; y < SKILL_COLUMN_COUNT; y++)
		{
			skillFrame_[cnt].position = Vector2(736, y * 61 + 939);

			cnt++;
		}
	}
	//^‚ñ’†
	for (int x = 0; x < SKILL_CENTERLINE_COUNT; x++)
	{
		for (int y = 0; y < SKILL_COLUMN_COUNT; y++)
		{
			skillFrame_[cnt].position = Vector2(x * 63 + 852, y * 61 + 939);
			cnt++;
		}
	}
	//‰E‘¤
	for (int x = 0; x < SKILL_RIGHTLINE_COUNT; x++)
	{
		for (int y = 0; y < SKILL_COLUMN_COUNT; y++)
		{
			skillFrame_[cnt].position = Vector2(x * 70 + 1282, y * 61 + 939);
			cnt++;
		}
	}

	//“–‚½‚è”»’è—p‹éŒ`Ý’è
	for (int i = 0; i < SKILLMAX_COUNT; i++)
	{
		Vector2 leftTop(skillFrame_[i].position.x - skillFrame_[i].size * 0.5f, skillFrame_[i].position.y - skillFrame_[i].size * 0.5f);
		Vector2 rightButtom(skillFrame_[i].position.x + skillFrame_[i].size * 0.5f, skillFrame_[i].position.y + skillFrame_[i].size * 0.5f);
		skillFrame_[i].rect = CRectangle(leftTop, rightButtom);
	}

	SetName();



}

void CSkillControllerRender::SetName()
{

	//ƒL[ƒ{[ƒh–¼Ý’è
	int cnt = 0;

	skillFrame_[cnt].str = "SHIFT";	//0
	
	cnt++;
	skillFrame_[cnt].str = "SPACE";	//1

	cnt++;
	skillFrame_[cnt].str = "‚p";		//2

	cnt++;
	skillFrame_[cnt].str = "‚`";		//3

	cnt++;
	skillFrame_[cnt].str = "‚v";		//4

	cnt++;
	skillFrame_[cnt].str = "‚r";		//5

	cnt++;
	skillFrame_[cnt].str = "‚d";		//6

	cnt++;
	skillFrame_[cnt].str = "‚c";		//7

	cnt++;
	skillFrame_[cnt].str = "‚q";		//8

	cnt++;
	skillFrame_[cnt].str = "‚e";		//9

	cnt++;
	skillFrame_[cnt].str = "‚s";		//10

	cnt++;
	skillFrame_[cnt].str = "‚b";		//11

	cnt++;
	skillFrame_[cnt].str = "‚f";		//12

	cnt++;
	skillFrame_[cnt].str = "‚u";		//13

	cnt++;
	skillFrame_[cnt].str = "‚P";		//14

	cnt++;
	skillFrame_[cnt].str = "‚R";		//15

	cnt++;
	skillFrame_[cnt].str = "‚Q";		//16

	cnt++;
	skillFrame_[cnt].str = "‚S";		//17

	//ƒL[‚ÌÀ•WÝ’è
	keyIndexs[INPUT_KEY_SKILL1] = 7;
	keyIndexs[INPUT_KEY_SKILL2] = 3;
	keyIndexs[INPUT_KEY_SKILL3] = 5;
	keyIndexs[INPUT_KEY_ESCAPE] = 1;
	keyIndexs[INPUT_KEY_SKILL4] = 9;
}
