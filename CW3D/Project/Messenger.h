#pragma once
#include "IMessenger.h"
#include    <array>
#include "IReceiver.h"

namespace ActionGame
{

    

    class Messenger : public IMessenger
    {
    private:
        std::array<ReceiverList, MessageCount> receiverLists;
    public:
        Messenger();
        
        /*
        * @brief    ���b�Z�[�W�𑗂�
        */
        void Send(GameMessageType message) override;

        /*
        * @brief    ���b�Z�[�W���󂯎�鑊���ǉ�
        */
        void AddReceiver(GameMessageType message, ReceiverPtr recv)
        {
            receiverLists[message].push_back(recv);
        }

        /*
        * @brief    ���b�Z�[�W���󂯎�鑊����폜
        */
        void DeleteReceiver(GameMessageType message)
        {
            receiverLists[message].clear();
        }
    };
}


