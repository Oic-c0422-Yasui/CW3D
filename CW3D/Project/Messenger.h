#pragma once
#include "IMessenger.h"
#include    <map>
#include "IReceiver.h"

namespace ActionGame
{

    /*
    * @brief    ���b�Z�[�W�𑗂�N���X
    */
    class CMessenger : public IMessenger
    {
    private:
        std::map<int, > m_ReceiverLists;
    public:
        CMessenger();
        
        /*
        * @brief    ���b�Z�[�W�𑗂�
        * @param    message�@���b�Z�[�W�̎��
        */
        void Send(GameMessageType message) override;

        /*
        * @brief    ���b�Z�[�W���󂯎�鑊���ǉ�
        * @param    message�@���b�Z�[�W�̎��
        * @param    recv�@���b�Z�[�W�̎��l
        */
        void AddReceiver(GameMessageType message, ReceiverPtr recv) override
        {
            m_ReceiverLists[message].push_back(recv);
        }

        /*
        * @brief    ���b�Z�[�W���󂯎�鑊����폜
        */
        void DeleteReceiver(GameMessageType message) override
        {
            m_ReceiverLists[message].clear();
        }
    };
}


