#include "StateInput.h"

void Input::CStateInput::Update()
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
	}
}

void Input::CStateInput::AddKey(const KeyType& keyName)
{
	keyMap_.emplace(keyName, KeyData());
}

void Input::CStateInput::SetKeyValue(const KeyType& keyName, float value)
{
	const auto& it = keyMap_.find(keyName);
	if (it == keyMap_.end()) 
	{ 
		return; 
	}
	KeyData& kd = it->second;
	kd.currentValue_ = value;
}

float Input::CStateInput::GetAxis(const KeyType& keyName) const
{
	const auto& value = keyMap_.find(keyName);
	if (value == keyMap_.end())
	{
		return 0;
	}
	const KeyData& kd = value->second;
	return kd.currentValue_;
}

bool Input::CStateInput::IsPush(const KeyType& keyName) const
{
	const auto& value = keyMap_.find(keyName);
	if (value == keyMap_.end())
	{
		return 0;
	}
	const KeyData& kd = value->second;
	return kd.currentValue_ > kd.inputValue_ && kd.previousValue_ < kd.inputValue_;
}

bool Input::CStateInput::IsDoublePush(const KeyType& keyName) const
{
	const auto& value = keyMap_.find(keyName);
	if (value == keyMap_.end())
	{
		return 0;
	}
	const KeyData& kd = value->second;
	return kd.currentValue_ > kd.inputValue_ && kd.previousValue_ < kd.inputValue_&&
		kd.pushTime_ < DOUBLE_PUSH_TIME;
}

bool Input::CStateInput::IsNegativePush(const KeyType& keyName) const
{
	const auto& value = keyMap_.find(keyName);
	if (value == keyMap_.end())
	{
		return 0;
	}
	const KeyData& kd = value->second;
	return kd.currentValue_ < -kd.inputValue_ && kd.previousValue_ > -kd.inputValue_;
}

bool Input::CStateInput::IsNegativeDoublePush(const KeyType& keyName) const
{
	const auto& value = keyMap_.find(keyName);
	if (value == keyMap_.end())
	{
		return 0;
	}
	const KeyData& kd = value->second;
	return kd.currentValue_ < -kd.inputValue_ && kd.previousValue_ > -kd.inputValue_ &&
		kd.pushTime_ < DOUBLE_PUSH_TIME;
}

bool Input::CStateInput::IsPull(const KeyType& keyName) const
{
	const auto& value = keyMap_.find(keyName);
	if (value == keyMap_.end()) 
	{ 
		return 0; 
	}
	const KeyData& kd = value->second;
	return kd.currentValue_ < kd.inputValue_&& kd.previousValue_ > kd.inputValue_;
}

bool Input::CStateInput::IsNegativePull(const KeyType& keyName) const
{
	const auto& value = keyMap_.find(keyName);
	if (value == keyMap_.end()) 
	{ 
		return 0; 
	}
	const KeyData& kd = value->second;
	return kd.currentValue_ > kd.inputValue_ && kd.previousValue_ < -kd.inputValue_;
}

bool Input::CStateInput::IsPress(const KeyType& keyName) const
{
	const auto& value = keyMap_.find(keyName);
	if (value == keyMap_.end()) 
	{ 
		return 0; 
	}
	const KeyData& kd = value->second;
	return kd.currentValue_ > kd.inputValue_;
}

float Input::CStateInput::GetPressTime(const KeyType& keyName) const
{
	const auto& value = keyMap_.find(keyName);
	if (value == keyMap_.end()) 
	{ 
		return 0; 
	}
	const KeyData& kd = value->second;
	return kd.holdTime_;
}

float Input::CStateInput::GetNegativePressTime(const KeyType& keyName) const
{
	const auto& value = keyMap_.find(keyName);
	if (value == keyMap_.end()) 
	{ 
		return 0; 
	}
	const KeyData& kd = value->second;
	return kd.holdTime_;
}


bool Input::CStateInput::IsNegativePress(const KeyType& keyName) const
{
	const auto& value = keyMap_.find(keyName);
	if (value == keyMap_.end())
	{
		return 0;
	}
	const KeyData& kd = value->second;
	return kd.currentValue_ < -kd.inputValue_;
}

std::vector<Input::IInput::KeyType> Input::CStateInput::GetKeyList() const
{
	std::vector<KeyType> keys;
	for (auto& key : keyMap_)
	{
		keys.push_back(key.first);
	}
	return keys;
}
