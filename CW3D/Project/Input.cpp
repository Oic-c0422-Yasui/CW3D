#include	"Input.h"

using namespace Input;



Input::CInput::CInput()
	: keyMap_()
	, operateDevice_()
{ 
}


/**
 * @brief		“o˜^ƒL[‚Ì’Ç‰Á
 * @param[in]	keyName				“o˜^ƒL[–¼
 * @param[in]	key				“o˜^ƒL[
 */
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

/**
 * @brief		“o˜^ƒL[‚Ì’Ç‰Á
 * @param[in]	keyName				“o˜^ƒL[–¼
 * @param[in]	positiveKey		+•ûŒü‚Ì“o˜^ƒL[
 * @param[in]	negativeKey		-•ûŒü‚Ì“o˜^ƒL[
 */
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

/**
 * @brief		“o˜^ƒL[‚Ì’Ç‰Á
 * @param[in]	keyName		“o˜^ƒL[–¼
 * @param[in]	Key		“o˜^ƒL[
 */
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

/**
 * @brief		“o˜^ƒL[‚Ì’Ç‰Á
 * @param[in]	keyName				“o˜^ƒL[–¼
 * @param[in]	pad				“o˜^ƒpƒbƒh
 * @param[in]	key				“o˜^ƒL[
 */
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

/**
 * @brief		“o˜^ƒL[‚Ì’Ç‰Á
 * @param[in]	keyName				“o˜^ƒL[–¼
 * @param[in]	pad				“o˜^ƒpƒbƒh
 * @param[in]	positiveKey		+•ûŒü‚Ì“o˜^ƒL[
 * @param[in]	negativeKey		-•ûŒü‚Ì“o˜^ƒL[
 */
void Input::CInput::AddJoypadKey(const KeyType& kn, int pad, int positiveKey, int negativeKey)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ positiveKey, negativeKey, pad, KeyData::Type::JoyPad });
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ positiveKey, negativeKey, pad, KeyData::Type::JoyPad });
	}
}

/**
 * @brief		“o˜^ƒL[‚Ì’Ç‰Á
 * @param[in]	keyName			“o˜^ƒL[–¼
 * @param[in]	pad				“o˜^ƒpƒbƒh
 * @param[in]	key				“o˜^ƒL[
 * @param[in]	holdKeys		“o˜^ƒL[”z—ñ
 * @param[in]	disableKeys		“ü—Í‚ðŽó‚¯•t‚¯‚È‚¢“o˜^‚³‚ê‚Ä‚¢‚éƒL[–¼
 */
void Input::CInput::AddJoypadKey(const KeyType& kn, int pad, int key, const ArrayKey& holdKeys, const ArrayKeyType& disableKeys)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ key, -1, pad, KeyData::Type::JoyPad, holdKeys});
		km->second.disableKeys_ = disableKeys;
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ key, -1, pad, KeyData::Type::JoyPad, holdKeys});
		km->second.disableKeys_ = disableKeys;
	}
}

/**
 * @brief		“o˜^ƒL[‚Ì’Ç‰Á
 * @param[in]	keyName				“o˜^ƒL[–¼
 * @param[in]	pad				“o˜^ƒpƒbƒh
 */
void Input::CInput::AddLeftJoyStickHorizontal(const KeyType& kn, int pad)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ -1, -1, pad, KeyData::Type::Left_JoyStick_Horizontal });
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ -1, -1, pad, KeyData::Type::Left_JoyStick_Horizontal });
	}
}

/**
 * @brief		“o˜^ƒL[‚Ì’Ç‰Á
 * @param[in]	keyName				“o˜^ƒL[–¼
 * @param[in]	pad				“o˜^ƒpƒbƒh
 */
void Input::CInput::AddLeftJoyStickVertical(const KeyType& kn, int pad)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ -1, -1, pad, KeyData::Type::Left_JoyStick_Vertical });
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ -1, -1, pad, KeyData::Type::Left_JoyStick_Vertical });
	}
}

/**
 * @brief		“o˜^ƒL[‚Ì’Ç‰Á
 * @param[in]	keyName				“o˜^ƒL[–¼
 * @param[in]	pad				“o˜^ƒpƒbƒh
 */
void Input::CInput::AddRightJoyStickHorizontal(const KeyType& kn, int pad)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ -1, -1, pad, KeyData::Type::Right_JoyStick_Horizontal });
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ -1, -1, pad, KeyData::Type::Right_JoyStick_Horizontal });
	}
}

/**
 * @brief		“o˜^ƒL[‚Ì’Ç‰Á
 * @param[in]	keyName				“o˜^ƒL[–¼
 * @param[in]	pad				“o˜^ƒpƒbƒh
 */
void Input::CInput::AddRightJoyStickVertical(const KeyType& kn, int pad)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ -1, -1, pad, KeyData::Type::Right_JoyStick_Vertical });
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ -1, -1, pad, KeyData::Type::Right_JoyStick_Vertical });
	}
}

/**
 * @brief		“o˜^ƒL[‚Ì’Ç‰Á
 * @param[in]	keyName				“o˜^ƒL[–¼
 * @param[in]	pad				“o˜^ƒpƒbƒh
 */
void Input::CInput::AddDPadLeftKey(const KeyType& kn, int pad)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ -1, -1, pad, KeyData::Type::DPad_Left });
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ -1, -1, pad, KeyData::Type::DPad_Left });
	}
}

/**
 * @brief		“o˜^ƒL[‚Ì’Ç‰Á
 * @param[in]	keyName				“o˜^ƒL[–¼
 * @param[in]	pad				“o˜^ƒpƒbƒh
 * @param[in]	holdKeys		“o˜^ƒL[”z—ñ
 * @param[in]	disableKeys		“ü—Í‚ðŽó‚¯•t‚¯‚È‚¢“o˜^‚³‚ê‚Ä‚¢‚éƒL[–¼
 */
void Input::CInput::AddDPadLeftKey(const KeyType& kn, int pad, const ArrayKey& holdKeys, const ArrayKeyType& disableKeys)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ -1, -1, pad, KeyData::Type::DPad_Left, holdKeys});
		km->second.disableKeys_ = disableKeys;
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ -1, -1, pad, KeyData::Type::DPad_Left, holdKeys });
		keyMap_[kn].disableKeys_ = disableKeys;
	}
}

/**
 * @brief		“o˜^ƒL[‚Ì’Ç‰Á
 * @param[in]	keyName				“o˜^ƒL[–¼
 * @param[in]	pad				“o˜^ƒpƒbƒh
 */
void Input::CInput::AddDPadRightKey(const KeyType& kn, int pad)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ -1, -1, pad, KeyData::Type::DPad_Right });
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ -1, -1, pad, KeyData::Type::DPad_Right });
	}
}

/**
 * @brief		“o˜^ƒL[‚Ì’Ç‰Á
 * @param[in]	keyName				“o˜^ƒL[–¼
 * @param[in]	pad				“o˜^ƒpƒbƒh
 * @param[in]	holdKeys		“o˜^ƒL[”z—ñ
 * @param[in]	disableKeys		“ü—Í‚ðŽó‚¯•t‚¯‚È‚¢“o˜^‚³‚ê‚Ä‚¢‚éƒL[–¼
 */
void Input::CInput::AddDPadRightKey(const KeyType& kn, int pad, const ArrayKey& holdKeys, const ArrayKeyType& disableKeys)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ -1, -1, pad, KeyData::Type::DPad_Right, holdKeys });
		km->second.disableKeys_ = disableKeys;
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ -1, -1, pad, KeyData::Type::DPad_Right, holdKeys });
		keyMap_[kn].disableKeys_ = disableKeys;
	}
}

/**
 * @brief		“o˜^ƒL[‚Ì’Ç‰Á
 * @param[in]	keyName				“o˜^ƒL[–¼
 * @param[in]	pad				“o˜^ƒpƒbƒh
 */
void Input::CInput::AddDPadUpKey(const KeyType& kn, int pad)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ -1, -1, pad, KeyData::Type::DPad_Up });
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ -1, -1, pad, KeyData::Type::DPad_Up });
	}
}

/**
 * @brief		“o˜^ƒL[‚Ì’Ç‰Á
 * @param[in]	keyName				“o˜^ƒL[–¼
 * @param[in]	pad				“o˜^ƒpƒbƒh
 * @param[in]	holdKeys		“o˜^ƒL[”z—ñ
 * @param[in]	disableKeys		“ü—Í‚ðŽó‚¯•t‚¯‚È‚¢“o˜^‚³‚ê‚Ä‚¢‚éƒL[–¼
 */
void Input::CInput::AddDPadUpKey(const KeyType& kn, int pad, const ArrayKey& holdKeys, const ArrayKeyType& disableKeys)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ -1, -1, pad, KeyData::Type::DPad_Up, holdKeys });
		km->second.disableKeys_ = disableKeys;
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ -1, -1, pad, KeyData::Type::DPad_Up, holdKeys });
		keyMap_[kn].disableKeys_ = disableKeys;
	}
}

/**
 * @brief		“o˜^ƒL[‚Ì’Ç‰Á
 * @param[in]	keyName				“o˜^ƒL[–¼
 * @param[in]	pad				“o˜^ƒpƒbƒh
 */
void Input::CInput::AddDPadDownKey(const KeyType& kn, int pad)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ -1, -1, pad, KeyData::Type::DPad_Down });
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ -1, -1, pad, KeyData::Type::DPad_Down });
	}
}

/**
 * @brief		“o˜^ƒL[‚Ì’Ç‰Á
 * @param[in]	keyName				“o˜^ƒL[–¼
 * @param[in]	pad				“o˜^ƒpƒbƒh
 * @param[in]	holdKeys		“o˜^ƒL[”z—ñ
 * @param[in]	disableKeys		“ü—Í‚ðŽó‚¯•t‚¯‚È‚¢“o˜^‚³‚ê‚Ä‚¢‚éƒL[–¼
 */
void Input::CInput::AddDPadDownKey(const KeyType& kn, int pad, const ArrayKey& holdKeys, const ArrayKeyType& disableKeys)
{
	auto km = keyMap_.find(kn);
	if (km != keyMap_.end())
	{
		km->second.inputKey_.push_back({ -1, -1, pad, KeyData::Type::DPad_Down, holdKeys });
		km->second.disableKeys_ = disableKeys;
	}
	else
	{
		keyMap_[kn].inputKey_.push_back({ -1, -1, pad, KeyData::Type::DPad_Down, holdKeys });
		keyMap_[kn].disableKeys_ = disableKeys;
	}
}

void Input::CInput::SetChangeDevice(KeyData::Type type, float currentVal)
{
	if (currentVal == 0)
	{
		return;
	}
	
	switch (type)
	{
	case Input::CInput::KeyData::Type::Keyboard:
	case Input::CInput::KeyData::Type::Mouse:
		operateDevice_.ChangeDevice(GameDevice::KeyBoardAndMouse);
		break;
	case Input::CInput::KeyData::Type::Left_JoyStick_Horizontal:
	case Input::CInput::KeyData::Type::Left_JoyStick_Vertical:
	case Input::CInput::KeyData::Type::Right_JoyStick_Horizontal:
	case Input::CInput::KeyData::Type::Right_JoyStick_Vertical:
	case Input::CInput::KeyData::Type::DPad_Left:
	case Input::CInput::KeyData::Type::DPad_Right:
	case Input::CInput::KeyData::Type::DPad_Up:
	case Input::CInput::KeyData::Type::DPad_Down:
	case Input::CInput::KeyData::Type::JoyPad:
		operateDevice_.ChangeDevice(GameDevice::Controller);
		break;
	default:
		break;
	}

}

float Input::CInput::GetHoldValue(const KeyData::Key& key)
{
	float value = 1.0f;
	for (auto holdKey : key.holdKeys_)
	{
		value *= GetJoypadKeyState(key.padNo_, holdKey, -1);
	}
	return value;
}

void Input::CInput::DisableInputKey(const KeyData& data)
{
	if (data.currentValue_ >= 1.0f)
	{
		for (auto disable : data.disableKeys_)
		{
			keyMap_[disable].currentValue_ = data.inputValue_;
		}
	}
}

void Input::CInput::InputDPad(DPad_Direction direction, const KeyData::Key& key, KeyData& outData)
{
	float value = 0;
	if (key.holdKeys_.size() > 0)
	{
		//ƒz[ƒ‹ƒh
		value = GetHoldValue(key) * GetDPadKeyState(key.padNo_,direction);
		outData.currentValue_ += value;
		SetChangeDevice(key.type_, value);

		//œŠO“ü—Í
		DisableInputKey(outData);
	}
	else
	{
		//’Êí“ü—Í
		value = GetDPadKeyState(key.padNo_, direction);
		outData.currentValue_ += value;
		SetChangeDevice(key.type_, value);
	}
}

/**
 * @brief		XV
 */
void Input::CInput::Update()
{
	for (auto k = keyMap_.begin(); k != keyMap_.end(); ++k)
	{
		//ƒz[ƒ‹ƒhŽžŠÔ
		if (IsPress(k->first) || IsNegativePress(k->first))
		{
			k->second.holdTime_ += CUtilities::GetFrameSecond();
		}
		else
		{
			k->second.holdTime_ = 0;
		}
		//ƒvƒbƒVƒ…ŽžŠÔ
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
					//ƒL[ƒ{[ƒh
				case KeyData::Type::Keyboard:
				{
					float value = GetKeyboardKeyState(key.positiveNo_, key.negativeNo_);
					k->second.currentValue_ += value;
					SetChangeDevice(key.type_, value);
					break;
				}
					//ƒ}ƒEƒX
				case KeyData::Type::Mouse:
				{
					float value = GetMouseKeyState(key.positiveNo_, key.negativeNo_);
					k->second.currentValue_ += value;
					SetChangeDevice(key.type_, value);
					break;
				}
					//ƒWƒ‡ƒCƒpƒbƒh
				case KeyData::Type::JoyPad:
				{
					float value;
					if (key.holdKeys_.size() > 0)
					{
						//ƒz[ƒ‹ƒh
						value = GetHoldValue(key) * GetJoypadKeyState(key.padNo_, key.positiveNo_, key.negativeNo_);
						k->second.currentValue_ += value;
						SetChangeDevice(key.type_, value);

						//œŠO“ü—Í
						DisableInputKey(k->second);
					}
					else
					{
						//’Êí“ü—Í
						value = GetJoypadKeyState(key.padNo_, key.positiveNo_, key.negativeNo_);
						k->second.currentValue_ += value;
						SetChangeDevice(key.type_, value);
					}

					break;
				}
					//¶ƒWƒ‡ƒCƒXƒeƒBƒbƒN
				case KeyData::Type::Left_JoyStick_Horizontal:
				{
					float value = GetLeftJoyStickHorizontal(key.padNo_);
					k->second.currentValue_ += value;
					SetChangeDevice(key.type_, value);
					break;
				}
					//¶ƒWƒ‡ƒCƒXƒeƒBƒbƒN
				case KeyData::Type::Left_JoyStick_Vertical:
				{
					float value = GetLeftJoyStickVertical(key.padNo_);
					k->second.currentValue_ += value;
					SetChangeDevice(key.type_, value);
					break;
				}
					//‰EƒWƒ‡ƒCƒXƒeƒBƒbƒN
				case KeyData::Type::Right_JoyStick_Horizontal:
				{
					float value = GetRightJoyStickHorizontal(key.padNo_);
					k->second.currentValue_ += value;
					SetChangeDevice(key.type_, value);
					break;
				}
					//‰EƒWƒ‡ƒCƒXƒeƒBƒbƒN
				case KeyData::Type::Right_JoyStick_Vertical:
				{
					float value = GetRightJoyStickVertical(key.padNo_);
					k->second.currentValue_ += value;
					SetChangeDevice(key.type_, value);
					break;
				}
					//\ŽšƒL[¶
				case KeyData::Type::DPad_Left:
				{
					InputDPad(Dpad_Left,key, k->second);
					break;
				}
					//\ŽšƒL[‰E
				case KeyData::Type::DPad_Right:
				{
					InputDPad(Dpad_Left, key, k->second);
					break;
				}
					//\ŽšƒL[ã
				case KeyData::Type::DPad_Up:
				{
					InputDPad(Dpad_Left, key, k->second);
					break;
				}
					//\ŽšƒL[‰º
				case KeyData::Type::DPad_Down:
				{
					InputDPad(Dpad_Left, key, k->second);
					break;
				}
			}//end switch
		}//end key loop

		//-1`+1‚ÅƒNƒŠƒbƒv
		if (k->second.currentValue_ > 1) { k->second.currentValue_ = 1; }
		else if (k->second.currentValue_ < -1) { k->second.currentValue_ = -1; }
	}

	//ƒfƒoƒCƒX•ÏXƒƒbƒZ[ƒW‚ð‘—‚é
	operateDevice_.SendDeviceMessage();
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

GameDevice Input::CInput::GetDeviceType() const noexcept
{
	return operateDevice_.GetDeviceType();
}

