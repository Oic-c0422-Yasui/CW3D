#pragma once
#include "IReceiver.h"
#include "MessageDefine.h"

namespace ActionGame
{


    /*
    * @brief    ���b�Z�[�W�̎��l��o�^����N���X�̃C���^�t�F�[�X
    */
    class IReceiverRegister
    {
    public:
        virtual ~IReceiverRegister() = default;

        /*
        * @brief    ���b�Z�[�W���󂯎�鑊���ǉ�
        * @param    message�@���b�Z�[�W�̎��
        * @param    recv    ���b�Z�[�W�̎��l
        */
        virtual void AddReceiver(GameMessageType message, ReceiverPtr recv) = 0;

        /*
        * @brief    ���b�Z�[�W���󂯎�鑊����폜
        */
        virtual void DeleteReceiver(GameMessageType message) = 0;
    };
}