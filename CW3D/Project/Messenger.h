#pragma once
#include "IMessenger.h"
#include <map>
#include <cassert>
#include "Subject.h"

namespace Messenger
{
    using ObserveMessage = std::unordered_map<std::string, ActionGame::CSubject<void>>;
    using ObserveMessageMap = std::unordered_map<int, ObserveMessage>;

    /*
    * @brief    ���b�Z�[�W�𑗂�N���X
    */
    class CMessenger : public IMessenger
    {
    private:
        ObserveMessageMap observeMap_;
    public:
        CMessenger();
        ~CMessenger() override;
        
        /*
        * @brief    ���b�Z�[�W�𑗂�
        * @param    message�@���b�Z�[�W�̎��
        */
        bool Send(GameMessageType message) override;

        /*
         * @brief    ���b�Z�[�W���󂯎�����ۂ̏�����ǉ�
         * @param    message�@���b�Z�[�W�̎��
         * @param    func    �������e�̊֐��|�C���^
         */
        void Regist(GameMessageType type, const MessageName& name,const MessageFuncPtr& func) override;

        /*
         * @brief    ���b�Z�[�W���󂯎�����ۂ̏�����ǉ�
         * @param    message�@���b�Z�[�W�̎��
         * @param    func    �������e�̊֐�
         */
        MessageFuncPtr Regist(GameMessageType type, const MessageName& name, const MessageFunc& func) override;
        

        /*
        * @brief    ���b�Z�[�W���󂯎�鑊����폜
        */
        bool Delete(GameMessageType type, const MessageName& name) override;

        /*
       * @brief    ���b�Z�[�W���󂯎�鑊����폜
       */
        bool Delete();
    };
}


