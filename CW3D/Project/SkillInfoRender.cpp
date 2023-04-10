#include "SkillInfoRender.h"
#include "InputDefine.h"


using namespace ActionGame;


CSkillInfoRender::CSkillInfoRender()
	: position_(0, 0)
{
}

CSkillInfoRender::~CSkillInfoRender()
{
	Release();
}



bool CSkillInfoRender::Load()
{

	frame_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "SkillUI");
	font_ = ResourcePtrManager<CFont>::GetInstance().GetResource("Font", "SkillFont");
	position_ = Vector2(582, 884);

	FrameSetting();

	return true;

}

void CSkillInfoRender::Render()
{
	frame_->Render(position_.x, position_.y);
}

void CSkillInfoRender::RenderDebug2D()
{

}

void CSkillInfoRender::Release()
{
	frame_.reset();
	font_.reset();
}

void CSkillInfoRender::RenderKeyName()
{
	for (int i = 0; i < SKILLMAX_COUNT; i++)
	{
		font_->RenderString(skillFrame_[i].position.x - skillFrame_[i].rect.GetWidth() * 0.5f, skillFrame_[i].position.y - skillFrame_[i].rect.GetHeight() * 0.5f, skillFrame_[i].str);
	}
}



void CSkillInfoRender::FrameSetting()
{
	for (int i = 0; i < SKILLMAX_COUNT; i++)
	{
		skillFrame_[i].size = 50;
	}

	int cnt = 0;

	//座標と当たり判定用矩形設定
	//左側
	for (int x = 0; x < SKILL_LEFTLINE_COUNT; x++)
	{
		for (int y = 0; y < SKILL_COLUMN_COUNT; y++)
		{
			skillFrame_[cnt].position = Vector2(736, y * 61 + 939);

			cnt++;
		}
	}
	//真ん中
	for (int x = 0; x < SKILL_CENTERLINE_COUNT; x++)
	{
		for (int y = 0; y < SKILL_COLUMN_COUNT; y++)
		{
			skillFrame_[cnt].position = Vector2(x * 63 + 852, y * 61 + 939);
			cnt++;
		}
	}
	//右側
	for (int x = 0; x < SKILL_RIGHTLINE_COUNT; x++)
	{
		for (int y = 0; y < SKILL_COLUMN_COUNT; y++)
		{
			skillFrame_[cnt].position = Vector2(x * 70 + 1282, y * 61 + 939);
			cnt++;
		}
	}

	//当たり判定用矩形設定
	for (int i = 0; i < SKILLMAX_COUNT; i++)
	{
		Vector2 leftTop(skillFrame_[i].position.x - skillFrame_[i].size * 0.5f, skillFrame_[i].position.y - skillFrame_[i].size * 0.5f);
		Vector2 rightButtom(skillFrame_[i].position.x + skillFrame_[i].size * 0.5f, skillFrame_[i].position.y + skillFrame_[i].size * 0.5f);
		skillFrame_[i].rect = CRectangle(leftTop, rightButtom);
	}

	SetName();



}

void CSkillInfoRender::SetName()
{

	//キーボード名設定
	int cnt = 0;

	skillFrame_[cnt].str = "SHIFT";	//0
	
	cnt++;
	skillFrame_[cnt].str = "SPACE";	//1

	cnt++;
	skillFrame_[cnt].str = "Q";		//2

	cnt++;
	skillFrame_[cnt].str = "A";		//3

	cnt++;
	skillFrame_[cnt].str = "W";		//4

	cnt++;
	skillFrame_[cnt].str = "S";		//5

	cnt++;
	skillFrame_[cnt].str = "E";		//6

	cnt++;
	skillFrame_[cnt].str = "D";		//7

	cnt++;
	skillFrame_[cnt].str = "R";		//8

	cnt++;
	skillFrame_[cnt].str = "F";		//9

	cnt++;
	skillFrame_[cnt].str = "T";		//10

	cnt++;
	skillFrame_[cnt].str = "C";		//11

	cnt++;
	skillFrame_[cnt].str = "G";		//12

	cnt++;
	skillFrame_[cnt].str = "V";		//13

	cnt++;
	skillFrame_[cnt].str = "１";		//14

	cnt++;
	skillFrame_[cnt].str = "３";		//15

	cnt++;
	skillFrame_[cnt].str = "２";		//16

	cnt++;
	skillFrame_[cnt].str = "４";		//17

	//キーの座標設定
	keyIndexs[INPUT_KEY_SKILL1] = 7;
	keyIndexs[INPUT_KEY_SKILL2] = 3;
	keyIndexs[INPUT_KEY_SKILL3] = 5;
	keyIndexs[INPUT_KEY_ESCAPE] = 1;
	keyIndexs[INPUT_KEY_SKILL4] = 9;
}
