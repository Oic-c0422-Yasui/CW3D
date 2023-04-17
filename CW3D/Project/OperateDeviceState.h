#pragma once
#include "DeviceDefine.h"
#include "IOperateDeviceState.h"

/*
* @brief	操作しているデバイスの状態を保持する
*/
class COperateDeviceState : public IOperateDeviceState
{
private:
	GameDevice currentDevice_;
	GameDevice prevDevice_;
public:
	COperateDeviceState();
	/*
	* @brief	登録されている受取人にメッセージを送る
				（デバイスが変更されていない場合はメッセージを送らない）
	*/
	void SendDeviceMessage();
	/*
	* @brief	操作しているデバイス変更
	*/
	void ChangeDevice(GameDevice device) noexcept;
	/*
	 * @brief		操作しているデバイスのタイプ取得
	 * @return		デバイスのタイプ
	 */
	GameDevice GetDeviceType() const noexcept override;

};

using OperateDeviceStatePtr = std::shared_ptr<COperateDeviceState>;

