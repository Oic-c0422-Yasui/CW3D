#include	"Input.h"

using namespace Input;

Input::CInput::CInput()
	: keyMap_()
{ 
}

void Input::CInput::AddKeyboardKey(const KeyType& kn, int key)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ key, -1, -1, KeyData::Type::Keyboard });
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ key, -1, -1, KeyData::Type::Keyboard });
	}
}

void Input::CInput::AddKeyboardKey(const KeyType& kn, int positiveKey, int negativeKey)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ positiveKey, negativeKey, -1, KeyData::Type::Keyboard });
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ positiveKey, negativeKey, -1, KeyData::Type::Keyboard });
	}
}

void Input::CInput::AddMouseKey(const KeyType& kn, int Key)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ Key, -1, -1, KeyData::Type::Mouse });
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ Key, -1, -1, KeyData::Type::Mouse });
	}
}

void Input::CInput::AddJoypadKey(const KeyType& kn, int pad, int key)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ key, -1, pad, KeyData::Type::JoyPad });
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ key, -1, pad, KeyData::Type::JoyPad });
	}
}

void Input::CInput::AddJoyStickHorizontal(const KeyType& kn, int pad)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ -1, -1, pad, KeyData::Type::JoyStickHorizontal });
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ -1, -1, pad, KeyData::Type::JoyStickHorizontal });
	}
}

void Input::CInput::AddJoyStickVertical(const KeyType& kn, int pad)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ -1, -1, pad, KeyData::Type::JoyStickVertical });
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ -1, -1, pad, KeyData::Type::JoyStickVertical });
	}
}

/**
 * @brief		更新
 */
void Input::CInput::Update()
{
	for (auto k = keyMap_.begin(); k != keyMap_.end(); ++k)
	{
		if (IsPress(k->first) || IsNegativePress(k->first))
		{
			k->second.holdTime_ += CUtilities::GetFrameSecond();
		}
		else
		{
			k->second.holdTime_ = 0;
		}
		if (IsPush(k->first) || IsNegativePush(k->first))
		{
			k->second.pushTime_ = 0;
		}
		else
		{
			k->second.pushTime_ += CUtilities::GetFrameSecond();
		}


		k->second.previousValue_ = k->second.currentValue_;
		k->second.currentValue_ = 0;
		for (auto& key : k->second.inputKey_)
		{
			switch (key.type_)
			{
				//キーボード
			case KeyData::Type::Keyboard:
				k->second.currentValue_ += GetKeyboardKeyState(key.positiveNo_, key.negativeNo_);
				break;

				//マウス
			case KeyData::Type::Mouse:
				k->second.currentValue_ += GetMouseKeyState(key.positiveNo_, key.negativeNo_);
				break;

				//ジョイパッド
			case KeyData::Type::JoyPad:
				k->second.currentValue_ += GetJoypadKeyState(key.padNo_, key.positiveNo_, key.negativeNo_);
				break;

				//ジョイスティック
			case KeyData::Type::JoyStickHorizontal:
				k->second.currentValue_ += GetJoypadStickHorizontal(key.padNo_);
				break;

				//ジョイスティック
			case KeyData::Type::JoyStickVertical:
				k->second.currentValue_ += GetJoypadStickVertical(key.padNo_);
				break;
			}
		}
		//-1～+1でクリップ
		if (k->second.currentValue_ > 1) { k->second.currentValue_ = 1; }
		else if (k->second.currentValue_ < -1) { k->second.currentValue_ = -1; }
	}
}

float Input::CInput::GetAxis(const KeyType& keyName) const
{
	const auto& v = keyMap_.find(keyName);
	if (v == keyMap_.end()) { return 0; }
	const KeyData& kd = v->second;
	return kd.currentValue_;
}

bool Input::CInput::IsPush(const KeyType& keyName) const
{
	const auto& v = keyMap_.find(keyName);
	if (v == keyMap_.end()) { return 0; }
	const KeyData& kd = v->second;
	return kd.currentValue_ > kd.inputValue_ && kd.previousValue_ < kd.inputValue_;
}

bool Input::CInput::IsDoublePush(const KeyType& keyName) const
{
	const auto& v = keyMap_.find(keyName);
	if (v == keyMap_.end()) { return 0; }
	const KeyData& kd = v->second;
	return kd.currentValue_ > kd.inputValue_ && kd.previousValue_ < kd.inputValue_&&
		kd.pushTime_ < DOUBLE_PUSH_TIME;
}

bool Input::CInput::IsNegativePush(const KeyType& keyName) const
{
	const auto& v = keyMap_.find(keyName);
	if (v == keyMap_.end()) { return 0; }
	const KeyData& kd = v->second;
	return kd.currentValue_ < -kd.inputValue_ && kd.previousValue_ > -kd.inputValue_;
}

bool Input::CInput::IsNegativeDoublePush(const KeyType& keyName) const
{
	const auto& v = keyMap_.find(keyName);
	if (v == keyMap_.end()) { return 0; }
	const KeyData& kd = v->second;
	return kd.currentValue_ < -kd.inputValue_ && kd.previousValue_ > -kd.inputValue_ &&
		kd.pushTime_ < DOUBLE_PUSH_TIME;
}

bool Input::CInput::IsPull(const KeyType& keyName) const
{
	const auto& v = keyMap_.find(keyName);
	if (v == keyMap_.end()) { return 0; }
	const KeyData& kd = v->second;
	return kd.currentValue_ < kd.inputValue_&& kd.previousValue_ > kd.inputValue_;
}

bool Input::CInput::IsNegativePull(const KeyType& keyName) const
{
	const auto& v = keyMap_.find(keyName);
	if (v == keyMap_.end()) { return 0; }
	const KeyData& kd = v->second;
	return kd.currentValue_ > kd.inputValue_ && kd.previousValue_ < -kd.inputValue_;
}

bool Input::CInput::IsPress(const KeyType& keyName) const
{
	const auto& v = keyMap_.find(keyName);
	if (v == keyMap_.end()) { return 0; }
	const KeyData& kd = v->second;
	return kd.currentValue_ > kd.inputValue_;
}

float Input::CInput::GetPressTime(const KeyType& keyName) const
{
	const auto& v = keyMap_.find(keyName);
	if (v == keyMap_.end()) { return 0; }
	const KeyData& kd = v->second;
	return kd.holdTime_;
}

float Input::CInput::GetNegativePressTime(const KeyType& keyName) const
{
	const auto& v = keyMap_.find(keyName);
	if (v == keyMap_.end()) { return 0; }
	const KeyData& kd = v->second;
	return kd.holdTime_;
}

bool Input::CInput::IsNegativePress(const KeyType& keyName) const
{
	const auto& v = keyMap_.find(keyName);
	if (v == keyMap_.end()) { return 0; }
	const KeyData& kd = v->second;
	return kd.currentValue_ < -kd.inputValue_;
}

std::vector<Input::IInput::KeyType> Input::CInput::GetKeyList() const
{
	std::vector<KeyType> keys;
	for (auto& key : keyMap_)
	{
		keys.push_back(key.first);
	}
	return keys;
}
