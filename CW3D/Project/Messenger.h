#pragma once
#include "IMessenger.h"
#include    <map>
#include    <cassert>
#include "Subject.h"

namespace Messenger
{

    /*
    * @brief    ���b�Z�[�W�𑗂�N���X
    */
    class CMessenger : public IMessenger
    {
    private:
        std::map<int, ActionGame::CSubject<void>> observeMap_;
    public:
        CMessenger();
        
        /*
        * @brief    ���b�Z�[�W�𑗂�
        * @param    message�@���b�Z�[�W�̎��
        */
        void Send(GameMessageType message) const override;

        /*
         * @brief    ���b�Z�[�W���󂯎�����ۂ̏�����ǉ�
         * @param    message�@���b�Z�[�W�̎��
         * @param    func    �������e�̊֐�
         */
        void Regist(GameMessageType message, const std::function<void>& func) override;
        

        /*
        * @brief    ���b�Z�[�W���󂯎�鑊����폜
        */
        void Delete(GameMessageType message) override;
    };
}


