#include "SkillInfoRender.h"
#include "InputDefine.h"
#include "ResourceManager.h"

using namespace ActionGame;


CSkillInfoRender::CSkillInfoRender()
	: position_(0, 0)
	, uiFrame_()
	, font_(nullptr)
	, padButtonFont_(nullptr)
	, skillFrame_()
	, keyIndexs_()
	, currentDevice_(Device_Keyboard)
{
}

CSkillInfoRender::~CSkillInfoRender()
{
	Release();
}



bool CSkillInfoRender::Load(GameDevice device)
{

	uiFrame_[Device_Keyboard] = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "SkillUI_PC");
	uiFrame_[Device_Controller] = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "SkillUI_Pad");
	font_ = ResourcePtrManager<CFont>::GetInstance().GetResource("Font", "SkillFont");
	padButtonFont_ = ResourcePtrManager<CFont>::GetInstance().GetResource("Font", "PadButtonFont");
	position_ = Vector2(366, 780);

	switch (device)
	{
	case GameDevice::KeyBoardAndMouse:
		currentDevice_ = Device_Keyboard;
		break;
	case GameDevice::Controller:
		currentDevice_ = Device_Controller;
		break;
	default:
		break;
	}

	KeyBoardFrameSetting();
	ControllerFrameSetting();

	return true;

}

void CSkillInfoRender::Render()
{
	uiFrame_[currentDevice_]->Render(position_.x, position_.y);
}

void CSkillInfoRender::RenderDebug2D()
{

}

void CSkillInfoRender::Release()
{
	for (int i = 0; i < Device_Count; i++)
	{
		uiFrame_[i].reset();
	}

	font_.reset();
	padButtonFont_.reset();
}

void CSkillInfoRender::RenderKeyName()
{
	
	if (currentDevice_ == Device_Keyboard)
	{
		//キーボード用文字
		auto k = currentDevice_;
		for (int i = 0; i < SKILLMAX_COUNT; i++)
		{
			font_->RenderString(skillFrame_[k][i].position.x - skillFrame_[k][i].rect.GetWidth() * 0.5f, skillFrame_[k][i].position.y - skillFrame_[k][i].rect.GetHeight() * 0.5f, skillFrame_[k][i].str);
		}
	}
	else
	{
		//コントローラー用文字
		auto c = currentDevice_;
		for (int i = 0; i < SKILLMAX_COUNT; i++)
		{
			font_->RenderString(skillFrame_[c][i].position.x - skillFrame_[c][i].rect.GetWidth() * 0.5f, skillFrame_[c][i].position.y - skillFrame_[c][i].rect.GetHeight() * 0.5f, skillFrame_[c][i].str);
		}

		//ボタン文字
		const auto color = MOF_ARGB(255, 10, 10, 10);
		const float height = 905;
		padButtonFont_->RenderFormatString(520, height, color, "LT");
		padButtonFont_->RenderFormatString(765, height, color, "LB");
		padButtonFont_->RenderFormatString(1135, height, color, "RB");
		padButtonFont_->RenderFormatString(1380, height, color, "RT");
	}

	
}


void ActionGame::CSkillInfoRender::ChangeKeyBoardTexture()
{
	currentDevice_ = Device_Keyboard;
}

void ActionGame::CSkillInfoRender::ChangeControllerTexture()
{
	currentDevice_ = Device_Controller;
}





void CSkillInfoRender::KeyBoardFrameSetting()
{
	for (int i = 0; i < SKILLMAX_COUNT; i++)
	{
		skillFrame_[Device_Keyboard][i].size = 50;
	}

	int cnt = 0;

	//座標と当たり判定用矩形設定
	//左側
	for (int x = 0; x < SKILL_LEFTLINE_COUNT; x++)
	{
		for (int y = 0; y < SKILL_COLUMN_COUNT; y++)
		{
			skillFrame_[Device_Keyboard][cnt].position = Vector2(709, y * 61 + 939);

			cnt++;
		}
	}
	//真ん中
	for (int x = 0; x < SKILL_CENTERLINE_COUNT; x++)
	{
		for (int y = 0; y < SKILL_COLUMN_COUNT; y++)
		{
			skillFrame_[Device_Keyboard][cnt].position = 
				Vector2(x * 63 + 825, y * 61 + 939);
			cnt++;
		}
	}
	//右側
	for (int x = 0; x < SKILL_RIGHTLINE_COUNT; x++)
	{
		for (int y = 0; y < SKILL_COLUMN_COUNT; y++)
		{
			skillFrame_[Device_Keyboard][cnt].position = 
				Vector2(x * 70 + 1255, y * 61 + 939);
			cnt++;
		}
	}

	//当たり判定用矩形設定
	for (int i = 0; i < SKILLMAX_COUNT; i++)
	{
		auto& frame = skillFrame_[Device_Keyboard][i];
		Vector2 leftTop(frame.position.x - frame.size * 0.5f, frame.position.y - frame.size * 0.5f);
		Vector2 rightButtom(frame.position.x + frame.size * 0.5f, frame.position.y + frame.size * 0.5f);
		frame.rect = CRectangle(leftTop, rightButtom);
	}

	SetKeyBoardName();
}

void ActionGame::CSkillInfoRender::ControllerFrameSetting()
{
	for (int i = 0; i < SKILLMAX_COUNT; i++)
	{
		skillFrame_[Device_Controller][i].size = 50;
	}

	int cnt = 0;

	//座標と当たり判定用矩形設定
	
	//パッド用の形になるよう配置
	auto skillPos = new Vector2[Controller_Pos_Count];
	skillPos[Controller_Pos_Up] = Vector2(0, -30);
	skillPos[Controller_Pos_Left] = Vector2(-59, 2);
	skillPos[Controller_Pos_Right] = Vector2(59, 2);
	skillPos[Controller_Pos_Down] = Vector2(0, 30);
	
	//LT
	for (int i = 0; i < Controller_Pos_Count; i++)
	{
		skillFrame_[Device_Controller][cnt].position 
			= Vector2(skillPos[i].x + 595, skillPos[i].y + 969);
		cnt++;
	}
	//LB
	for (int i = 0; i < Controller_Pos_Count; i++)
	{
		skillFrame_[Device_Controller][cnt].position
			= Vector2(skillPos[i].x + 838, skillPos[i].y + 969);
		cnt++;
	}
	//RB
	for (int i = 0; i < Controller_Pos_Count; i++)
	{
		skillFrame_[Device_Controller][cnt].position
			= Vector2(skillPos[i].x + 1084, skillPos[i].y + 969);
		cnt++;
	}
	//RT
	for (int i = 0; i < Controller_Pos_Count; i++)
	{
		skillFrame_[Device_Controller][cnt].position
			= Vector2(skillPos[i].x + 1324, skillPos[i].y + 969);
		cnt++;
	}
	//右端（２つのスキル欄）
	for (int i = 0; i < SKILL_COLUMN_COUNT; i++)
	{
		skillFrame_[Device_Controller][cnt].position = Vector2(1513, i * 60 + 939);
		cnt++;
	}

	//当たり判定用矩形設定
	for (int i = 0; i < SKILLMAX_COUNT; i++)
	{
		auto& frame = skillFrame_[Device_Controller][i];
		Vector2 leftTop(frame.position.x - frame.size * 0.5f, frame.position.y - frame.size * 0.5f);
		Vector2 rightButtom(frame.position.x + frame.size * 0.5f, frame.position.y + frame.size * 0.5f);
		frame.rect = CRectangle(leftTop, rightButtom);
	}

	delete[] skillPos;

	SetControllerName();
}

void CSkillInfoRender::SetKeyBoardName()
{

	//キーボード名設定
	int cnt = 0;

	auto& frame = skillFrame_[Device_Keyboard];
	frame[cnt].str = "SHIFT";	//0
	
	cnt++;
	frame[cnt].str = "SPACE";	//1

	cnt++;
	frame[cnt].str = "Q";		//2

	cnt++;
	frame[cnt].str = "A";		//3

	cnt++;
	frame[cnt].str = "W";		//4

	cnt++;
	frame[cnt].str = "S";		//5

	cnt++;
	frame[cnt].str = "E";		//6

	cnt++;
	frame[cnt].str = "D";		//7

	cnt++;
	frame[cnt].str = "R";		//8

	cnt++;
	frame[cnt].str = "F";		//9

	cnt++;
	frame[cnt].str = "T";		//10

	cnt++;
	frame[cnt].str = "C";		//11

	cnt++;
	frame[cnt].str = "G";		//12

	cnt++;
	frame[cnt].str = "V";		//13

	cnt++;
	frame[cnt].str = "１";		//14

	cnt++;
	frame[cnt].str = "３";		//15

	cnt++;
	frame[cnt].str = "２";		//16

	cnt++;
	frame[cnt].str = "４";		//17

	//キーの座標設定
	auto& key = keyIndexs_[Device_Keyboard];
	key[INPUT_KEY_SKILL1] = 7;
	key[INPUT_KEY_SKILL2] = 3;
	key[INPUT_KEY_SKILL3] = 5;
	key[INPUT_KEY_ESCAPE] = 1;
	key[INPUT_KEY_SKILL4] = 9;
}

void ActionGame::CSkillInfoRender::SetControllerName()
{
	/*
	* LT:0~3
	* LB:4~7
	* RB:8~11
	* RT:12~15
	* 右端2つ:16~17
	* 
	* 上左からカウント
	*/
	auto& frame = skillFrame_[Device_Controller];
	frame[16].str = "Y";	//三角
	frame[17].str = "A";	//丸


	//キーの座標設定
	auto& key = keyIndexs_[Device_Controller];
	key[INPUT_KEY_SKILL1] = 10;
	key[INPUT_KEY_SKILL2] = 8;
	key[INPUT_KEY_SKILL3] = 9;
	key[INPUT_KEY_ESCAPE] = 17;
	key[INPUT_KEY_SKILL4] = 11;
}
