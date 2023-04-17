#pragma once
#include "DeviceDefine.h"
#include <memory>

/*
* @brief	���삵�Ă���f�o�C�X�̏�Ԃ�ێ�����C���^�t�F�[�X
*/
class IOperateDeviceState
{
public:
	virtual ~IOperateDeviceState() = default;
	/*
	* @brief	���삵�Ă���f�o�C�X���擾
	*/
	virtual  GameDevice GetDeviceType() const noexcept = 0;
};

using OperateDevicePtr = std::shared_ptr<IOperateDeviceState>;