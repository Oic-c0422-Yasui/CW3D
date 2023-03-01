#pragma once

#include "MessageDefine.h"
#include <functional>

namespace Messenger
{
    /*
    * @brief    ���b�Z�[�W���󂯎�����ۂ̏�����o�^����C���^�t�F�[�X
    */
    class IRegister
    {
    public:
        virtual ~IRegister() = default;

        /*
        * @brief    ���b�Z�[�W���󂯎�����ۂ̏�����ǉ�
        * @param    message�@���b�Z�[�W�̎��
        * @param    func    �������e�̊֐�
        */
        virtual void Regist(GameMessageType message, const std::function<void()>& func) = 0;

        /*
        * @brief    ���b�Z�[�W���󂯎�����ۂ̏������폜
        */
        virtual void Delete(GameMessageType message) = 0;
    };
}