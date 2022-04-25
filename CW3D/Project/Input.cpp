#include	"Input.h"

using namespace Sample;

/**
 * @brief		�X�V
 */
void Input::Update()
{
	for (auto k = keyMap_.begin(); k != keyMap_.end(); ++k)
	{
		k->second.prevValue = k->second.nowValue;
		k->second.nowValue = 0;
		for (auto& key : k->second.key)
		{
			switch (key.type)
			{
				//�L�[�{�[�h
			case KeyData::Type::Keyboard:
				k->second.nowValue += GetKeyboardKeyState(key.positiveNo, key.negativeNo);
				break;

				//�}�E�X
			case KeyData::Type::Mouse:
				k->second.nowValue += GetMouseKeyState(key.positiveNo, key.negativeNo);
				break;

				//�W���C�p�b�h
			case KeyData::Type::JoyPad:
				k->second.nowValue += GetJoypadKeyState(key.padNo, key.positiveNo, key.negativeNo);
				break;

				//�W���C�X�e�B�b�N
			case KeyData::Type::JoyStickHorizontal:
				k->second.nowValue += GetJoypadStickHorizontal(key.padNo);
				break;

				//�W���C�X�e�B�b�N
			case KeyData::Type::JoyStickVertical:
				k->second.nowValue += GetJoypadStickVertical(key.padNo);
				break;

			}
		}
		//-1�`+1�ŃN���b�v
		if (k->second.nowValue > 1) { k->second.nowValue = 1; }
		else if (k->second.nowValue < -1) { k->second.nowValue = -1; }
	}
}
