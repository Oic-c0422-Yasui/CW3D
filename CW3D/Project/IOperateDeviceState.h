#pragma once
#include "DeviceDefine.h"
#include <memory>

/*
* @brief	操作しているデバイスの状態を保持するインタフェース
*/
class IOperateDeviceState
{
public:
	virtual ~IOperateDeviceState() = default;
	/*
	* @brief	操作しているデバイスを取得
	*/
	virtual  GameDevice GetDeviceType() const noexcept = 0;
};

using OperateDevicePtr = std::shared_ptr<IOperateDeviceState>;