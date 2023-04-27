#pragma once

#include "MessageDefine.h"
#include "Observable.h"
#include <string>
#include <functional>
#include <memory>

namespace Messenger
{
    using MessageFunc = std::function<void()>;
    using MessageFuncPtr = std::shared_ptr<ActionGame::IObserver<void>>;
    using MessageName = std::string;
    /*
    * @brief    ���b�Z�[�W���󂯎�����ۂ̏�����o�^����C���^�t�F�[�X
    */
    class __declspec(novtable) IRegister
    {
    public:
        virtual ~IRegister() = default;

        /*
        * @brief    ���b�Z�[�W���󂯎�����ۂ̏�����ǉ�
        * @param    type�@���b�Z�[�W�̎��
        * @param    name�@���b�Z�[�W�̖��O
        * @param    func    �������e�̊֐��|�C���^
        */
        virtual void Regist(GameMessageType type,const MessageName& name, const MessageFuncPtr& func) = 0;
        /*
        * @brief    ���b�Z�[�W���󂯎�����ۂ̏�����ǉ�
        * @param    type�@���b�Z�[�W�̎��
        * @param    name    ���b�Z�[�W�̖��O
        * @param    func    �������e�̊֐�
        * @return   �������e�̊֐��|�C���^
        */
        virtual MessageFuncPtr Regist(GameMessageType type, const MessageName& name, const MessageFunc& func) = 0;

        /*
        * @brief    ���b�Z�[�W���󂯎�����ۂ̏������폜
        * @param    type�@   ���b�Z�[�W�̎��
        * @param    name    ���b�Z�[�W�̖��O
        */
        virtual bool Delete(GameMessageType message, const MessageName& name) = 0;
    };
}