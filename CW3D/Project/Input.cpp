#include	"Input.h"

using namespace ActionGame;

/**
 * @brief		更新
 */
void Input::Update()
{
	for (auto k = m_KeyMap.begin(); k != m_KeyMap.end(); ++k)
	{
		if (IsPress(k->first) || IsNegativePress(k->first))
		{
			k->second.m_HoldTime += CUtilities::GetFrameSecond();
		}
		else
		{
			k->second.m_HoldTime = 0;
		}
		if (IsPush(k->first) || IsNegativePush(k->first))
		{
			k->second.m_PushTime = 0;
		}
		else
		{
			k->second.m_PushTime += CUtilities::GetFrameSecond();
		}


		k->second.m_PreviousValue = k->second.m_NowValue;
		k->second.m_NowValue = 0;
		for (auto& key : k->second.m_Key)
		{
			switch (key.m_Type)
			{
				//キーボード
			case KeyData::Type::Keyboard:
				k->second.m_NowValue += GetKeyboardKeyState(key.m_PositiveNo, key.m_NegativeNo);
				break;

				//マウス
			case KeyData::Type::Mouse:
				k->second.m_NowValue += GetMouseKeyState(key.m_PositiveNo, key.m_NegativeNo);
				break;

				//ジョイパッド
			case KeyData::Type::JoyPad:
				k->second.m_NowValue += GetJoypadKeyState(key.m_PadNo, key.m_PositiveNo, key.m_NegativeNo);
				break;

				//ジョイスティック
			case KeyData::Type::JoyStickHorizontal:
				k->second.m_NowValue += GetJoypadStickHorizontal(key.m_PadNo);
				break;

				//ジョイスティック
			case KeyData::Type::JoyStickVertical:
				k->second.m_NowValue += GetJoypadStickVertical(key.m_PadNo);
				break;
			}
		}
		//-1～+1でクリップ
		if (k->second.m_NowValue > 1) { k->second.m_NowValue = 1; }
		else if (k->second.m_NowValue < -1) { k->second.m_NowValue = -1; }
	}
}
