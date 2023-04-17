#pragma once
#include "DeviceDefine.h"
#include "IOperateDeviceState.h"

/*
* @brief	���삵�Ă���f�o�C�X�̏�Ԃ�ێ�����
*/
class COperateDeviceState : public IOperateDeviceState
{
private:
	GameDevice currentDevice_;
	GameDevice prevDevice_;
public:
	COperateDeviceState();
	/*
	* @brief	�o�^����Ă�����l�Ƀ��b�Z�[�W�𑗂�
				�i�f�o�C�X���ύX����Ă��Ȃ��ꍇ�̓��b�Z�[�W�𑗂�Ȃ��j
	*/
	void SendDeviceMessage();
	/*
	* @brief	���삵�Ă���f�o�C�X�ύX
	*/
	void ChangeDevice(GameDevice device) noexcept;
	/*
	 * @brief		���삵�Ă���f�o�C�X�̃^�C�v�擾
	 * @return		�f�o�C�X�̃^�C�v
	 */
	GameDevice GetDeviceType() const noexcept override;

};

using OperateDeviceStatePtr = std::shared_ptr<COperateDeviceState>;

